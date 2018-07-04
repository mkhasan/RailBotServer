// File: lzhamtest.cpp
// This is a small app primarily designed to test the codec. Sorry, it doesn't really make the best sample, it's just a test harness.
// I also test LZHAM in a private branch of 7zip, mostly to ensure the streaming API is solid. Please contact me if you would like this branch.
// See the decompress_file() function to see how to use the decompression API, and the compress_file() function for the compression API.
// See include/lzham.h for documentation on the public LZHAM API.
// Tested on Windows, Linux, and OSX. On iOS, I use a small "Hello World" test app to test the codec.
// See Copyright Notice and license at the end of include/lzham.h
#if defined(__GNUC__)
#define _FILE_OFFSET_BITS 64
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#if !defined(__APPLE__) && !defined(__FreeBSD__)
#include <malloc.h>
#endif
#include <vector>
#include <string>

#include "timer.h"

#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))

#define LZHAM_PRINT_OUTPUT_PROGRESS

// Note: lzham can be used as static libs, or as a DLL. The default (out of the box) configuration under Win32 loads the DLL.
// To test lzham as a static library under Win32, set LZHAM_USE_LZHAM_DLL to 0, add ../lzhamcomp and ../lzhamdecomp to the additional inc paths, and link with the lzhamcomp and lzhamdecomp libs.
// On non-Win32 platforms, this test app currently assumes static libs.
   #include <unistd.h>
   #define Sleep(ms) usleep(ms*1000)
   #define _aligned_malloc(size, alignment) memalign(alignment, size)
   #define _aligned_free free
   #define fopen fopen64
   #define _fseeki64 fseeko64
   #define _ftelli64 ftello64


   #define QUAD_INT_FMT "%llu"


#if LZHAM_USE_LZHAM_DLL
   #include "lzham_dynamic_lib.h"
#else
   #include "lzham_static_lib.h"
#endif

#ifdef _DEBUG
const bool g_is_debug = true;
#else
const bool g_is_debug = false;
#endif

typedef unsigned char uint8;
typedef unsigned int uint;
typedef unsigned int uint32;

#ifdef __GNUC__
   typedef unsigned long long    uint64;
   typedef long long             int64;
#else
   typedef unsigned __int64      uint64;
   typedef signed __int64        int64;
#endif

#ifdef LZHAM_64BIT
   #define LZHAMTEST_MAX_POSSIBLE_DICT_SIZE LZHAM_MAX_DICT_SIZE_LOG2_X64
   // 256MB default dictionary size under x64 (max is 512MB, but this requires more than 4GB of physical memory without thrashing)
   #define LZHAMTEST_DEFAULT_DICT_SIZE 28
#else
   #define LZHAMTEST_MAX_POSSIBLE_DICT_SIZE LZHAM_MAX_DICT_SIZE_LOG2_X86
   // 64MB default dictionary size under x86
   #define LZHAMTEST_DEFAULT_DICT_SIZE LZHAM_MAX_DICT_SIZE_LOG2_X86
#endif

#if 1
   #define LZHAMTEST_COMP_INPUT_BUFFER_SIZE 65536*4
   #define LZHAMTEST_COMP_OUTPUT_BUFFER_SIZE 65536*4
   #define LZHAMTEST_DECOMP_INPUT_BUFFER_SIZE 65536*4
   #define LZHAMTEST_DECOMP_OUTPUT_BUFFER_SIZE 65536*4
#else
   #define LZHAMTEST_COMP_INPUT_BUFFER_SIZE 1
   #define LZHAMTEST_COMP_OUTPUT_BUFFER_SIZE 1
   #define LZHAMTEST_DECOMP_INPUT_BUFFER_SIZE 1
   #define LZHAMTEST_DECOMP_OUTPUT_BUFFER_SIZE 1
#endif

#define LZHAMTEST_NO_RANDOM_EXTREME_PARSING 1

