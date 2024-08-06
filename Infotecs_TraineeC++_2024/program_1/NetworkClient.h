#include <netinet/in.h>
#include <string>

#ifndef INFOTECSEVENTS_NETWORKCLIENT_H
#define INFOTECSEVENTS_NETWORKCLIENT_H

namespace network {
  class NetworkClient {
    public:
     NetworkClient(const std::string&, int port);
     bool connectTo();
     void sendData(std::string&);
     int getSock();
    private:
     int sock;
     int port;
     struct sockaddr_in addr;
     std::string server_ip;
  };
}

#endif
