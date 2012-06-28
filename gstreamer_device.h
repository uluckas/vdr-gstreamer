#include <vdr/device.h>

#ifndef  __GSTREAMER_DEVICE_H
#define __GSTREAMER_DEVICE_H

class cGStreamerVideoSrc;

class cGStreamerDevice : public cDevice {

private:
  cGStreamerVideoSrc *mGRunLoopThread;
  
public:
  static bool Initialize(void);

  public:
  cGStreamerDevice();
  virtual ~cGStreamerDevice();

  // Replay
  virtual bool HasDecoder(void) const;
  virtual bool CanReplay(void) const;
  virtual bool SetPlayMode(ePlayMode PlayMode);
  virtual int64_t GetSTC(void);
  virtual bool HasIBPTrickSpeed(void);
  virtual void TrickSpeed(int Speed);
  virtual void Clear(void);
  virtual void Play(void);
  virtual void Freeze(void);
  virtual void Mute(void);
  virtual void StillPicture(const uchar *Data, int Length);
  virtual bool Poll(cPoller &Poller, int TimeoutMs = 0);
  virtual int PlayPesPacket(const uchar *Data, int Length, bool VideoOnly);

    
  // Extra replay
  //virtual bool GrabImage(const char *FileName, bool Jpeg = true, int Quality = -1, int SizeX = -1, int SizeY = -1);
  //virtual void SetVideoFormat(bool VideoFormat16_9);
  //virtual void SetVolumeDevice(int Volume);

};

#endif