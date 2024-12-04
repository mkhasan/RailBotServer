#ifndef _ABS_RECEIVER_H
#define _ABS_RECEIVER_H

#include "IR_Image.h"

class AbsReceiver {

    int width;
    int height;
    int pixelSize;

    ACE_SV_Semaphore_Complex mutex;
    ACE_SV_Semaphore_Complex synch;
    IR_Image * pImage = NULL;

public:

    AbsReceiver(int width = 384, int height = 288, int pixelSize = 2);

    virtual void Initialize();
    
    virtual ~AbsReceiver();

    virtual void Finalize();

    virtual void Update(const char *buffer, int len) = 0;
};

#endif