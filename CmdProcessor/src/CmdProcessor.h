/*
 * CmdProcessor.h
 *
 *  Created on: Jul 20, 2018
 *      Author: usrc
 */

#ifndef CMDPROCESSOR_SRC_CMDPROCESSOR_H_
#define CMDPROCESSOR_SRC_CMDPROCESSOR_H_

#define BUFLEN 1024
#define TRUE 1
#define FALSE 0

enum {CMD_NONE, CMD_FORWARD};

#define CMD_LEN 16
#define sprintf_s sprintf


void *CommandThreadHandler( void *ptr );
void SetCmd(const char * cmd);
void GetCmd(char * cmd);



#endif /* CMDPROCESSOR_SRC_CMDPROCESSOR_H_ */
