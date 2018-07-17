/*
 * IR_Image.h
 *
 *  Created on: Jul 3, 2018
 *      Author: usrc
 */

#ifndef COMMON_INCLUDE_IR_IMAGE_H_
#define COMMON_INCLUDE_IR_IMAGE_H_

#include "Def.h"


#include "ace/SV_Semaphore_Complex.h"
#include "ace/Shared_Memory_SV.h"


class IR_Image
{


public:

	static const int SIZE = 204800;

	char data[SIZE];		// Mail Box contains a array of mail items
	unsigned short width;
	unsigned short height;
	unsigned char pixelSize;


};


#endif /* COMMON_INCLUDE_IR_IMAGE_H_ */
