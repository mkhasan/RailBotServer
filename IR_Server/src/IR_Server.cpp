/*
 * IR_Server.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: usrc
 */

#include "Def.h"
#include "CStreamer.h"
#include "CRtspSession.h"

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


const int port = 8555;


ACE_SV_Semaphore_Complex mutex;

IR_Image *pImage = NULL;

int main(int argc , char *argv[])
{
    int c;
    int MasterSocket;
    int ClientSocket;

    int *new_sock;

    struct sockaddr_in ServerAddr , ClientAddr;

    //Create socket
    gettimeofday(&start_time, NULL);


    //////////////////   For Shared memory ///////////////////////////

	if(mutex.open (SEM_KEY_1, ACE_SV_Semaphore_Complex::ACE_CREATE, 1) == -1)
		RB_ERROR_RETURN(("IR_Server: Error in getting mutex \n"), -1);


	ACE_SV_Semaphore_Complex synch;
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

    while( (ClientSocket = accept(MasterSocket, (struct sockaddr *)&ClientAddr, (socklen_t*)&c)) )
	{
		puts("Connection accepted");

		pthread_t sniffer_thread;
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

    close(MasterSocket);

    if (synch.release () == -1)
    	RB_ERROR_RETURN(("IR_Server: Error in releasing synch\n"), -1);


    return 0;

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

    const unsigned long intervalUs = 40000;

    while(!data.Stop) {
    	if(data.StreamingStarted)
    		Streamer.StreamImage(RtspSession.GetStreamID());

    	usleep(intervalUs);
    }

    //Receive a message from client

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
	while(!pData->Stop) {
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
