/*
 * IR_Image.h
 *
 *  Created on: Jul 3, 2018
 *      Author: usrc
 */

#ifndef COMMON_INCLUDE_IR_IMAGE_H_
#define COMMON_INCLUDE_IR_IMAGE_H_

#include "Def.h"

#include "ace/Log_Msg.h"
#include "ace/SV_Semaphore_Complex.h"
#include "ace/Shared_Memory_SV.h"


class IR_Image
{

	static const int SIZE = 204800;
public:

	char data[SIZE];		// Mail Box contains a array of mail items

};



#endif /* COMMON_INCLUDE_IR_IMAGE_H_ */
