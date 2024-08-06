#include <netinet/in.h>
#include <string>

#ifndef INFOTECSEVENTS_NETWORKCLIENT_H
#define INFOTECSEVENTS_NETWORKCLIENT_H

// !!! можно сделать абстрактный класс, наследовавшись от которого класс будет реализовывать функционал

namespace network {
  class NetworkClient {
    public:
     NetworkClient(int port);
     void connectTo();
     void sendData(std::string&);
     int getSock();
    private:
     int sock;
     int port;
     struct sockaddr_in addr;
     std::string buffer_data;
  };
}

#endif
