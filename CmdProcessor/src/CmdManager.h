/*
 * CmdManager.h
 *
 *  Created on: Jul 23, 2018
 *      Author: usrc
 */


#include "CmdProcessor.h"

#include <mosquittopp.h>
#include <pthread.h>


class CmdManager : public mosqpp::mosquittopp
{



private:
	CmdManager();
	~CmdManager();
	CmdManager(CmdManager & copy);
	CmdManager & operator=(CmdManager & copy);

	static pthread_mutex_t lock;
	pthread_t threadT;

	bool connected;
	bool quit;

	static char curCmd[CMD_LEN+1];

	static void *CommandThreadHandler( void *ptr );

	static void GetCmd(char *_curCmd);

public:

	static void SetCmd(char *_curCmd);




	static CmdManager* Instnace();
	int connect(const char *host, int port);
	int disconnect();
	void on_connect(int rc);
	void on_subscribe(uint16_t mid, int qos_count, const uint8_t *grandted_qos);
	void on_message(const struct mosquitto_message *message);
	bool IsConnected();






private:



};