struct comp_options
{
  comp_options() :
	 m_comp_level(LZHAM_COMP_LEVEL_UBER),
	 m_dict_size_log2(LZHAMTEST_DEFAULT_DICT_SIZE),
	 m_compute_adler32_during_decomp(true),
	 m_max_helper_threads(0),
	 m_unbuffered_decompression(false),
	 m_verify_compressed_data(false),
	 m_randomize_params(false),
	 m_extreme_parsing(false),
	 m_deterministic_parsing(false),
	 m_tradeoff_decomp_rate_for_comp_ratio(false),
	 m_test_compressor_reinit(false),
	m_table_update_rate(LZHAM_DEFAULT_TABLE_UPDATE_RATE)
  {
  }

  void print()
  {
	 printf("Comp level: %u\n", m_comp_level);
	 printf("Dict size: %i (%u bytes)\n", m_dict_size_log2, 1 << m_dict_size_log2);
	 printf("Compute adler32 during decompression: %u\n", (uint)m_compute_adler32_during_decomp);
	 printf("Max helper threads: %i\n", m_max_helper_threads);
	 printf("Unbuffered decompression: %u\n", (uint)m_unbuffered_decompression);
	 printf("Verify compressed data: %u\n", (uint)m_verify_compressed_data);
	 printf("Extreme parsing: %u\n", (uint)m_extreme_parsing);
	 printf("Randomize parameters: %u\n", m_randomize_params);
	 printf("Deterministic parsing: %u\n", m_deterministic_parsing);
	 printf("Trade off decompression rate for compression ratio: %u\n", m_tradeoff_decomp_rate_for_comp_ratio);
	 printf("Test compressor reinit: %u\n", m_test_compressor_reinit);
	printf("Table update speed: %u\n", m_table_update_rate);
  }

  lzham_compress_level m_comp_level;
  int m_dict_size_log2;
  bool m_compute_adler32_during_decomp;
  int m_max_helper_threads;           // -1 = try to auto-detect
  bool m_unbuffered_decompression;
  bool m_verify_compressed_data;
  bool m_randomize_params;
  bool m_extreme_parsing;
  bool m_deterministic_parsing;
  bool m_tradeoff_decomp_rate_for_comp_ratio;
  bool m_test_compressor_reinit;
uint m_table_update_rate;
};


static void print_error(const char *pMsg, ...)
{
   char buf[1024];

   va_list args;
   va_start(args, pMsg);
   vsnprintf(buf, sizeof(buf), pMsg, args);
   va_end(args);

   buf[sizeof(buf) - 1] = '\0';

   fprintf(stderr, "Error: %s", buf);
}

static FILE* open_file_with_retries(const char *pFilename, const char* pMode)
{
   const uint cNumRetries = 8;
   for (uint i = 0; i < cNumRetries; i++)
   {
      FILE* pFile = fopen(pFilename, pMode);
      if (pFile)
         return pFile;
      Sleep(250);
   }
   return NULL;
}

static bool ensure_file_is_writable(const char *pFilename)
{
   const int cNumRetries = 8;
   for (int i = 0; i < cNumRetries; i++)
   {
      FILE *pFile = fopen(pFilename, "wb");
      if (pFile)
      {
         fclose(pFile);
         return true;
      }
      Sleep(250);
   }
   return false;
}

