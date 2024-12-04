#ifndef _FAKE_RECEIVER_H
#define _FAKE_RECEIVER_H

#include "abs_receiver.h"

class FakeReceiver : public AbsReceiver {

public:
    FakeReceiver(const char* filename);
    ~FakeReceiver(); 
};



#endif