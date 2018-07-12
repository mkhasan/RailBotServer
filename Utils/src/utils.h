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



#define Sleep(ms) usleep(ms*1000)
#define _aligned_malloc(size, alignment) memalign(alignment, size)
#define _aligned_free free
#define fopen fopen64
#define _fseeki64 fseeko64
#define _ftelli64 ftello64


#include "lzham_static_lib.h"


namespace RB_ROBOT_UTILS {

class Squeezer {

private:

#if LZHAM_STATIC_LIB
   lzham_static_lib lzham_lib;

#else
   lzham_dll_loader lzham_lib;
#endif


	Squeezer();
	~Squeezer();

	Squeezer(Squeezer & copy);

	Squeezer operator=(Squeezer & copy);

public:
	int Compress(char *dest, int & destLength, const char *src, int srcLength);
	int DeCompress(char *dest, int & destLength, const char *src, int srcLength);

	static Squeezer * Instance();
	void Test();
};



}



#endif /* UTILS_SRC_UTILS_H_ */
