#include "OTNRTSPStreamer.h"


OTNRTSPStreamer * OTNRTSPStreamer::m_instance = nullptr;

OTNRTSPStreamer::OTNRTSPStreamer ()
{

}

OTNRTSPStreamer::~OTNRTSPStreamer ()
{

}

OTNRTSPStreamer::OTNRTSPStreamer (const OTNRTSPStreamer &)
{

}

OTNRTSPStreamer& OTNRTSPStreamer::operator= (const OTNRTSPStreamer & rvl)
{
    return *this;
}

void OTNRTSPStreamer::make_mapping (int id, OTNClient * cl)
{
    m_map.insert (std::pair <int, OTNClient*>(id, cl));
}

OTNRTSPStreamer* OTNRTSPStreamer::get_instance ()
{
    if (m_instance == nullptr)
    {
        m_instance = new OTNRTSPStreamer ();
    }
    assert (m_instance != nullptr);
    return m_instance;
}

void OTNRTSPStreamer::open_stream_for_client (int client_id)
{
    OTNClient * client = new OTNClient (client_id);
    make_mapping (client_id, client);
    client -> start_stream ();
}
