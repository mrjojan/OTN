#include "OTNClientServer.h"


OTNClientServer::OTNClientServer ()
{
    //create_stream_and_run ();
}

void OTNClientServer::create_stream_and_run ()
{
    /*
     * I think i need one socket here to get id from client 
     * then give that id to OtnRTSP.cpp to open stream for it.
     * then in OtnRTSP.cpp i need some socket to get info 
     * from each client to change index and location.
     */
    //int pid1, pid2;
    OTNRTSPStreamer* streamer = OTNRTSPStreamer::get_instance ();

    std::thread t4 (&OTNRTSPStreamer::open_stream_for_client, streamer, 400);
    std::thread t3 (&OTNRTSPStreamer::open_stream_for_client, streamer, 300);
    std::thread t2 (&OTNRTSPStreamer::open_stream_for_client, streamer, 200);
    std::thread t1 (&OTNRTSPStreamer::open_stream_for_client, streamer, 100);
    t1.join ();
    t2.join ();
    t3.join ();
    t4.join ();
    //pid1 = fork ();
    //switch (pid1)
    //{
    //    case -1:
    //        std::cout << "Unable to fork" << std::endl;
    //        return;
    //    case 0:
    //        std::cout << "Yeah1" << std::endl;
    //        streamer -> open_stream_for_client (100);
    //        break;
    //}
    ////streamer -> open_stream_for_client (200);
    //pid2 = fork ();
    //switch (pid2)
    //{
    //    case -1:
    //        std::cout << "Unable to fork" << std::endl;
    //        return;
    //    case 0:
    //        std::cout << "Yeah2" << std::endl;
    //        streamer -> open_stream_for_client (200);
    //        break;
    //}
}
