#ifndef INFOTECSEVENTS_NETWORKCLIENT_H
#define INFOTECSEVENTS_NETWORKCLIENT_H

#include <netinet/in.h>
#include <string>

namespace network_programm_1 {
  class NetworkClient{
    public:
     NetworkClient() = delete;
     NetworkClient(const NetworkClient& other) = default;
     NetworkClient(NetworkClient&& other) = delete;
     NetworkClient(const std::string&, int port);
     ~NetworkClient() = default;
     NetworkClient& operator=(const NetworkClient& other) = delete;
     NetworkClient& operator=(NetworkClient&& other) = delete;
     bool connectTo();
     void sendData(std::string&);
     int getSock() const noexcept;
    private:
     int sock;
     size_t port;
     struct sockaddr_in addr;
     std::string server_ip;
  };
}

#endif