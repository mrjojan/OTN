#include "OTNClient.h"


OTNClient::OTNClient (int id): m_id (id)
{

}
void client_conected ()
{
    std::cout << "Client Connected" << std::endl;
}
void OTNClient::start_stream ()
{
    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPClient *client;
    GstRTSPMountPoints *mounts;
    OtnRTSP *factory;

    std::string str;
    gchar  test1 [11]  = "";
    gchar  test2 [11]  = "";
    snprintf (test1,1000, "%d", m_id + 8454);
    snprintf (test2,1000, "%d", m_id );

    loop = g_main_loop_new (NULL, FALSE);

    server = gst_rtsp_server_new ();
    client = gst_rtsp_client_new ();
    server->m_client = client;

    gst_rtsp_server_set_service (server, test1);

    mounts = gst_rtsp_server_get_mount_points (server);
    g_signal_connect (server, "client-connected", client_conected , NULL);

    factory = otn_rtsp_new ();

    otn_rtsp_set_id (factory, test2);

    gst_rtsp_mount_points_add_factory (mounts, "/test",
            GST_RTSP_MEDIA_FACTORY (factory));

    g_object_unref (mounts);

    if (gst_rtsp_server_attach (server, NULL) == 0)
    {
        g_error ("failed to attach the server\n");
    }

    std::cout << "Stream ready at: rtsp://192.168.1.11:" << test1 << "/test" << std::endl;
    g_main_loop_run (loop);
}
