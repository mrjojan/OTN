#ifndef OTNRTSPSTREAMER_H
#define OTNRTSPSTREAMER_H

#include "OTNClient.h"
#include <map>
#include <cassert>
class OTNRTSPStreamer 
{

/* 
 * @get_instance creates single OTNRTSPStreamer 
 * object and returns it, for singleton
*/
    public:
        static OTNRTSPStreamer * get_instance ();

/* 
 * @make_mapping is doing mapping for 
 * client`s id and client object
 * id -> client
*/
    public:
        void make_mapping (int , OTNClient* );

/* 
 * @open_stream_for_client creates OTNClient 
 * object with @id , calls make_mapping function
 * for mapping id and client, then calling 
 * calling start_stream for that client object
*/
    public:
        void open_stream_for_client (int );

/* 
 * constructor, copy constructor, destructor 
 * and operator= are private because we are
 * using singleton design pattern to create
 * single object
*/
    private:
/* Constructor */
        OTNRTSPStreamer ();

/* Destructor */
        ~OTNRTSPStreamer ();

/* Copy Constructor */
        OTNRTSPStreamer (const OTNRTSPStreamer& );

/* operator= */
        OTNRTSPStreamer& operator= (const OTNRTSPStreamer &);

/* 
 * @m_map member is for save client`s object 
 * with id. id -> client_obj  
 * @m_instance member is singleton object
 * for this class 
*/
    private:
        std::map <int, OTNClient*> m_map;
        static OTNRTSPStreamer* m_instance;
};



#endif /*OTNStreamer.h*/
