/*
 * CmdProcessor.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: usrc
 */





#include "CmdProcessor.h"
#include "CmdManager.h"

#include "Def.h"




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


	sprintf(cmd, "%c5000000%c000000000", 0x02, 0x03);
	if (pthread_mutex_init(&lock, NULL) != 0) {

		RB_ERROR("mutex init failed\n");
		return 1;
	}


	////////////  initializing mosquitto ///////////////

	mosqpp::lib_init();

	CmdManager *cmdManager = CmdManager::Instnace();
	int ret = cmdManager->connect("localhost", 1883);
	RB_ASSERT(ret == 0);

	pthread_t threadT;
	pthread_t mosquittoT;


	if( pthread_create( &threadT , NULL ,  CommandThreadHandler , NULL) < 0)
	{
		RB_ERROR("could not create thread");
		return 1;
	}

	if( pthread_create( &mosquittoT , NULL ,  MosquittoThreadHandler , NULL) < 0)
	{
		RB_ERROR("could not create thread");
		return 1;
	}




	char key='0';

	char curCmd[100];

	const char* speed1 = "0020";
	const char* dist = "0005";
	static int tiltAngle = 0;
	static int panAngle = 0;
	const int ANGLE_STEP = 20;


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

				sprintf_s(curCmd, "%c10%s0%c000000000", 0x02, "0000", 0x03);
				SetCmd(curCmd);

				break;

			case 'u':

				tiltAngle += ANGLE_STEP;

				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';
				curCmd[CMD_LEN] = 0;

				sprintf_s(curCmd, "%c31%4d0%c000000000", 0x02, tiltAngle, 0x03);
				SetCmd(curCmd);

				break;

			case 'd':

				tiltAngle -= ANGLE_STEP;

				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';
				curCmd[CMD_LEN] = 0;

				sprintf_s(curCmd, "%c31%4d0%c000000000", 0x02, tiltAngle, 0x03);
				SetCmd(curCmd);

				break;


			case 'r':

				panAngle += ANGLE_STEP;

				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';
				curCmd[CMD_LEN] = 0;

				sprintf_s(curCmd, "%c32%4d0%c000000000", 0x02, panAngle, 0x03);
				SetCmd(curCmd);

				break;

			case 'l':

				panAngle -= ANGLE_STEP;

				for (int i = 0; i < CMD_LEN; i++)
					curCmd[i] = '0';
				curCmd[CMD_LEN] = 0;

				sprintf_s(curCmd, "%c32%4d0%c000000000", 0x02, panAngle, 0x03);
				SetCmd(curCmd);

				break;




			case 'q':

				break;

		}
	}


	quit = true;

	pthread_join(threadT,NULL);

	pthread_join(mosquittoT, NULL);

	pthread_mutex_destroy(&lock);

	mosqpp::lib_cleanup();

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
	si_other.sin_port = htons(CTRL_PORT);

	RB_DEBUG("target ip %s, targbet port %d \n", controlIP.c_str(), CTRL_PORT);
	if (inet_aton(controlIP.c_str() , &si_other.sin_addr) == 0)	{

		RB_ERROR("CommandThreadHandler: inet_aton() failed \n");
		exit(1);
	}


	//start communication

	int count = 0;
	char curCmd[100];

	pthread_t threadT;

	receiver_info receiverInfo;
	receiverInfo.s = s;
	receiverInfo.si_other = si_other;

	pthread_t receiverT = NULL;




	if( pthread_create( &receiverT , NULL ,  Receiver , (void *) &receiverInfo) < 0)
	{
		RB_ERROR("could not create thread");
		exit(1);
	}





	while (quit == false)
	{
		//printf("Enter message : ");




		//send the message
		for (int i = 0; i < 100; i++)
			curCmd[i] = 0;

		GetCmd(message);

		//strcpy(message, curCmd);

		if(message[0] == 0 || message[1] != '5') {
			RB_DEBUG("Sending cmd %c%c%c%c%c%c \n", message[1], message[2], message[3], message[4], message[5], message[6]);


			if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1) {

				RB_ERROR("CommandThreadHandler: sendto() failed \n");
				exit(1);
			}

		}
		Sleep(500);

	}


	if(receiverT != NULL)
		pthread_cancel(receiverT);

	close(s);



	return 0;
}


void *MosquittoThreadHandler( void *ptr ) {
	int rc;
	CmdManager * p = CmdManager::Instnace();


	while(!quit) {
		rc = p->loop();
		if(rc) {
			RB_DEBUG("MosquittoThreadHandler: p not connected \n");
			p->reconnect();
		}

		RB_DEBUG("looping \n");
	}

	RB_DEBUG("MosquittoThreadHandler: Terminating ...\n");
	return NULL;
}

void *Receiver( void *ptr ) {
	receiver_info * p = (receiver_info *) ptr;


	char buf[BUFLEN];
	int slen = sizeof(p->si_other);
	memset(buf, '\0', BUFLEN);



	//try to receive some data, this is a blocking call
	while(!quit) {
		RB_DEBUG("try to receive some data, this is a blocking call \n");
		if (recvfrom(p->s, buf, BUFLEN, 0, (struct sockaddr *) &p->si_other, (socklen_t *)&slen) == -1) {

			RB_ERROR("Receiver: recvfrom() failed \n");
			exit(1);
		}

		buf[CMD_LEN] = 0;
		CmdManager::SetCmd(buf);
		puts(buf);
		Sleep(50);
	}







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
		_cmd[CMD_LEN] = cmd[CMD_LEN] = 0;

	}


	pthread_mutex_unlock(&lock);


}


void SetCmd(const char *_cmd) {


	pthread_mutex_lock(&lock);

	for (int i = 0; i < CMD_LEN; i++)
		cmd[i] = _cmd[i];


	pthread_mutex_unlock(&lock);


}

