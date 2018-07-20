/*
 * CmdProcessor.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: usrc
 */




#include "CmdProcessor.h"

#include "Def.h"




#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>


#include <iostream>

using namespace std;

static string controlIP = CTRL_IP;
static bool quit = false;
pthread_mutex_t lock;
static char cmd[100];



int main(int argc, char *argv[]) {

	if(argc >= 2)
		controlIP = argv[1];


	if (pthread_mutex_init(&lock, NULL) != 0) {

		RB_ERROR("mutex init failed\n");
		return 1;
	}

	pthread_t threadT;


	if( pthread_create( &threadT , NULL ,  CommandThreadHandler , NULL) < 0)
	{
		RB_ERROR("could not create thread");
		return 1;
	}


	char key='0';

	char curCmd[100];

	const char* speed1 = "0010";
	const char* dist = "0005";

	while (key != 'q') {
		scanf("%c", &key);
		switch (key) {
			case 'v':
				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';

				sprintf_s(curCmd, "%c20%s0%c000000000", 0x02, speed1, 0x03);
				SetCmd(curCmd);


				break;

			case 'f':
				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';

				sprintf_s(curCmd, "%c11%s0%c000000000", 0x02, dist, 0x03);
				SetCmd(curCmd);

				break;


			case 'b':
				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';

				sprintf_s(curCmd, "%c12%s0%c000000000", 0x02, dist, 0x03);
				SetCmd(curCmd);

				break;

			case 's':
				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';

				sprintf_s(curCmd, "%c10%s0%c000000000", 0x02, 0, 0x03);
				SetCmd(curCmd);

				break;


			case 'q':

				break;

		}
	}


	quit = true;

	pthread_join(threadT,NULL);

	pthread_mutex_destroy(&lock);

	return 0;
}



void *CommandThreadHandler( void *ptr ) {

	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		RB_ERROR("CommandThreadHandler: Error in creating socket \n");
		exit(1);
	}

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(CTROL_PORT);

	if (inet_aton(controlIP.c_str() , &si_other.sin_addr) == 0)	{

		RB_ERROR("CommandThreadHandler: inet_aton() failed \n");
		exit(1);
	}


	//start communication

	int count = 0;
	char curCmd[100];
	while (quit == false)
	{
		//printf("Enter message : ");




		//send the message
		for (int i = 0; i < 100; i++)
			curCmd[i] = 0;

		GetCmd(curCmd);

		strcpy(message, curCmd);

		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1) {

			RB_ERROR("CommandThreadHandler: sendto() failed \n");
			exit(1);
		}



		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *)&slen) == -1) {

			RB_ERROR("CommandThreadHandler: recvfrom() failed \n");
			exit(1);
		}




		puts(buf);


		Sleep(500);
	}

	close(s);


	return 0;
}

void GetCmd(char *_cmd) {

	DWORD dwWaitResult;

	char message[BUFLEN];
	sprintf(message, "%c5000000%c000000000", 0x02, 0x03); //s type5 cmd0 value0000 cs0 e

	pthread_mutex_lock(&lock);

	if (cmd[0] == 0) {
		_cmd[0] = 0;


	}

	else {

		for (int i = 0; i < CMD_LEN; i++)
			_cmd[i] = cmd[i];

		for (int i = 0; i < CMD_LEN; i++)
			cmd[i] = message[i];

	}


	pthread_mutex_unlock(&lock);


}


void SetCmd(const char *_cmd) {


	pthread_mutex_lock(&lock);

	for (int i = 0; i < CMD_LEN; i++)
		cmd[i] = _cmd[i];


	pthread_mutex_unlock(&lock);


}

