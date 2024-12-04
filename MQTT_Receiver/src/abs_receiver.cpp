#include "abs_receiver.h"

AbsReceiver::AbsReceiver(int _width, int _height, int _pixelSize) 
    : widht(_width), height(_height), pixelSize(_pixelSize)
{
    
}

AbsReceiver::~AbsReceiver() {

}

void AbsReceiver::Initialize() {
    if(mutex.open (SEM_KEY_1, ACE_SV_Semaphore_Complex::ACE_CREATE, 1) == -1)
		RB_ERROR_RETURN(("IR_Handler: Error in getting mutex \n"), -1);


	
	if(synch.open (SEM_KEY_2,
						  ACE_SV_Semaphore_Complex::ACE_CREATE,
						  1) == -1)
		RB_ERROR_RETURN(("IR_Handler: Error in getting sync \n"), -1);


	ACE_Shared_Memory_SV shm_server (SHM_KEY,
								   sizeof (IR_Image),
								   ACE_Shared_Memory_SV::ACE_CREATE);
	char *shm = (char *) shm_server.malloc ();

	if (shm == 0)
		RB_ERROR_RETURN(("IR_Handler: Error in allocationg shared mem \n"), -1);

	pImage = new (shm) IR_Image;

}

void AbsReceiver::Finalize() {

    RB_DEBUG("IR_Handler: Trying to terminate normally ...\n");

	if (synch.acquire () == -1)		// wait here if someone else is accessing or going to access shared memory
		RB_ERROR_RETURN(("IR_Handler: Error in acquiring synch\n"), -1);

	RB_DEBUG("IR_Handler: Terminating normally ...\n");

	if (mutex.remove () == -1)
		RB_ERROR_RETURN(("IR_Handler: Error in removing mutex \n"), -1);



	if (shm_server.remove () < 0)
		RB_ERROR_RETURN(("IR_Handler: Error in removing Mail Box \n"), -1);



	if (synch.release () == -1)
		RB_ERROR_RETURN(("IR_Handler: Error in release Mail Box synch\n"), -1);

	if (synch.remove () == -1)
		RB_ERROR_RETURN(("IR_Handler: Error in removing Mail Box synch\n"), -1);

}

AbsReceiver::Update(const char* buffer, int len){
    
}