static int simple_test(ilzham &lzham_dll, const comp_options &options)
{
   printf("\n");
   printf("LZHAM simple memory to memory compression test\n");

   lzham_compress_params comp_params;
   memset(&comp_params, 0, sizeof(comp_params));
   comp_params.m_struct_size = sizeof(comp_params);
   comp_params.m_dict_size_log2 = options.m_dict_size_log2;
   comp_params.m_level = options.m_comp_level;
   comp_params.m_max_helper_threads = 1;

   lzham_uint8 cmp_buf[1024];
   size_t cmp_len = sizeof(cmp_buf);

   const char *p = "This is a test.This is a test.This is a test.1234567This is a test.This is a test.123456";
   size_t uncomp_len = strlen(p);

   lzham_uint32 comp_adler32 = 0;
   lzham_compress_status_t comp_status = lzham_dll.lzham_compress_memory(&comp_params, cmp_buf, &cmp_len, (const lzham_uint8 *)p, uncomp_len, &comp_adler32);
   if (comp_status != LZHAM_COMP_STATUS_SUCCESS)
   {
      print_error("Compression test failed with status %i!\n", comp_status);
      return EXIT_FAILURE;
   }

   printf("Uncompressed size: %u\nCompressed size: %u\n", (uint)uncomp_len, (uint)cmp_len);

   lzham_decompress_params decomp_params;
   memset(&decomp_params, 0, sizeof(decomp_params));
   decomp_params.m_struct_size = sizeof(decomp_params);
   decomp_params.m_dict_size_log2 = options.m_dict_size_log2;
   if (options.m_compute_adler32_during_decomp)
      decomp_params.m_decompress_flags |= LZHAM_DECOMP_FLAG_COMPUTE_ADLER32;

   lzham_uint8 decomp_buf[1024];
   size_t decomp_size = sizeof(decomp_buf);
   lzham_uint32 decomp_adler32 = 0;
   lzham_decompress_status_t decomp_status = lzham_dll.lzham_decompress_memory(&decomp_params, decomp_buf, &decomp_size, cmp_buf, cmp_len, &decomp_adler32);
   if (decomp_status != LZHAM_DECOMP_STATUS_SUCCESS)
   {
      print_error("Compression test failed with status %i!\n", decomp_status);
      return EXIT_FAILURE;
   }

   if ((comp_adler32 != decomp_adler32) || (decomp_size != uncomp_len) || (memcmp(decomp_buf, p, uncomp_len)))
   {
      print_error("Compression test failed!\n");
      return EXIT_FAILURE;
   }

   printf("Compression test succeeded.\n");

   return EXIT_SUCCESS;
}

static bool read_seed_file(const char *pSeed_filename, lzham_uint32 &num_seed_bytes, const void *&pSeed_bytes, uint dict_size_log2)
{
   num_seed_bytes = 0;
   pSeed_bytes = NULL;

   if (pSeed_filename)
   {
      FILE *pSeed_file = fopen(pSeed_filename, "rb");
      if (!pSeed_file)
      {
         print_error("Unable to open file: %s\n", pSeed_filename);
         return false;
      }

      _fseeki64(pSeed_file, 0, SEEK_END);
      uint64 seed_file_size = _ftelli64(pSeed_file);
      _fseeki64(pSeed_file, 0, SEEK_SET);

      lzham_uint32 seed_size = (lzham_uint32)my_min(seed_file_size, 1ULL << dict_size_log2);
      if (seed_size)
      {
         pSeed_bytes = _aligned_malloc(seed_size, 16);
         if (pSeed_bytes)
         {
            num_seed_bytes = (lzham_uint32)seed_size;

            if (fread((void*)pSeed_bytes, 1, seed_size, pSeed_file) != seed_size)
            {
               print_error("Failed reading file!\n");

               num_seed_bytes = 0;

               _aligned_free((void*)pSeed_bytes);
               pSeed_bytes = NULL;
               fclose(pSeed_file);
               return false;
            }
         }
      }

      fclose(pSeed_file);

      printf("Read File \"%s\", Size: %u bytes\n", pSeed_filename, seed_size);
   }

   return true;
}

