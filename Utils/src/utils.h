/*
 * util.h
 *
 *  Created on: Jul 9, 2018
 *      Author: usrc
 */

#ifndef UTILS_SRC_UTILS_H_
#define UTILS_SRC_UTILS_H_


#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))


#if defined(WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#define LZHAM_USE_LZHAM_DLL 1
#else 
	#define Sleep(ms) usleep(ms*1000)
	#define _aligned_malloc(size, alignment) memalign(alignment, size)
	#define _aligned_free free
	//#define fopen fopen64		// uncommenting this line does not allow cout to be use used because cout internally use ::fopen
	#define _fseeki64 fseeko64
	#define _ftelli64 ftello64
#endif


#if LZHAM_USE_LZHAM_DLL
#include "lzham_dynamic_lib.h"
#else
#include "lzham_static_lib.h"
#endif

namespace RB_ROBOT_UTILS {

class Squeezer {

private:

#if LZHAM_STATIC_LIB
   lzham_static_lib lzham_lib;

#else
   lzham_dll_loader lzham_lib;
#endif

public:
	const int LZHAM_ERROR = -1;
	const int NOT_INSTIALIZED = -2;
	const int MODULE_NOT_FOUND = -3;
	const int SUCCESS = 0;
private:
	bool isInitialized;

	Squeezer();
	~Squeezer();



	Squeezer(Squeezer & copy);

	Squeezer operator=(Squeezer & copy);

public:


	int Initialize();
	void Finalize();

	int Compress(lzham_uint8 *dest, size_t * pDestLength, const lzham_uint8 *src, size_t srcLength);
	int DeCompress(lzham_uint8 *dest, size_t * pDestLength, const lzham_uint8 *src, size_t srcLength);

	static Squeezer * Instance();
	void Test();

	bool IsInitialized();
};



}



#endif /* UTILS_SRC_UTILS_H_ */
