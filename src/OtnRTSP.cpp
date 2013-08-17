#include "OtnRTSP.h"

#define OTN_RTSP_GET_PRIVATE(obj)  \
    (G_TYPE_INSTANCE_GET_PRIVATE ((obj), OTN_TYPE_RTSP, OtnRTSPPrivate))

struct _OtnRTSPPrivate
{
    GMutex lock;
    gchar *id;
    GstElement* main_element1;
    GstElement* main_element2;
};

#define DEFAULT_ID         0

enum
{
    PROP_0,
    PROP_ID,
};

static void otn_rtsp_get_property (GObject * object,
        guint propid, GValue * value, GParamSpec * pspec);
static void otn_rtsp_set_property (GObject * object,
        guint propid, const GValue * value, GParamSpec * pspec);
static GstRTSPMedia *otn_rtsp_construct (GstRTSPMediaFactory * factory,
    const GstRTSPUrl * url);
static void otn_rtsp_finalize (GObject * obj);


static GstElement *otn_rtsp_create_element (GstRTSPMediaFactory *factory, 
        const GstRTSPUrl * url);

G_DEFINE_TYPE (OtnRTSP, otn_rtsp, GST_TYPE_RTSP_MEDIA_FACTORY);

static void
otn_rtsp_class_init (OtnRTSPClass * klass)
{
    GObjectClass *gobject_class;
    GstRTSPMediaFactoryClass *mediafactory_class;

    g_type_class_add_private (klass, sizeof (OtnRTSPPrivate));

    gobject_class = G_OBJECT_CLASS (klass);
    mediafactory_class = GST_RTSP_MEDIA_FACTORY_CLASS (klass);

    gobject_class->get_property = otn_rtsp_get_property;
    gobject_class->set_property = otn_rtsp_set_property;
    gobject_class->finalize = otn_rtsp_finalize;

    mediafactory_class->create_element = otn_rtsp_create_element;
    mediafactory_class->construct = otn_rtsp_construct;

}

static void
otn_rtsp_init (OtnRTSP * factory)
{
    OtnRTSPPrivate *priv =
        OTN_RTSP_GET_PRIVATE (factory);

    factory->priv = priv;

    priv->id = g_strdup (DEFAULT_ID);
    g_mutex_init (&priv->lock);


}

static void
otn_rtsp_set_property (GObject * object, guint propid,
        const GValue * value, GParamSpec * pspec)
{
    OtnRTSP *factory = OTN_RTSP (object);

    switch (propid) {
        case PROP_ID:
            otn_rtsp_set_id (factory, g_value_get_string (value));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, propid, pspec);
    }
}

static void
otn_rtsp_get_property (GObject * object, guint propid,
        GValue * value, GParamSpec * pspec)
{
    OtnRTSP *factory = OTN_RTSP (object);

    switch (propid) {
        case PROP_ID:
            g_value_take_string (value, otn_rtsp_get_id (factory));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, propid, pspec);
    }
}

static void
otn_rtsp_finalize (GObject * obj)
{
    OtnRTSP *factory = OTN_RTSP (obj);
    OtnRTSPPrivate *priv = factory->priv;

    g_free (priv->id);
    g_mutex_clear (&priv->lock);

    G_OBJECT_CLASS (otn_rtsp_parent_class)->finalize (obj);
}

OtnRTSP *
otn_rtsp_new (void)
{
    OtnRTSP *result;

    result = static_cast <OtnRTSP*>(g_object_new (OTN_TYPE_RTSP, NULL));

    return result;
}

void
otn_rtsp_set_id (OtnRTSP * factory, const gchar * id)
{
    OtnRTSPPrivate *priv;

    g_return_if_fail (OTN_IS_RTSP (factory));
    g_return_if_fail (id != NULL);

    priv = factory->priv;

    g_mutex_lock (&priv->lock);
    g_free (priv->id);
    priv->id = g_strdup (id);
    g_mutex_unlock (&priv->lock);
}


gchar *
otn_rtsp_get_id (OtnRTSP * factory)
{
    OtnRTSPPrivate *priv;
    gchar *result;

    g_return_val_if_fail (OTN_IS_RTSP (factory), NULL);

    priv = factory->priv;

    g_mutex_lock (&priv->lock);
    result = g_strdup (priv->id);
    g_mutex_unlock (&priv->lock);

    return result;
}

void open_socket (int buffer, GstElement* main_element1, GstElement* main_element2)
{
    char buf [100]; 
    socklen_t len; 
    int k, sock_desc, temp_sock_desc; 
    struct sockaddr_in client, server; 
    memset (&client, 0, sizeof (client)); 
    memset (&server, 0, sizeof (server)); 
    sock_desc = socket (AF_INET, SOCK_STREAM, 0); 
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = inet_addr ("127.0.0.1"); 
    server.sin_port = 7777;
    int helper = 7777;
    k = bind (sock_desc, (struct sockaddr*) &server, sizeof (server)); 
    if (k == -1)
    {
        g_print ("Error Bind\n");
        server.sin_port = 8888;
        helper = 8888;
        k = bind (sock_desc, (struct sockaddr*) &server, sizeof (server)); 
    }
    k = listen (sock_desc, 20); 
    if (k == -1)
    {
        g_print ("Error Listen\n");
    }
    len = sizeof (client);
    temp_sock_desc = accept (sock_desc, (struct sockaddr*) &client, &len); 
    while (1)
    {     
        k = recv (temp_sock_desc, buf, 100, 0);     
        if (strcmp (buf, "exit") == 0)        
            break;     
        if (k > 0)
        {
            buffer = atoi (buf);
            if (buffer != 0)
            {
                std::cout << "Buffer " << buffer << " from " << helper << std::endl;
                gst_element_set_state (main_element2, GST_STATE_NULL);
                g_object_set (main_element2, "index", buffer, NULL);
                gst_element_set_state (main_element2, GST_STATE_PLAYING);
            }
        }
    }
    close (sock_desc); 
    close (temp_sock_desc); 
}

