#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-media-factory.h>
#include <thread>
#include <string>
#include <iostream>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef __OTN_RTSP__
#define __OTN_RTSP__

G_BEGIN_DECLS

/* types for the media factory */

#define OTN_TYPE_RTSP              (otn_rtsp_get_type ())
#define OTN_IS_RTSP(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OTN_TYPE_RTSP))
#define OTN_IS_RTSP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), OTN_TYPE_RTSP))
#define OTN_RTSP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), OTN_TYPE_RTSP, OtnRTSPClass))
#define OTN_RTSP(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), OTN_TYPE_RTSP, OtnRTSP))
#define OTN_RTSP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), OTN_TYPE_RTSP, OtnRTSPClass))
#define OTN_RTSP_CAST(obj)         ((OtnRTSP*)(obj))
#define OTN_RTSP_CLASS_CAST(klass) ((OtnRTSPClass*)(klass))

typedef struct _OtnRTSP OtnRTSP;
typedef struct _OtnRTSPClass OtnRTSPClass;
typedef struct _OtnRTSPPrivate OtnRTSPPrivate;

/**
 * OtnRTSP:
 *
 * A media factory that creates a pipeline to play and uri.
 */
struct _OtnRTSP {
    GstRTSPMediaFactory   parent;

    OtnRTSPPrivate *priv;
};

/**
 * OtnRTSPClass:
 *
 * The #OtnRTSP class structure.
 */
struct _OtnRTSPClass {
    GstRTSPMediaFactoryClass  parent_class;
};

GType                 otn_rtsp_get_type   (void);

/* creating the factory */
OtnRTSP *             otn_rtsp_new     (void);

/* Set and Get clients id */
void                  otn_rtsp_set_id      (OtnRTSP *factory, const gchar *uri);
gchar *               otn_rtsp_get_id      (OtnRTSP *factory);

G_END_DECLS

#endif /* __OTN_RTSP_H__ */
