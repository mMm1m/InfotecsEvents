#ifndef INFOTECSEVENTS_NETWORK_H
#define INFOTECSEVENTS_NETWORK_H

#include <string>
#include <netinet/in.h>

#include "handler.h"

namespace network{
    class NetworkClient{
      public:
       NetworkClient() = delete;
       NetworkClient(const NetworkClient& other) = delete;
       NetworkClient(NetworkClient&& other) = default;
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
       handler::DataHandler dataHandler;
       void setupServer();
       void handleClient(int);
    };
}

#endif