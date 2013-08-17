#include "OTNClientServer.h"
#include <iostream>

int main (int argc, char* argv[])
{
    gst_init (&argc, &argv);
    OTNClientServer* client_server = new OTNClientServer ();
    client_server -> create_stream_and_run ();
    return 0;
}
