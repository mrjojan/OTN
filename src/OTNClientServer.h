#ifndef OTNCLIENTSERVER_H
#define OTNCLIENTSERVER_H

#include "OTNRTSPStreamer.h"
#include <thread>

class OTNClientServer
{

/*
 * Constructor calls create_stream_and_run function
*/
    public:
        OTNClientServer (); 
/* 
 *@create_stream_and_run function is for create 
 * OTNRTSPStreamer singleton object , and for each
 * client call open_stream_for_client with his id.
 * this all with threads
*/
    public:
        void create_stream_and_run ();
};

#endif /*OTNClientServer.h*/
