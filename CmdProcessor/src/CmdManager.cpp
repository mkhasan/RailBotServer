/*
 * CmdManager.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: usrc
 */


#include "CmdManager.h"

#include "Def.h"

pthread_mutex_t CmdManager::lock;
char CmdManager::curCmd[CMD_LEN+1];


CmdManager::CmdManager() : mosquittopp("CMD_MANAGER"), connected(false), quit(false), threadT(NULL) {


	int ret = pthread_mutex_init(&lock, NULL);

	RB_ASSERT(ret == 0);
}

CmdManager::~CmdManager() {
	quit = false;
	if(threadT != NULL)
		pthread_join(threadT, NULL);

	pthread_mutex_destroy(&lock);
}

int CmdManager::connect(const char *host, int port) {
	int keepalive = 60;
	mosquittopp::connect(host, port, keepalive);


	if( pthread_create( &threadT , NULL ,  CommandThreadHandler , (void *) this) < 0)	{
		RB_ERROR("could not create thread \n");
		return -1;
	}


	return 0;
}

int CmdManager::disconnect() {
	connected = false;
	quit = true;
	if(threadT != NULL)
		pthread_join(threadT, NULL);

	threadT = NULL;

	return mosquittopp::disconnect();

}

void CmdManager::on_connect(int rc) {
	RB_DEBUG("Connected with code %d \n", rc);

	if(rc == 0) {
		connected = true;
		subscribe(NULL, FROM_CLIENT);
	}
}

void CmdManager::on_subscribe(uint16_t mid, int qos_count, const uint8_t *grandted_qos) {
	RB_DEBUG("Sbuscribe succeeded \n");
}

void CmdManager::on_message(const mosquitto_message * message) {

	char buf[CMD_LEN+1];
	const char *p;
	int i;
	if(!strcmp(message->topic, FROM_CLIENT)) {
		p = (char *) message->payload;
		for(i=0; i<CMD_LEN; i++) {

			buf[i] = p[i];
			if(buf[i] == 0)
				break;
		}

		buf[CMD_LEN] = 0;

		::SetCmd(buf);

	}
}

void *CmdManager::CommandThreadHandler(void *ptr) {
	CmdManager *p = (CmdManager *) ptr;
	char msg[CMD_LEN+1];
	while(!p->quit) {

		if(p->connected) {
			GetCmd(msg);
			if(msg[0]) {
				p->publish(NULL, TO_CLIENT, strlen(msg), (uint8_t *) msg);
			}
		}
		Sleep(500);

	}
}

void CmdManager::GetCmd(char * _curCmd) {
	pthread_mutex_lock(&lock);

	for(int i=0; i<CMD_LEN; i++)
		_curCmd[i] = curCmd[i];

	_curCmd[CMD_LEN] = 0;

	curCmd[0] = 0;
	pthread_mutex_unlock(&lock);
}

void CmdManager::SetCmd(char * _curCmd) {
	pthread_mutex_lock(&lock);

	for(int i=0; i<CMD_LEN; i++)
		curCmd[i] = _curCmd[i];

	curCmd[CMD_LEN] = 0;


	pthread_mutex_unlock(&lock);
}
