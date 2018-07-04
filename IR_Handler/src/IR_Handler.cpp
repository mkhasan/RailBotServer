/*
 * main.c
 *
 *  Created on: Jan 10, 2017
 *      Author: usrc
 */

#include "IR_Image.h"

#include "ir_viewer.h"
#include "Socket.h"
#include "CircularBuffer.h"



#include <stdio.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>


struct Viewer *pIR_Viewer;

using std::cerr;
using std::endl;




const char * hostIP = "143.248.204.35";

static void CatchSignal(int sig);

SDL_Surface* screen;
SDL_mutex       *screen_mutex;

ACE_SV_Semaphore_Complex mutex;
IR_Image * pImage = NULL;

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);



int main(int argc, char **argv) {
	int ret = 0;


	signal(SIGTERM, CatchSignal);
	//signal(SIGINT, CatchSignal);		// caught in a different way for testing
	signal(SIGHUP, CatchSignal);
	signal(SIGKILL, CatchSignal);
	signal(SIGTSTP, CatchSignal);


	//////////////////   For Shared memory ///////////////////////////


	if(mutex.open (SEM_KEY_1, ACE_SV_Semaphore_Complex::ACE_CREATE, 1) == -1)
		RB_ERROR_RETURN(("Error in getting mutex \n"), -1);


	ACE_SV_Semaphore_Complex synch;
	if(synch.open (SEM_KEY_2,
						  ACE_SV_Semaphore_Complex::ACE_CREATE,
						  1) == -1)
		RB_ERROR_RETURN(("Error in getting sync \n"), -1);


	ACE_Shared_Memory_SV shm_server (SHM_KEY,
								   sizeof (IR_Image),
								   ACE_Shared_Memory_SV::ACE_CREATE);
	char *shm = (char *) shm_server.malloc ();

	if (shm == 0)
		RB_ERROR_RETURN(("Error in allocationg shared mem \n"), -1);

	pImage = new (shm) IR_Image;

	//////////////////   For Shared memory ///////////////////////////

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "SDL_Init() Failed: " << SDL_GetError() << endl;
		exit(1);
	}

	 // Set the video mode

	 screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	 screen_mutex = SDL_CreateMutex();
	 if (screen == NULL)
	 {
	  cerr << "SDL_SetVideoMode() Failed: " << SDL_GetError() << endl;
	  exit(1);
	 }


	ret = jni_ir_viewer_init((void *)NULL, (void *)NULL, hostIP);



	if (ret != 0 ) {
		cerr << "viewer init error " << ret <<  endl;
		exit(1);
	}

	usleep(100000);

	ret = Connect(pIR_Viewer);



	if (ret != 0 ) {
		cerr << "viewer connect error " << ret <<  endl;
		exit(1);
	}

	usleep(100000);






	ret = Play(pIR_Viewer);



	if (ret != 0 ) {
		cerr << "viewer play error " << ret <<  endl;
		exit(1);
	}





/*
	SDL_WM_SetCaption("SDL Tutorial", "SDL Tutorial");

	// Load the image
	SDL_Surface* image;
	image = SDL_LoadBMP("sails.bmp");
	if (image == NULL)
	{
		cerr << "SDL_LoadBMP() Failed: " << SDL_GetError() << endl;
		exit(1);
	}

	*/


	SDL_Event event;
	while(1)
	{
		// Check for messages
		if (SDL_PollEvent(&event))
		{
			// Check for the quit message
			if (event.type == SDL_QUIT)
			{
				// Quit the program
				break;
			}
		}
			// Game loop will go here...
			// Apply the image to the display







	}

	// Tell the SDL to clean up and shut down





	//

	SDL_Quit();


	jni_ir_viewer_dealloc((void *)NULL, (void *)NULL);


	//////////////////   For Shared memory ///////////////////////////


	RB_DEBUG("Trying to terminate normally ...\n");

	if (synch.acquire () == -1)		// wait here if someone else is accessing or going to access shared memory
		RB_ERROR_RETURN(("Error in acquiring synch\n"), -1);

	RB_DEBUG("Terminating normally ...\n");

	if (mutex.remove () == -1)
		RB_ERROR_RETURN(("Error in removing mutex \n"), -1);



	if (shm_server.remove () < 0)
		RB_ERROR_RETURN(("Error in removing Mail Box \n"), -1);



	if (synch.release () == -1)
		RB_ERROR_RETURN(("Error in release Mail Box synch\n"), -1);

	if (synch.remove () == -1)
		RB_ERROR_RETURN(("Error in removing Mail Box synch\n"), -1);

	//////////////////   For Shared memory ///////////////////////////


	return 0;

}


void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint32 *target_pixel = (Uint32 *)((Uint8 *) surface->pixels + y * surface->pitch +
                                                     x * sizeof *target_pixel);
  *target_pixel = pixel;
}

void CatchSignal(int sig)
{

	RB_DEBUG("Signal %d caught", sig);

}
