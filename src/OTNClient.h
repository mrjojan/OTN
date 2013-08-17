#ifndef OTNCLIENT_H
#define OTNCLIENT_H

#include "OtnRTSP.h"
#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <iostream>

class OTNClient 
{

/*
 * constructor is setting @m_d
*/
    public:
        OTNClient (int = 1);

/* 
 * @start_stream Gst part for create and 
 * stream rtsp stream
*/
    public:
        void start_stream ();

/* @m_id is clients id */
    private:
        int m_id;
};

#endif /*OTNClient.h*/
