#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "NetworkServer.h"

network_program_2::NetworkServer::NetworkServer(int port):
  port(port),
  server_fd(-1),
  dataHandler(handler_program_2::DataHandler())
{
  setupServer();
}

network_program_2::NetworkServer::~NetworkServer() {
  if (server_fd != -1) {
    close(server_fd);
  }
}

void network_program_2::NetworkServer::setupServer() {
  struct sockaddr_in address;
  int opt = 1;

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }
}

void network_program_2::NetworkServer::startListening() {
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

void network_program_2::NetworkServer::handleClient(int client_socket) {
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