static GstRTSPMedia *
otn_rtsp_construct (GstRTSPMediaFactory * factory, const GstRTSPUrl * url)
{
    GstRTSPMedia *media;
    GstElement *element, *pipeline;
    GstRTSPMediaFactoryClass *klass;
    int test1 = 0;

    OtnRTSPPrivate *priv;
    OtnRTSP *my_factory;;

    my_factory = OTN_RTSP_CAST (factory);
    priv = my_factory->priv;

    klass = GST_RTSP_MEDIA_FACTORY_GET_CLASS (factory);

    if (!klass->create_pipeline)
    {
        g_critical ("no create_pipeline function");
        return NULL;
    }

    element = otn_rtsp_create_element (factory, url);
    if (element == NULL)
    {
        g_critical ("could not create element");
        return NULL;
    }

    /* create a new empty media */
    media = gst_rtsp_media_new (element);

    priv -> main_element1 = gst_bin_get_by_name (GST_BIN (element),"src");
    priv -> main_element2 = gst_bin_get_by_name (GST_BIN (element),"src2");
    std::thread t1 (open_socket, test1, priv -> main_element1, priv -> main_element2);
    t1.detach ();
    gst_rtsp_media_collect_streams (media);
    

    pipeline = klass->create_pipeline (factory, media);
    if (pipeline == NULL)
    {
        g_critical ("can't create pipeline");
        g_object_unref (media);
        return NULL;
    }

    return media;

}
static GstElement *
otn_rtsp_create_element (GstRTSPMediaFactory * factory, const GstRTSPUrl * url)
{

/* Create */
    OtnRTSPPrivate *priv;
    GstElement *pipeline;
    GstElement *bin1, *src1, *payload1, *parser1, *identty;
    GstElement *bin2, *src2, *payload2, *parser2, *enc, *dec;
    OtnRTSP *urifact;

    urifact = OTN_RTSP_CAST (factory);
    priv = urifact->priv;
/* Video, If its not working just add identity element */
    pipeline = gst_pipeline_new ("my-pipeline");
    bin1 = gst_bin_new ("my-bin1");
    src1 = gst_element_factory_make ("multifilesrc", "src");
    if (src1 == NULL)
        g_error ("Could not create 'multifilesrc' element");

    parser1 = gst_element_factory_make ("h264parse", "parser");
    if (parser1 == NULL)
        g_error ("Could not create 'parser' element");

    identty = gst_element_factory_make ("identity", "identty");
    if (identty == NULL)
        g_error ("Could not create 'identity' element");
    payload1 = gst_element_factory_make ("rtph264pay", "payload1");
    if (payload1 == NULL) {
        g_error ("Could not create 'rtph264pay' element");
    }
    /*
     * Give Default values for video
     */
    g_object_set (src1, "location", "/home/adavtyan/OTNMedia/video/arsen%03d.h264","user_id" , atoi (priv->id), "index",1,NULL);
    g_object_set (parser1, "config-interval", 1, NULL);
    g_object_set (identty, "datarate", 25,"user_id", atoi(priv->id), NULL );
    g_object_set (payload1, "name", "pay0","config-interval",1,"pt",96, NULL);

/* Audio */
    bin2 = gst_bin_new ("my-bin2");
    src2 = gst_element_factory_make ("multifilesrc", "src2");
    if (src2 == NULL)
        g_error ("Could not create 'multifilesrc' element");

    parser2 = gst_element_factory_make ("aacparse", "parser2");
    if (parser2 == NULL)
        g_error ("Could not create 'aacparse' element");

    payload2 = gst_element_factory_make ("rtpmp4apay", "payload2");
    if (payload2 == NULL) {
        g_error ("Could not create 'rtpmp4apay' element");
    }
    dec = gst_element_factory_make ("faad", "my-decoder");
    if (dec == NULL) {
        g_error ("Could not create 'faad' element");
    }
    enc = gst_element_factory_make ("faac", "my-encoder");
    if (enc == NULL) {
        g_error ("Could not create 'faac' element");
    }
    /*
     * Give Default values for audio
     */
    g_object_set (src2, "location", "/home/adavtyan/OTNMedia/audio/audio_96f_%03d.aac", "index",30,NULL);
    g_object_set (payload2, "name", "pay1","pt",97, NULL);

/* Connect */
    gst_bin_add_many (GST_BIN (bin1), src1, parser1,identty, payload1, NULL);
    gst_bin_add_many (GST_BIN (bin2), src2, parser2, dec, enc, payload2, NULL);
    gst_element_link_many (src1, parser1,identty, payload1, NULL);
    gst_element_link_many (src2, parser2, dec, enc, payload2, NULL);
    gst_bin_add (GST_BIN (pipeline), bin1);
    gst_bin_add (GST_BIN (pipeline), bin2);

    return pipeline;
}
