#include <sys/socket.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <numeric>
#include <arpa/inet.h>

#include "NetworkClient.h"

network_programm_1::NetworkClient::NetworkClient(const std::string& server_ip, int port):
  server_ip(server_ip),
  sock(-1)
{
  if(port < 0) {
    throw std::runtime_error("Incorrect port\n");
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (inet_pton(AF_INET, server_ip.c_str(), &addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid address or address not supported\n");
  }
}

bool network_programm_1::NetworkClient::connectTo(){
  if (sock != -1) {
    close(sock);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    throw std::runtime_error("Failed to create socket\n");
  }

  if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    close(sock);
    sock = -1;
    return false;
  }
  return true;
}

void network_programm_1::NetworkClient::sendData(std::string& data){
  printf("\nThe string received from the buffer: %s", data.c_str());
  int number = std::accumulate(data.begin(), data.end(), 0,[](int a, char b){
    return std::isdigit(b) ? a+(b-'0'): a;
  });

  std::string s = std::to_string(number);
  char const *packet = s.c_str();

  if (send(sock, packet, s.size(), 0) < 0) {
    throw std::runtime_error("\nFailed to send data\n");
  }

  char ans[1024];
  ssize_t received = recv(sock, ans, sizeof(ans) - 1, 0);
  if (received <= 0) {
    std::cerr << "\nFailed to receive data , exception on server side\n";
  }
  ans[received] = '\0';
  printf("\n%s\n", ans);
}

int network_programm_1::NetworkClient::getSock() const noexcept{
  return this->sock;
}