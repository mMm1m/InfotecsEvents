#include <netinet/in.h>
#include "DataHandler.h"

#ifndef INFOTECSEVENTS_NETWORKSERVER_H
#define INFOTECSEVENTS_NETWORKSERVER_H

namespace network_program_2 {

  class NetworkServer{
    public:
     NetworkServer() = delete;
     NetworkServer(const NetworkServer& other) = delete;
     NetworkServer(NetworkServer&& other) = delete;
     ~NetworkServer();
     NetworkServer& operator=(const NetworkServer& other) = delete;
     NetworkServer& operator=(NetworkServer&& other) = delete;
     NetworkServer(int port);
     void startListening();
    private:
     int port;
     int server_fd;
     void setupServer();
     void handleClient(int);
     handler_program_2::DataHandler dataHandler;
  };

}

#endif