#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>
#include <stdexcept>
#include <iostream>

#include "NetworkServer.h"

network_programm_2::NetworkServer::NetworkServer(int port):
  port(port),
  server_fd(-1),
  dataHandler(handler_programm_2::DataHandler())
{
  assert(port >= 0);
  setupServer();
}

network_programm_2::NetworkServer::~NetworkServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
}

void network_programm_2::NetworkServer::setupServer() {
  struct sockaddr_in address;
  int opt = 1;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    throw std::runtime_error("Socket creation failed\n");
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    close(server_fd);
    throw std::runtime_error("Setsockopt failed\n");
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    close(server_fd);
    throw std::runtime_error("Bind failed\n");
  }
}

void network_programm_2::NetworkServer::startListening() {
  if (listen(server_fd, 3) < 0) {
    close(server_fd);
    throw std::runtime_error("Listen failed\n");
  }

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int new_socket;

  while (true) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      close(server_fd);
      throw std::runtime_error("Accept failed\n");
    }
    handleClient(new_socket);
  }
}

void network_programm_2::NetworkServer::handleClient(int client_socket) {
  try {
    char buffer[1024];
    int valread = read(client_socket, buffer, sizeof(buffer));
    if (valread < 0) {
      throw std::runtime_error("Error reading from socket\n");
    }

    if (valread > 0) {
      std::string received_data(buffer, valread);
      int num = std::stoi(received_data);
      dataHandler.handleData(buffer, num);
      if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        throw std::runtime_error("Error sending data\n");
      }
    }
    close(client_socket);
  }
  catch (const std::exception& e) {
    std::cerr << "Exception in during execution of client request\n";
    close(client_socket);
    throw;
  }
}