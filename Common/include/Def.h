//
// Created by usrc on 17. 1. 16.
//

#ifndef ROBOTCONTROL_DEF_H
#define ROBOTCONTROL_DEF_H

#ifndef WIN32 
typedef unsigned char BYTE;
typedef bool BOOL;
typedef unsigned int DWORD;
typedef unsigned short WORD;

#include "ace/Log_Msg.h"


#include "Callback.h"

#endif

#define SERVER_IP "143.248.221.68"

#define CTRL_IP "120.203.102.209"
#define IMAGE_CAM_IP "120.203.102.210"
#define IR_CAM_IP "120.203.102.211"

#define CTRL_PORT 8081

#define CMD_LEN 16

#define PACK_SIZE 60024
#define RTP_HEADER_SIZE 12
#define RTP_PACK_SIZE (PACK_SIZE + RTP_HEADER_SIZE)	//$0rtp_packet_size
#define ENCODE_QUALITY 80

#define FALSE false
#define TRUST true


#define WIDTH 336
#define HEIGHT 254

#define MAX_IMAGE_FILE_SIZE 204800

#define IMAGE_QUEUE_SIZE 10

enum returnType {SUCCESS=0, SOCK_ACCESS_ERROR=1, MAX_FILE_COUNT_REACHED=2, WAIT_FUNC_FAIL=3, STREAM_CREATION_ERROR=4, STREAM_LOAD_ERROR=5, MISSING_PACK_ERROR=6};

#define PIXEL_SIZE 2

#define EPSILON 0.001
#define FPS 12.5

#define TO_CLIENT "CMD_MANAGER/TO_CLIENT"
#define FROM_CLIENT "CMD_MANAGER/FROM_CLIENT"


#ifdef WIN32 
#define RB_DEBUG(...)
#else
typedef struct {
    BYTE r;
    BYTE g;
    BYTE b;
} RGB_T;


const RGB_T iron[128] =  {
        {0,   0,  0},
        {0,   0,  0},
        {0,   0,  36},
        {0,   0,  51},
        {0,   0,  66},
        {0,   0,  81},
        {2,   0,  90},
        {4,   0,  99},
        {7,   0, 106},
        {11,   0, 115},
        {14,   0, 119},
        {20,   0, 123},
        {27,   0, 128},
        {33,   0, 133},
        {41,   0, 137},
        {48,   0, 140},
        {55,   0, 143},
        {61,   0, 146},
        {66,   0, 149},
        {72,   0, 150},
        {78,   0, 151},
        {84,   0, 152},
        {91,   0, 153},
        {97,   0, 155},
        {104,   0, 155},
        {110,   0, 156},
        {115,   0, 157},
        {122,   0, 157},
        {128,   0, 157},
        {134,   0, 157},
        {139,   0, 157},
        {146,   0, 156},
        {152,   0, 155},
        {157,   0, 155},
        {162,   0, 155},
        {167,   0, 154},
        {171,   0, 153},
        {175,   1, 152},
        {178,   1, 151},
        {182,   2, 149},
        {185,   4, 149},
        {188,   5, 147},
        {191,   6, 146},
        {193,   8, 144},
        {195,  11, 142},
        {198,  13, 139},
        {201,  17, 135},
        {203,  20, 132},
        {206,  23, 127},
        {208,  26, 121},
        {210,  29, 116},
        {212,  33, 111},
        {214,  37, 103},
        {217,  41,  97},
        {219,  46,  89},
        {221,  49,  78},
        {223,  53,  66},
        {224,  56,  54},
        {226,  60,  42},
        {228,  64,  30},
        {229,  68,  25},
        {231,  72,  20},
        {232,  76,  16},
        {234,  78,  12},
        {235,  82,  10},
        {236,  86,   8},
        {237,  90,   7},
        {238,  93,   5},
        {239,  96,   4},
        {240, 100,   3},
        {241, 103,   3},
        {241, 106,   2},
        {242, 109,   1},
        {243, 113,   1},
        {244, 116,   0},
        {244, 120,   0},
        {245, 125,   0},
        {246, 129,   0},
        {247, 133,   0},
        {248, 136,   0},
        {248, 139,   0},
        {249, 142,   0},
        {249, 145,   0},
        {250, 149,   0},
        {251, 154,   0},
        {252, 159,   0},
        {253, 163,   0},
        {253, 168,   0},
        {253, 172,   0},
        {254, 176,   0},
        {254, 179,   0},
        {254, 184,   0},
        {254, 187,   0},
        {254, 191,   0},
        {254, 195,   0},
        {254, 199,   0},
        {254, 202,   1},
        {254, 205,   2},
        {254, 208,   5},
        {254, 212,   9},
        {254, 216,  12},
        {255, 219,  15},
        {255, 221,  23},
        {255, 224,  32},
        {255, 227,  39},
        {255, 229,  50},
        {255, 232,  63},
        {255, 235,  75},
        {255, 238,  88},
        {255, 239, 102},
        {255, 241, 116},
        {255, 242, 134},
        {255, 244, 149},
        {255, 245, 164},
        {255, 247, 179},
        {255, 248, 192},
        {255, 249, 203},
        {255, 251, 216},
        {255, 253, 228},
        {255, 254, 239},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249},
        {255, 255, 249}
};



