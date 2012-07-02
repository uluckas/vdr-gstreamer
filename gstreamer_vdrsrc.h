#ifndef  __GSTREAMER_VDRSRC_H
#define __GSTREAMER_VDRSRC_H

#include <gst/gst.h>
#include <vdr/device.h>

class cGStreamerVideoSrc : public cThread {
    
private:
  GMainLoop *mLoop;
  GstElement *mVdrSrc;
  virtual void Action(void);

public:
  cGStreamerVideoSrc();
  virtual ~cGStreamerVideoSrc();
  
  virtual int playPesPacket(const uchar *data, int length, bool VideoOnly);
  
};

#endif