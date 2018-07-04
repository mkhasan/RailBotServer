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


public:

	static const int SIZE = 204800;

	char data[SIZE];		// Mail Box contains a array of mail items

};

#define PACK_SIZE IR_Image::SIZE
#define RTP_HEADER_SIZE 12
#define PACK_SIZE 4096
#define RTP_PACK_SIZE (PACK_SIZE + RTP_HEADER_SIZE)	//$0rtp_packet_size
#define ENCODE_QUALITY 80

#endif /* COMMON_INCLUDE_IR_IMAGE_H_ */
