/*
 * utils.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: usrc
 */



#include "utils.h"


#include <stdio.h>
#include <memory.h>
#include <string.h>



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

#define print_error printf

using namespace RB_ROBOT_UTILS;

Squeezer::Squeezer() : isInitialized(false) {

}

int Squeezer::Initialize() {
	if (isInitialized)
		return 0;

#ifdef LZHAM_64BIT
   printf("LZHAM Codec - x64 Command Line Test App - Compiled %s %s\n", __DATE__, __TIME__);
#else
   //printf("LZHAM Codec - x86 Command Line Test App - Compiled %s %s\n", __DATE__, __TIME__);
#endif

   //printf("Expecting LZHAM DLL Version 0x%04X\n", LZHAM_DLL_VERSION);

#if LZHAM_STATIC_LIB

   lzham_lib.load();
   printf("Using static libraries.\n");

#else

   char lzham_dll_filename[MAX_PATH];
   lzham_dll_loader::create_module_path(lzham_dll_filename, MAX_PATH, g_is_debug);
   printf("Dynamically loading DLL \"%s\"\n", lzham_dll_filename);

   HRESULT hres = lzham_lib.load(lzham_dll_filename);
   if (FAILED(hres))
   {
      print_error("Failed loading LZHAM DLL (Status=0x%04X)!\n", (uint)hres);
	  return this->MODULE_NOT_FOUND;
   }


#endif

   isInitialized = true;
   return 0;


}

void Squeezer::Finalize() {
	if (isInitialized == false)
		return;

	lzham_lib.unload();
	isInitialized = false;
}
Squeezer::~Squeezer() {
	Finalize();

}

Squeezer * Squeezer::Instance() {
	static Squeezer squeezer;
	return &squeezer;
}

void Squeezer::Test() {

	lzham_compress_params comp_params;
	int num_helper_threads = -1;

	comp_options options;
	options.m_max_helper_threads = num_helper_threads;


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
	   lzham_compress_status_t comp_status = lzham_lib.lzham_compress_memory(&comp_params, cmp_buf, &cmp_len, (const lzham_uint8 *)p, uncomp_len, &comp_adler32);
	   if (comp_status != LZHAM_COMP_STATUS_SUCCESS)
	   {
	      print_error("Compression test failed with status %i!\n", comp_status);
	      return ;
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
	   lzham_decompress_status_t decomp_status = lzham_lib.lzham_decompress_memory(&decomp_params, decomp_buf, &decomp_size, cmp_buf, cmp_len, &decomp_adler32);
	   if (decomp_status != LZHAM_DECOMP_STATUS_SUCCESS)
	   {
	      print_error("Compression test failed with status %i!\n", decomp_status);
	      return ;
	   }

	   if ((comp_adler32 != decomp_adler32) || (decomp_size != uncomp_len) || (memcmp(decomp_buf, p, uncomp_len)))
	   {
	      print_error("Compression test failed!\n");
	      return ;
	   }

	   printf("Compression test succeeded.\n");

}

int Squeezer::Compress(lzham_uint8 *dest, size_t * pDestLength, const lzham_uint8 *src, size_t srcLength) {

	lzham_compress_params comp_params;
	int num_helper_threads = -1;

	comp_options options;
	options.m_max_helper_threads = num_helper_threads;


	memset(&comp_params, 0, sizeof(comp_params));
	comp_params.m_struct_size = sizeof(comp_params);
	comp_params.m_dict_size_log2 = options.m_dict_size_log2;
	comp_params.m_level = options.m_comp_level;
	comp_params.m_max_helper_threads = 1;

	lzham_uint8 cmp_buf[1024];
	size_t cmp_len = sizeof(cmp_buf);

//	const char *p = "This is a test.This is a test.This is a test.1234567This is a test.This is a test.123456";
//	size_t uncomp_len = strlen(p);

	lzham_uint32 comp_adler32 = 0;
	lzham_compress_status_t comp_status = lzham_lib.lzham_compress_memory(&comp_params, dest, pDestLength, src, srcLength, &comp_adler32);
	if (comp_status != LZHAM_COMP_STATUS_SUCCESS)
	{
	  print_error("Compression test failed with status %i!\n", comp_status);
	  return -1;
	}

	printf("Uncompressed size: %u\nCompressed size: %u\n", (uint)srcLength, (uint)*pDestLength);

	return 0;

	/*
	lzham_decompress_params decomp_params;
	memset(&decomp_params, 0, sizeof(decomp_params));
	decomp_params.m_struct_size = sizeof(decomp_params);
	decomp_params.m_dict_size_log2 = options.m_dict_size_log2;
	if (options.m_compute_adler32_during_decomp)
	  decomp_params.m_decompress_flags |= LZHAM_DECOMP_FLAG_COMPUTE_ADLER32;

	lzham_uint8 decomp_buf[1024];
	size_t decomp_size = sizeof(decomp_buf);
	lzham_uint32 decomp_adler32 = 0;
	lzham_decompress_status_t decomp_status = lzham_lib.lzham_decompress_memory(&decomp_params, decomp_buf, &decomp_size, cmp_buf, cmp_len, &decomp_adler32);
	if (decomp_status != LZHAM_DECOMP_STATUS_SUCCESS)
	{
	  print_error("Compression test failed with status %i!\n", decomp_status);
	  return ;
	}

	if ((comp_adler32 != decomp_adler32) || (decomp_size != uncomp_len) || (memcmp(decomp_buf, p, uncomp_len)))
	{
	  print_error("Compression test failed!\n");
	  return ;
	}

	printf("Compression test succeeded.\n");
	*/


}

int Squeezer::DeCompress(lzham_uint8 *dest, size_t * pDestLength, const lzham_uint8 *src, size_t srcLength) {
	lzham_compress_params comp_params;
	int num_helper_threads = -1;

	comp_options options;
	options.m_max_helper_threads = num_helper_threads;

	lzham_decompress_params decomp_params;
	memset(&decomp_params, 0, sizeof(decomp_params));
	decomp_params.m_struct_size = sizeof(decomp_params);
	decomp_params.m_dict_size_log2 = options.m_dict_size_log2;
	if (options.m_compute_adler32_during_decomp)
	  decomp_params.m_decompress_flags |= LZHAM_DECOMP_FLAG_COMPUTE_ADLER32;

	lzham_uint8 decomp_buf[1024];
	size_t decomp_size = sizeof(decomp_buf);
	lzham_uint32 decomp_adler32 = 0;
	lzham_decompress_status_t decomp_status = lzham_lib.lzham_decompress_memory(&decomp_params, dest, pDestLength, src, srcLength, &decomp_adler32);
	if (decomp_status != LZHAM_DECOMP_STATUS_SUCCESS)
	{
	  print_error("Compression test failed with status %i!\n", decomp_status);
	  return -1;
	}


	printf("Compression test succeeded.\n");

	return 0;



}
