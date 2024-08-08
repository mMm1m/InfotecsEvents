#include <netinet/in.h>
#include "DataHandler.h"

#ifndef INFOTECSEVENTS_NETWORKSERVER_H
#define INFOTECSEVENTS_NETWORKSERVER_H

namespace network_programm_2 {
  class NetworkServer{
    public:
     NetworkServer() = delete;
     NetworkServer(const NetworkServer& other) = delete;
     NetworkServer(NetworkServer&& other) = delete;
     NetworkServer(int port);
     ~NetworkServer();
     NetworkServer& operator=(const NetworkServer& other) = delete;
     NetworkServer& operator=(NetworkServer&& other) = delete;
     void startListening();
    private:
     int port;
     int server_fd;
     handler_programm_2::DataHandler dataHandler;
     void setupServer();
     void handleClient(int);
  };
}

#endif