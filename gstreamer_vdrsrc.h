#ifndef  __GSTREAMER_VDRSRC_H
#define __GSTREAMER_VDRSRC_H

#include <gst/gst.h>
#include <vdr/device.h>

class cGStreamerVideoSrc : public cThread {
  
  GstElement *mPipeline, *mVdrSrc;
  GstBus *bus;
  
private:
  GMainLoop *mLoop;
  virtual void Action(void);

public:
  virtual ~cGStreamerVideoSrc();
  
  virtual int playPesPacket(const uchar *data, int length, bool VideoOnly);
  
};

#endif