/*
 * CStreamer.h
 *
 *  Created on: Jun 27, 2018
 *      Author: usrc
 */

#ifndef SRC_CSTREAMER_H_
#define SRC_CSTREAMER_H_

#include "ImageProcessor.h"

class CStreamer
{
public:
	CStreamer(int aClient, ImageProcessor *aImgProcessor);
    ~CStreamer();

    void    InitTransport(unsigned short aRtpPort, unsigned short aRtcpPort, bool TCP);
    unsigned short GetRtpServerPort();
    unsigned short GetRtcpServerPort();
    void    StreamImage(int StreamID);

private:
    void    SendRtpPacket(const char * data, int dataLength, bool isLastFragment);

    ImageProcessor * m_ImageProcessor;
    int  m_RtpSocket;          // RTP socket for streaming RTP packets to client
    int  m_RtcpSocket;         // RTCP socket for sending/receiving RTCP packages

    unsigned short m_RtpClientPort;      // RTP receiver port on client
    unsigned short m_RtcpClientPort;     // RTCP receiver port on client
    unsigned short m_RtpServerPort;      // RTP sender port on server
    unsigned short m_RtcpServerPort;     // RTCP sender port on server

    unsigned short m_SequenceNumber;
    unsigned int   m_Timestamp;
    int     m_SendIdx;
    bool    m_TCPTransport;
    int  m_Client;
};




#endif /* SRC_CSTREAMER_H_ */
