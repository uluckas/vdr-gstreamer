/*
 * gstreamer.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <vdr/plugin.h>

#include "gstreamer_device.h"

static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = "Audio, video and OSD output device through 'gstreamer' plugin";
static const char *MAINMENUENTRY  = "Gstreamer";

class cPluginGstreamer : public cPlugin {
private:
  // Add any member variables or functions you may need here.
  
public:
  cPluginGstreamer(void);
  virtual ~cPluginGstreamer();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual void MainThreadHook(void);
  virtual cString Active(void);
  virtual time_t WakeupTime(void);
  virtual const char *MainMenuEntry(void) { return MAINMENUENTRY; }
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  virtual bool Service(const char *Id, void *Data = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
  };

cPluginGstreamer::cPluginGstreamer(void) {
  isyslog("%s", __PRETTY_FUNCTION__);
}

cPluginGstreamer::~cPluginGstreamer()
{
  isyslog("%s", __PRETTY_FUNCTION__);
}

const char *cPluginGstreamer::CommandLineHelp(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginGstreamer::ProcessArgs(int argc, char *argv[])
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginGstreamer::Initialize(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  cGStreamerDevice::Initialize();
  // Initialize any background activities the plugin shall perform.
  return true;
}

bool cPluginGstreamer::Start(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Start any background activities the plugin shall perform.
  return true;
}

void cPluginGstreamer::Stop(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Stop any background activities the plugin is performing.
}

void cPluginGstreamer::Housekeeping(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Perform any cleanup or other regular tasks.
}

void cPluginGstreamer::MainThreadHook(void)
{
  // Perform actions in the context of the main program thread.
  // WARNING: Use with great care - see PLUGINS.html!
}

cString cPluginGstreamer::Active(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Return a message string if shutdown should be postponed
  return NULL;
}

time_t cPluginGstreamer::WakeupTime(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Return custom wakeup time for shutdown script
  return 0;
}

cOsdObject *cPluginGstreamer::MainMenuAction(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Perform the action when selected from the main VDR menu.
  return NULL;
}

cMenuSetupPage *cPluginGstreamer::SetupMenu(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Return a setup menu in case the plugin supports one.
  return NULL;
}

bool cPluginGstreamer::SetupParse(const char *Name, const char *Value)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Parse your own setup parameters and store their values.
  return false;
}

bool cPluginGstreamer::Service(const char *Id, void *Data)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Handle custom service requests from other plugins
  return false;
}

const char **cPluginGstreamer::SVDRPHelpPages(void)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Return help text for SVDRP commands this plugin implements
  return NULL;
}

cString cPluginGstreamer::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  isyslog("%s", __PRETTY_FUNCTION__);
  // Process SVDRP commands this plugin implements
  return NULL;
}

VDRPLUGINCREATOR(cPluginGstreamer); // Don't touch this!
