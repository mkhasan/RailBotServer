/*
 * CmdProcessor.h
 *
 *  Created on: Jul 20, 2018
 *      Author: usrc
 */

#ifndef CMDPROCESSOR_SRC_CMDPROCESSOR_H_
#define CMDPROCESSOR_SRC_CMDPROCESSOR_H_

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>

#define BUFLEN 1024
#define TRUE 1
#define FALSE 0

enum {CMD_NONE, CMD_FORWARD};

#define CMD_LEN 16
#define sprintf_s sprintf

struct receiver_info {
	int s;
	struct sockaddr_in si_other;
};


void *CommandThreadHandler( void *ptr );
void *Receiver( void *ptr );
void SetCmd(const char * cmd);
void GetCmd(char * cmd);




#endif /* CMDPROCESSOR_SRC_CMDPROCESSOR_H_ */
