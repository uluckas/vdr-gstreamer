#include "gstreamer_device.h"
#include "gstreamer_vdrsrc.h"

#include <gst/gst.h>

bool cGStreamerDevice::Initialize(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
  
  new cGStreamerDevice();
  return true;
}

cGStreamerDevice::cGStreamerDevice() :
cDevice() {
  isyslog("%s", __PRETTY_FUNCTION__);
  
  mGRunLoopThread = NULL;
}

cGStreamerDevice::~cGStreamerDevice() {
  isyslog("%s", __PRETTY_FUNCTION__);
  delete mGRunLoopThread;
}

bool cGStreamerDevice::HasDecoder(void) const {
  //isyslog("%s", __PRETTY_FUNCTION__);
  return true;
}

bool cGStreamerDevice::CanReplay(void) const {
  isyslog("%s", __PRETTY_FUNCTION__);
  return true;
}

bool cGStreamerDevice::SetPlayMode(ePlayMode PlayMode) {
  isyslog("%s: %d", __PRETTY_FUNCTION__, PlayMode);
  if (mGRunLoopThread) {
    delete mGRunLoopThread;
    mGRunLoopThread = NULL;
  }
  if (PlayMode != pmNone) {
    mGRunLoopThread = new cGStreamerVideoSrc();
    mGRunLoopThread->Start();
  }

  return false;
}

int64_t cGStreamerDevice::GetSTC(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
  return -1;
}

bool cGStreamerDevice::HasIBPTrickSpeed(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
  return false;
}

void cGStreamerDevice::TrickSpeed(int Speed) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

void cGStreamerDevice::Clear(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

void cGStreamerDevice::Play(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

void cGStreamerDevice::Freeze(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

void cGStreamerDevice::Mute(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

void cGStreamerDevice::StillPicture(const uchar *Data, int Length) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

bool cGStreamerDevice::Poll(cPoller &Poller, int TimeoutMs) {
//   isyslog("%s", __PRETTY_FUNCTION__);
  return true;
}

int cGStreamerDevice::PlayPesPacket(const uchar *Data, int Length, bool VideoOnly) {
//   isyslog("%s", __PRETTY_FUNCTION__);
  return mGRunLoopThread->playPesPacket(Data, Length, VideoOnly);
}

