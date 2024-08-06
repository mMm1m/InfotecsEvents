#include <netinet/in.h>
#include "DataHandler.h"

#ifndef INFOTECSEVENTS_NETWORKSERVER_H
#define INFOTECSEVENTS_NETWORKSERVER_H

namespace networking {
  class NetworkServer {
    public:
     NetworkServer(int port);
     void connectTo();
    private:
     int port;
     int sock;
     int listener;
     char buf[1024];
     struct sockaddr_in addr;
     handler::DataHandler dataHandler;
  };
}


#endif //INFOTECSEVENTS_NETWORKSERVER_H
