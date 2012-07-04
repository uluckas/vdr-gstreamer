#include "gstreamer_vdrsrc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if 1
#define AUDIO_SINK "autoaudiosink"
#define VIDEO_SINK "xvimagesink force-aspect-ratio=1 "
#else
#define AUDIO_SINK "alsasink"
//#define VIDEO_SINK "dfbvideosink "
#define VIDEO_SINK "fbdevsink device=/dev/fb0"
#endif

cGStreamerVideoSrc::cGStreamerVideoSrc(void) {
  isyslog("%s", __PRETTY_FUNCTION__);  
}

cGStreamerVideoSrc::~cGStreamerVideoSrc(void) {
  isyslog("%s", __PRETTY_FUNCTION__);  
  gst_object_unref (GST_OBJECT (mVdrSrc) );
  mVdrSrc = NULL;
  g_main_loop_quit(mLoop);
  Cancel(3);
}

void cGStreamerVideoSrc::Action(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
  
  /* Initialisation */
  gst_init (NULL, NULL);
  
  /* Create gstreamer elements */
  GstElement *pipeline = gst_parse_launch("appsrc name=vdrsource"
  " ! mpegpsdemux name=demux"
  " { demux."
  "   ! queue max-size-buffers=0 max-size-time=0 name=queue1"
  "   ! mpeg2dec name=dec"
  "   ! ffdeinterlace mode=auto name=deinterlace"
  "   ! " VIDEO_SINK " name=video"
  " }"
  " { demux."
  "   ! queue max-size-buffers=0 max-size-time=0 name=queue2"
  "   ! mad name=mad"
  "   ! " AUDIO_SINK " name=audio"
  " } "
  , NULL);
//  "filesink location=/tmp/test.pes", NULL);
  
  if (!pipeline) {
   isyslog("!pipeline");
   return;
  }
  
  mVdrSrc = gst_bin_get_by_name (GST_BIN(pipeline), "vdrsource");
  if (!mVdrSrc) {
    if (pipeline) gst_object_unref (GST_OBJECT (pipeline));
    isyslog("!mVdrSrc");
    return;
  }
  
  /* Set the pipeline to "playing" state*/
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  
  /* Iterate */
  mLoop = g_main_loop_new (NULL, FALSE);
  isyslog("MainLoop running");
  g_main_loop_run (mLoop);
  isyslog("MainLoop done");

  /* Out of the main loop, clean up nicely */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  
  if (pipeline) {
    gst_object_unref (GST_OBJECT (pipeline));
    pipeline = NULL;
  }
}

int cGStreamerVideoSrc::playPesPacket(const uchar *data, int length, bool VideoOnly) {
  if (!mVdrSrc) return -1;

  GstFlowReturn ret;
  guint8* bufferData = (guint8*) g_malloc (length);
  memcpy(bufferData, data, length);
#if GST_VERSION_MAJOR == 0 && GST_VERSION_MINOR <= 10
  GstBuffer *buf = gst_buffer_new ();
  GST_BUFFER_MALLOCDATA(buf) = GST_BUFFER_DATA(buf) = bufferData;
  GST_BUFFER_SIZE(buf) = length;
#else      
  GstBuffer *buf = gst_buffer_new_wrapped(bufferData, length);
#endif      
  g_signal_emit_by_name (mVdrSrc, "push-buffer", buf, &ret);
  gst_buffer_unref (buf);
  
  if (ret < GST_FLOW_OK) {
    esyslog("Error sending buffer: %d", ret);
    return -1;
  }
  return length;
}
  

