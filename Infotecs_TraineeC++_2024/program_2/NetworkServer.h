#include <netinet/in.h>
#include "DataHandler.h"

#ifndef INFOTECSEVENTS_NETWORKSERVER_H
#define INFOTECSEVENTS_NETWORKSERVER_H

namespace network {

  class NetworkServer {
    public:
     NetworkServer(int port);
     ~NetworkServer();
     void startListening();

    private:
     int port;
     int server_fd;
     void setupServer();
     void handleClient(int);
     handler::DataHandler dataHandler;
  };

}

#endif
