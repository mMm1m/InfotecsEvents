#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "NetworkServer.h"

network::NetworkServer::NetworkServer(int port) : port(port), server_fd(-1), dataHandler(handler::DataHandler()) {
  setupServer();
}

network::NetworkServer::~NetworkServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
}

void network::NetworkServer::setupServer() {
  struct sockaddr_in address;
  int opt = 1;

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  // Forcefully attaching socket to the port
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }
}

void network::NetworkServer::startListening() {
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int new_socket;

  while (true) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      perror("accept");
      close(server_fd);
      exit(EXIT_FAILURE);
    }
    handleClient(new_socket);
  }
}

void network::NetworkServer::handleClient(int client_socket) {
  char buffer[1024];
  int valread = read(client_socket, buffer, 1024);
  if (valread > 0) {
    std::string received_data(buffer, valread);
    int num = std::stoi(received_data);
    dataHandler.handleData(buffer, num);
    send(client_socket, buffer, sizeof(buffer), 0);
  }
  close(client_socket);
}

/*networking::NetworkServer::NetworkServer(int port) : port(port),
sock(), listener(socket(AF_INET, SOCK_STREAM, 0)), addr(),dataHandler(handler::DataHandler()){
  if(listener < 0)
  {
    perror("socket\n");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("bind\n");
    exit(2);
  }
  listen(listener, 1);
}

void networking::NetworkServer::connectTo(){
  sock = accept(listener, NULL, NULL);
  if(sock < 0)
  {
    perror("accept");
    exit(3);
  }

  while(true)
  {
    int bytes_read = recv(sock, buf, sizeof(buf), 0);
    if(bytes_read <= 0) break;

    char ans[1024];
    int sum = std::atoi(buf);
    dataHandler.handleData(ans, sum);
    send(sock, ans, sizeof(ans), 0);
  }
  close(sock);
}*/