static bool compress_file(ilzham &lzham_dll, const char* pSrc_filename, const char *pDst_filename, const comp_options &options, const char *pSeed_filename, float *pTotal_comp_time = NULL)
{
	if (pTotal_comp_time)
		*pTotal_comp_time = 0;

   printf("Testing: Streaming compression\n");

   FILE *pInFile = fopen(pSrc_filename, "rb");
   if (!pInFile)
   {
      print_error("Unable to read file: %s\n", pSrc_filename);
      return false;
   }

   FILE *pOutFile = fopen(pDst_filename, "wb");
   if (!pOutFile)
   {
      print_error("Unable to create file: %s\n", pDst_filename);
      return false;
   }

   _fseeki64(pInFile, 0, SEEK_END);
   uint64 src_file_size = _ftelli64(pInFile);
   _fseeki64(pInFile, 0, SEEK_SET);

   fputc('L', pOutFile);
   fputc('Z', pOutFile);
   fputc('H', pOutFile);
   fputc('0', pOutFile);
   fputc(options.m_dict_size_log2, pOutFile);

   for (uint i = 0; i < 8; i++)
   {
      fputc(static_cast<int>((src_file_size >> (i * 8)) & 0xFF), pOutFile);
   }

   uint64 cmp_file_header_size = _ftelli64(pOutFile);

   const uint cInBufSize = LZHAMTEST_COMP_INPUT_BUFFER_SIZE;
   const uint cOutBufSize = LZHAMTEST_COMP_OUTPUT_BUFFER_SIZE;

   uint8 *in_file_buf = static_cast<uint8*>(_aligned_malloc(cInBufSize, 16));
   uint8 *out_file_buf = static_cast<uint8*>(_aligned_malloc(cOutBufSize, 16));
   if ((!in_file_buf) || (!out_file_buf))
   {
      print_error("Out of memory!\n");
      _aligned_free(in_file_buf);
      _aligned_free(out_file_buf);
      fclose(pInFile);
      fclose(pOutFile);
      return false;
   }

   uint64 src_bytes_left = src_file_size;

   uint in_file_buf_size = 0;
   uint in_file_buf_ofs = 0;

   uint64 total_output_bytes = 0;

   timer_ticks start_time = timer::get_ticks();

   lzham_compress_params params;
   memset(&params, 0, sizeof(params));
   params.m_struct_size = sizeof(lzham_compress_params);
   params.m_dict_size_log2 = options.m_dict_size_log2;
   params.m_max_helper_threads = options.m_max_helper_threads;
   params.m_level = options.m_comp_level;
   if (options.m_extreme_parsing)
      params.m_compress_flags |= LZHAM_COMP_FLAG_EXTREME_PARSING;
   if (options.m_deterministic_parsing)
      params.m_compress_flags |= LZHAM_COMP_FLAG_DETERMINISTIC_PARSING;
   if (options.m_tradeoff_decomp_rate_for_comp_ratio)
      params.m_compress_flags |= LZHAM_COMP_FLAG_TRADEOFF_DECOMPRESSION_RATE_FOR_COMP_RATIO;
  
   params.m_table_update_rate = options.m_table_update_rate;
      
   if (pSeed_filename)
   {
      if (!read_seed_file(pSeed_filename, params.m_num_seed_bytes, params.m_pSeed_bytes, params.m_dict_size_log2))
      {
         _aligned_free(in_file_buf);
         _aligned_free(out_file_buf);
         fclose(pInFile);
         fclose(pOutFile);
         return false;
      }
   }

   timer_ticks init_start_time = timer::get_ticks();
   lzham_compress_state_ptr pComp_state = lzham_dll.lzham_compress_init(&params);
   timer_ticks total_init_time = timer::get_ticks() - init_start_time;

	float total_comp_time = (float)timer::ticks_to_secs(total_init_time);
	
   if ((pComp_state) && (options.m_test_compressor_reinit))
   {
      if (!lzham_dll.lzham_compress_reinit(pComp_state))
      {
         lzham_dll.lzham_compress_deinit(pComp_state);
         pComp_state = NULL;
      }
   }

   if (!pComp_state)
   {
      print_error("Failed initializing compressor!\n");
      _aligned_free(in_file_buf);
      _aligned_free(out_file_buf);
      fclose(pInFile);
      fclose(pOutFile);
      _aligned_free((void*)params.m_pSeed_bytes);
      return false;
   }
   
   printf("lzham_compress_init took %3.3fms\n", timer::ticks_to_secs(total_init_time)*1000.0f);

   lzham_compress_status_t status = LZHAM_COMP_STATUS_FAILED;

   // Performs 1 pass normally, or 2 passes to test compressor reinitialization (with a reinit in between the passes).
   uint total_passes = options.m_test_compressor_reinit ? 2 : 1;
   for (uint pass = 0; pass < total_passes; ++pass)
   {
      for ( ; ; )
      {
         if (src_file_size)
         {
            double total_elapsed_time = timer::ticks_to_secs(timer::get_ticks() - start_time);
            double total_bytes_processed = static_cast<double>(src_file_size - src_bytes_left);
            double comp_rate = (total_elapsed_time > 0.0f) ? total_bytes_processed / total_elapsed_time : 0.0f;

   #ifdef LZHAM_PRINT_OUTPUT_PROGRESS
            for (int i = 0; i < 15; i++)
               printf("\b\b\b\b");
            printf("Progress: %3.1f%%, Bytes Remaining: %3.1fMB, %3.3fMB/sec", (1.0f - (static_cast<float>(src_bytes_left) / src_file_size)) * 100.0f, src_bytes_left / 1048576.0f, comp_rate / (1024.0f * 1024.0f));
            printf("                \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
   #endif
         }

         if (in_file_buf_ofs == in_file_buf_size)
         {
            in_file_buf_size = static_cast<uint>(my_min(cInBufSize, src_bytes_left));

            if (fread(in_file_buf, 1, in_file_buf_size, pInFile) != in_file_buf_size)
            {
               printf("\n");
               print_error("Failure reading from source file!\n");
               _aligned_free(in_file_buf);
               _aligned_free(out_file_buf);
               fclose(pInFile);
               fclose(pOutFile);
               _aligned_free((void*)params.m_pSeed_bytes);
               lzham_dll.lzham_compress_deinit(pComp_state);
               return false;
            }

            src_bytes_left -= in_file_buf_size;

            in_file_buf_ofs = 0;
         }

         uint8 *pIn_bytes = &in_file_buf[in_file_buf_ofs];
         size_t num_in_bytes = in_file_buf_size - in_file_buf_ofs;
         uint8* pOut_bytes = out_file_buf;
         size_t out_num_bytes = cOutBufSize;

			timer_ticks comp_start_time = timer::get_ticks();
         status = lzham_dll.lzham_compress(pComp_state, pIn_bytes, &num_in_bytes, pOut_bytes, &out_num_bytes, src_bytes_left == 0);
			timer_ticks comp_time = timer::get_ticks() - comp_start_time;

			total_comp_time += (float)timer::ticks_to_secs(comp_time);

         if (num_in_bytes)
         {
            in_file_buf_ofs += (uint)num_in_bytes;
            assert(in_file_buf_ofs <= in_file_buf_size);
         }

         if (out_num_bytes)
         {
            if (fwrite(out_file_buf, 1, static_cast<uint>(out_num_bytes), pOutFile) != out_num_bytes)
            {
               printf("\n");
               print_error("Failure writing to destination file!\n");
               _aligned_free(in_file_buf);
               _aligned_free(out_file_buf);
               fclose(pInFile);
               fclose(pOutFile);
               _aligned_free((void*)params.m_pSeed_bytes);
               lzham_dll.lzham_compress_deinit(pComp_state);
               return false;
            }

            total_output_bytes += out_num_bytes;
         }
         
         if (status >= LZHAM_COMP_STATUS_FIRST_SUCCESS_OR_FAILURE_CODE)
            break;
      }

#ifdef LZHAM_PRINT_OUTPUT_PROGRESS
      for (int i = 0; i < 15; i++)
      {
         printf("\b\b\b\b    \b\b\b\b");
      }
#endif

      if ((pass == 0) && (total_passes == 2))
      {
         printf("\n");
         
         uint64 cmp_file_size = _ftelli64(pOutFile);
         printf("Input file size: " QUAD_INT_FMT ", Compressed file size: " QUAD_INT_FMT ", Ratio: %3.2f%%\n", src_file_size, cmp_file_size, src_file_size ? ((1.0f - (static_cast<float>(cmp_file_size) / src_file_size)) * 100.0f) : 0.0f);

         init_start_time = timer::get_ticks();
         if (!lzham_dll.lzham_compress_reinit(pComp_state))
         {
            print_error("Failed reinitializing compressor!\n");
            _aligned_free(in_file_buf);
            _aligned_free(out_file_buf);
            fclose(pInFile);
            fclose(pOutFile);
            _aligned_free((void*)params.m_pSeed_bytes);
            lzham_dll.lzham_compress_deinit(pComp_state);
            return false;
         }
         total_init_time = timer::get_ticks() - init_start_time;
         printf("lzham_compress_reinit took %3.3fms\n", timer::ticks_to_secs(total_init_time)*1000.0f);

         fseek(pInFile, 0, SEEK_SET);
         fseek(pOutFile, static_cast<long>(cmp_file_header_size), SEEK_SET);
         
         src_bytes_left = src_file_size;
         in_file_buf_size = 0;
         in_file_buf_ofs = 0;
         total_output_bytes = 0;
      }
   }

   src_bytes_left += (in_file_buf_size - in_file_buf_ofs);
		
	timer_ticks deinit_start_time = timer::get_ticks();
   uint32 adler32 = lzham_dll.lzham_compress_deinit(pComp_state);
	timer_ticks total_deinit_time = timer::get_ticks() - deinit_start_time;
	
	total_comp_time += (float)timer::ticks_to_secs(total_deinit_time);
	if (pTotal_comp_time)
		*pTotal_comp_time = total_comp_time;

   pComp_state = NULL;

   timer_ticks end_time = timer::get_ticks();
   double total_time = timer::ticks_to_secs(my_max(1, end_time - start_time));

   uint64 cmp_file_size = _ftelli64(pOutFile);

   _aligned_free(in_file_buf);
   in_file_buf = NULL;
   _aligned_free(out_file_buf);
   out_file_buf = NULL;
   _aligned_free((void*)params.m_pSeed_bytes);
   params.m_pSeed_bytes = NULL;

   fclose(pInFile);
   pInFile = NULL;
   fclose(pOutFile);
   pOutFile = NULL;

   if (status != LZHAM_COMP_STATUS_SUCCESS)
   {
      print_error("Compression failed with status %i\n", status);
      return false;
   }

   if (src_bytes_left)
   {
      print_error("Compressor failed to consume entire input file!\n");
      return false;
   }

   printf("Success\n");
   printf("Input file size: " QUAD_INT_FMT ", Compressed file size: " QUAD_INT_FMT ", Ratio: %3.2f%%\n", src_file_size, cmp_file_size, src_file_size ? ((1.0f - (static_cast<float>(cmp_file_size) / src_file_size)) * 100.0f) : 0.0f);
	printf("Compression-only time: %3.6f\nConsumption rate: %9.1f bytes/sec, Emission rate: %9.1f bytes/sec\n", total_comp_time, src_file_size / total_comp_time, cmp_file_size / total_comp_time);
   printf("Total time: %3.6f\nConsumption rate: %9.1f bytes/sec, Emission rate: %9.1f bytes/sec\n", total_time, src_file_size / total_time, cmp_file_size / total_time);
   printf("Input file adler32: 0x%08X\n", adler32);
		
   return true;
}


typedef std::vector< std::string > string_array;


int main_internal(string_array cmd_line, int num_helper_threads, ilzham &lzham_dll)
{
   comp_options options;
   options.m_max_helper_threads = num_helper_threads;


   if (!cmd_line.size())
   {

      return simple_test(lzham_dll, options);
   }

   return -1;


}


int main(int argc, char *argv[])

{
   (void)g_is_debug;


#ifdef LZHAM_64BIT
   printf("LZHAM Codec - x64 Command Line Test App - Compiled %s %s\n", __DATE__, __TIME__);
#else
   //printf("LZHAM Codec - x86 Command Line Test App - Compiled %s %s\n", __DATE__, __TIME__);
#endif

   //printf("Expecting LZHAM DLL Version 0x%04X\n", LZHAM_DLL_VERSION);

#if LZHAM_STATIC_LIB
   lzham_static_lib lzham_lib;
   lzham_lib.load();
   printf("Using static libraries.\n");
#else
   lzham_dll_loader lzham_lib;
   char lzham_dll_filename[MAX_PATH];
   lzham_dll_loader::create_module_path(lzham_dll_filename, MAX_PATH, g_is_debug);
   printf("Dynamically loading DLL \"%s\"\n", lzham_dll_filename);

   HRESULT hres = lzham_lib.load(lzham_dll_filename);
   if (FAILED(hres))
   {
      print_error("Failed loading LZHAM DLL (Status=0x%04X)!\n", (uint)hres);
      return EXIT_FAILURE;
   }
#endif

   // -1 = auto-detection
   int num_helper_threads = -1;

   //printf("Loaded LZHAM DLL version 0x%04X\n\n", lzham_lib.lzham_get_version());

   string_array cmd_line;
   for (int i = 1; i < argc; i++)
   {
      cmd_line.push_back(std::string(argv[i]));
   }

   int exit_status = main_internal(cmd_line, num_helper_threads, lzham_lib);

   lzham_lib.unload();

   return exit_status;
}
