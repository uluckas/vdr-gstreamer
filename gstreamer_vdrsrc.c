#include "gstreamer_vdrsrc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if 1
#define AUDIO_SINK "pulsesink"
#define VIDEO_SINK "xvimagesink"
#else
#define AUDIO_SINK "alsasink"
//#define VIDEO_SINK "dfbvideosink "
#define VIDEO_SINK "fbdevsink device=/dev/fb0"
#endif

cGStreamerVideoSrc::~cGStreamerVideoSrc(void) {
  Cancel(3);
}

void cGStreamerVideoSrc::Action(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
  
  /* Initialisation */
  gst_init (NULL, NULL);
  
  mLoop = g_main_loop_new (NULL, FALSE);
  
  /* Create gstreamer elements */
  mPipeline = gst_parse_launch("appsrc name=vdrsource ! "
  "mpegpsdemux name=demux ! "
  "queue max-size-buffers=0 max-size-time=0 ! "
  "mpeg2dec ! "
  VIDEO_SINK " ! "
  "demux. ! "
  "queue max-size-buffers=0 max-size-time=0 ! "
  "ffdec_mp3 ! "
  AUDIO_SINK " ", NULL);
//  "filesink location=/tmp/test.pes", NULL);
  
  if (!mPipeline) {
   isyslog("!mPipeline");
   return;
  }
  
  mVdrSrc = gst_bin_get_by_name (GST_BIN(mPipeline), "vdrsource");
  if (!mVdrSrc) {
    if (mPipeline) gst_object_unref (GST_OBJECT (mPipeline));
    isyslog("!mVdrSrc");
    return;
  }
  
  /* Set the pipeline to "playing" state*/
  gst_element_set_state (mPipeline, GST_STATE_PLAYING);
  
  /* Iterate */
  g_main_loop_run (mLoop);
  
  /* Out of the main loop, clean up nicely */
  gst_element_set_state (mPipeline, GST_STATE_NULL);
  
  gst_object_unref (GST_OBJECT (mPipeline));
}

int cGStreamerVideoSrc::playPesPacket(const uchar *data, int length, bool VideoOnly) {
  static int fd = -1;
//   // Lazy initialize
//   if (fd == -1) {
//     fd = open("/tmp/test.pes", O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
//     if (fd == -1) {
//       perror("Opening test.pes");
//     }
//   }
//   int count =  write(fd, data, length);
//   if (count == -1) {
//     perror("Writing test.pes");
//     printf("fd = %d\n", fd);
//   }
  const uchar c = data[3];
  switch (c) {
    case 0xBE:          // padding stream, needed for MPEG1
    case 0xC0 ... 0xDF: // audio
    case 0xE0 ... 0xEF: {// video
      GstFlowReturn ret;
      guint8* bufferData = (guint8*) g_malloc (length);
      memcpy(bufferData, data, length);
#if GST_VERSION_MINOR>10
      GstBuffer *buf = gst_buffer_new_wrapped(bufferData, length);
#else      
      GstBuffer *buf = gst_buffer_new ();
      GST_BUFFER_MALLOCDATA(buf) = GST_BUFFER_DATA(buf) = bufferData;
      GST_BUFFER_SIZE(buf) = length;
#endif      
      g_signal_emit_by_name (mVdrSrc, "push-buffer", buf, &ret);
      gst_buffer_unref (buf);
      
      if (ret < GST_FLOW_OK) {
	esyslog("Error sending buffer: %d", ret);
	return -1;
      }
    }
    break;
    default:
      isyslog("%s: Packet type %x", __PRETTY_FUNCTION__, c);
      //Ignore for now
      break;
  }
  return length;
}
  

