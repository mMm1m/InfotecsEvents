#include <sys/socket.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <algorithm>
#include <numeric>
#include <arpa/inet.h>
#include <cstring>
#include "NetworkClient.h"


network::NetworkClient::NetworkClient(const std::string& server_ip, int port) : server_ip(server_ip), sock(-1), port(port), addr(){
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (inet_pton(AF_INET, server_ip.c_str(), &addr.sin_addr) <= 0) {
    std::cerr << "\nInvalid address/ Address not supported\n";
    exit(1);
  }
}

bool network::NetworkClient::connectTo(){
  if (sock != -1) {
    close(sock);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("\nsocket\n");
    return false;
  }

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    close(sock);
    sock = -1;
    return false;
  }
  return true;
}

void network::NetworkClient::sendData(std::string& data){
  printf("\nThe string received from the buffer: %s", data.c_str());
  int number = std::accumulate(data.begin(), data.end(), 0,[](int a, char b){return std::isdigit(b) ? a+(b-'0'): a;});

  std::string s = std::to_string(number);
  char const *packet = s.c_str();

  send(sock, packet, sizeof(packet), 0);
  char ans[1024];

  recv(sock, ans, sizeof(ans), 0);
  printf("\n%s\n", ans);
}

int network::NetworkClient::getSock(){
  return this->sock;
}

