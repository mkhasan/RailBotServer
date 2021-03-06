/*
 * IR_Server.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: usrc
 */

#include "Def.h"
#include "CStreamer.h"
#include "CRtspSession.h"

#include "utils.h"

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <signal.h>


using namespace RB_ROBOT_UTILS;

pthread_mutex_t lock;
pthread_cond_t cond;

void *SessionThreadHandler(void *);
void *RtspRequestHandler(void *);
bool IsReqReady(int sockfd);

struct RtspReqData{
	bool StreamingStarted;
	bool Stop;
	CRtspSession *pSession;
	int Client;

};

void Test();
const int port = 8554;


ACE_SV_Semaphore_Complex mutex;
ACE_SV_Semaphore_Complex synch;

int MasterSocket;

IR_Image *pImage = NULL;

static bool quit = false;

pthread_t sniffer_thread;
pthread_t req_handler;

void CatchSignal(int sig);

Callback *callback = NULL;



int main(int argc , char *argv[])
{
    int c;

    int ClientSocket;

    int *new_sock;

    struct sockaddr_in ServerAddr , ClientAddr;

	signal(SIGTERM, CatchSignal);
	signal(SIGINT, CatchSignal);		// caught in a different way for testing
	signal(SIGHUP, CatchSignal);
	signal(SIGKILL, CatchSignal);
	signal(SIGTSTP, CatchSignal);


    //Create socket
    //gettimeofday(&start_time, NULL);

    /*
    callback = new Callback;
    ACE_LOG_MSG->set_flags(ACE_Log_Msg::MSG_CALLBACK);
    ACE_LOG_MSG->clr_flags(ACE_Log_Msg::STDERR);
    ACE_LOG_MSG->msg_callback(callback);

    */
    // now.tv_sec-start_time.tv_sec, now.tv_usec)



    //////////////////   For Shared memory ///////////////////////////

	if(mutex.open (SEM_KEY_1, ACE_SV_Semaphore_Complex::ACE_CREATE, 1) == -1)
		RB_ERROR_RETURN(("IR_Server: Error in getting mutex \n"), -1);



	if(synch.open (SEM_KEY_2,
						  ACE_SV_Semaphore_Complex::ACE_CREATE,
						  1) == -1)
		RB_ERROR_RETURN(("IR_Server: Error in getting sync \n"), -1);


	ACE_Shared_Memory_SV shm_client (SHM_KEY, sizeof (IR_Image));

	char *shm = (char *) shm_client.malloc ();

	if (shm == 0)
		RB_ERROR_RETURN(("IR_Server: Error in connecting IR_Image \n"), -1);


	pImage = new (shm) IR_Image;

	if (synch.acquire () == -1)
		RB_ERROR_RETURN(("IR_Server: Error in acquiring synch\n"), -1);


	//////////////////   For Shared memory ///////////////////////////

    MasterSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (MasterSocket == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port = htons( port );

    //Bind
    if( bind(MasterSocket,(struct sockaddr *)&ServerAddr , sizeof(ServerAddr)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");





    //printf("%s%Lu.%Lu \n", "Now ", now.tv_sec, now.tv_usec);


    //printf("%ld : Received cmd %s \n", time(NULL), "Test");


    //Listen
    listen(MasterSocket , 5);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);


    //Accept and incoming connection
    /*puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);*/

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);


    while(quit == false)
	{
    	ClientSocket = accept(MasterSocket, (struct sockaddr *)&ClientAddr, (socklen_t*)&c);

		puts("Connection accepted");

		new_sock = (int *)malloc(1);
		*new_sock = ClientSocket;


		if( pthread_create( &sniffer_thread , NULL ,  SessionThreadHandler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}

		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL); // was commented before
		puts("Handler assigned");
	}


    pthread_join(sniffer_thread,NULL);

    int ret = close(MasterSocket);

    RB_INFO("ret value of close is %d \n", ret);

    if (synch.release () == -1)
    	RB_ERROR_RETURN(("IR_Server: Error in releasing synch\n"), -1);


    return 0;


    delete callback;
}


void *SessionThreadHandler(void *socket_desc)
{
    //Get the socket descriptor


    int Client = *(int*)socket_desc;

    ImageProcessor imgPro;



    int res;
    CStreamer Streamer(Client, &imgPro);
    CRtspSession RtspSession(Client, &Streamer);
    int StreamID = 0;


    int read_size;
    char *message , client_message[2000];

    RtspReqData data;
    data.StreamingStarted = false;
    data.Stop= false;
    data.pSession = &RtspSession;
    data.Client = Client;


    pthread_t req_handler;

    if( pthread_create( &req_handler , NULL ,  RtspRequestHandler , (void*) &data) < 0)	{
		perror("could not create thread");
		return NULL;
	}


    const unsigned long intervalUs = ((1000.0+EPSILON)/FPS)*1000;




    ACE_Time_Value twakeup, tinc, tsleep, t1;

    tinc.set(0, intervalUs);

    twakeup = ACE_OS::gettimeofday();

    while(!data.Stop && quit == false) {

    	twakeup += tinc;

    	if(data.StreamingStarted) {
    		Streamer.StreamImage(RtspSession.GetStreamID());
    		//printf("(%Lu %Lu) \n", twakeup.sec(), twakeup.usec());
    	}

    	//usleep(intervalUs);

    	t1 = ACE_OS::gettimeofday();

    	tsleep= twakeup - t1;

        if (tsleep > ACE_Time_Value::zero)
        	ACE_OS::sleep(tsleep);
        else {

        	RB_INFO("No time to sleep enough !!! \n");
        	usleep(intervalUs/2);
        	twakeup = ACE_OS::gettimeofday();
        }



    	//RB_INFO("Next loop \n");
    }

    //Receive a message from client

    pthread_join(req_handler,NULL);

	close(Client);

    pthread_exit(NULL);

}



void *RtspRequestHandler(void *userData)
{
	RtspReqData * pData = (RtspReqData *) userData;

	const unsigned long sleepUs = 100000;	// 100 ms

	int i, length, flags;

	char RecvBuf[10000];

	static int first = 0;

	/*
	 * Example req:
	 *
	 * [3:290060] req: OPTIONS rtsp://127.0.0.1:8555/mjpeg/1/ RTSP/1.0
		CSeq: 2
		User-Agent: LibVLC/2.1.6 (LIVE555 Streaming Media v2014.01.13)

	 *
	 */
	while(!pData->Stop && quit == false) {
		if(IsReqReady(pData->Client)) {
					            //written = pBuffer->Receive(sockfd);

			flags = fcntl(pData->Client, F_GETFL, 0);
			fcntl(pData->Client, F_SETFL, flags | O_NONBLOCK);



			length = read(pData->Client, RecvBuf, sizeof(RecvBuf));

			if(first) {
				RB_DEBUG("req: %s len: %d \n", RecvBuf, length);
				first = 0;
			}

			if(length) {
                if ((RecvBuf[0] == 'O') || (RecvBuf[0] == 'D') || (RecvBuf[0] == 'S') || (RecvBuf[0] == 'P') || (RecvBuf[0] == 'T'))
                {
                    RTSP_CMD_TYPES C = pData->pSession->Handle_RtspRequest(RecvBuf,length);
                    if (C == RTSP_PLAY)     pData->StreamingStarted = true; else if (C == RTSP_TEARDOWN) pData->Stop = true;

                    //time(&now);
                    RB_DEBUG("Received cmd %d \n", C);


                };


			}



		}

		usleep(sleepUs);

	}

	pData->Stop = true;

    return NULL;
}

bool IsReqReady(int sockfd)
{

    /// Got here because iSelectReturn > 0 thus data available on at least one descriptor
    // Is our socket in the return list of readable sockets
    bool             res;
    fd_set          sready;
    struct timeval  nowait;

    FD_ZERO(&sready);
    FD_SET((unsigned int)sockfd,&sready);
    //bzero((char *)&nowait,sizeof(nowait));
    memset((char *)&nowait,0,sizeof(nowait));

    res = select(sockfd+1,&sready,NULL,NULL,&nowait);
    if( FD_ISSET(sockfd,&sready) )
        res = true;
    else
        res = false;


    return res;

}

void CatchSignal(int sig)
{



	RB_INFO("Signal %d caught \n", sig);

	quit = true;





    //close(MasterSocket);

    if (synch.release () == -1)
    	RB_ERROR_RETURN(("CatchSignal: Error in releasing synch\n"), );

    if(sig == 20) {
    	delete callback;
    	exit(1);
    }


}