#define SKI_DEFAULT_SEM_KEY ACE_DEFAULT_SEM_KEY
#define BASE 1


#define SEM_KEY_1 (SKI_DEFAULT_SEM_KEY+10*BASE+1)
#define SEM_KEY_2 (SKI_DEFAULT_SEM_KEY+10*BASE+2)

#define SHM_KEY (SKI_DEFAULT_SEM_KEY+10*BASE)

#include <sys/time.h>

#define Sleep(ms) usleep(ms*1000)
#include "ace/Task.h"

#ifndef V_LEVEL
#error
#endif

// = ACE_OS::gettimeofday();

#if V_LEVEL <= DEBUG
#define RB_DEBUG(...) { \
		printf("[%Lu:%Lu] ", ACE_OS::gettimeofday().sec(), ACE_OS::gettimeofday().usec()); \
        printf(__VA_ARGS__); \
		}

#define _DEBUG_
#else
#define RB_DEBUG(...)
#endif

#if V_LEVEL <= INFO
#define RB_INFO(...) ACE_DEBUG((LM_DEBUG, __VA_ARGS__))
#else
#define RB_INFO(...)
#endif

#if V_LEVEL <= WARN
#define RB_WARN(...) ACE_DEBUG((LM_DEBUG, __VA_ARGS__))
#else
#define RB_WARN(...)
#endif

#if V_LEVEL <= ERROR
#define RB_ERROR(...) ACE_DEBUG((LM_DEBUG, __VA_ARGS__))
#else
#define RB_ERROR(...)
#endif

#if V_LEVEL <= FATAL
#define RB_FATAL(...) ACE_DEBUG((LM_DEBUG, __VA_ARGS__))
#else
#define RB_FATAL(...)
#endif




#define RB_RETURN(X, Y) \
	do { \
		X; \
		return Y; \
	} while (0)



#define RB_DEBUG_RETURN(X, Y) \
	do { \
		RB_RETURN(RB_ERROR X, Y);\
	} while (0)


#define RB_ERROR_RETURN(X, Y) \
	do { \
		RB_RETURN(RB_ERROR X, Y);\
	} while (0)




#define RB_REQUIRE_RETURN(exp, ret) do{ if (!(exp)){ RB_WARN(#exp "\n"); return (ret); }}while(0)

#define RB_ASSERT ACE_ASSERT

#define RB_NEW_RETURN ACE_NEW_RETURN



extern timeval now;
extern timeval start_time;

#endif

#endif //ROBOTCONTROL_DEF_H
