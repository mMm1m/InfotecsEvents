#include <sys/socket.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <algorithm>
#include <numeric>
#include "NetworkClient.h"

network::NetworkClient::NetworkClient(int port) : sock(socket(AF_INET, SOCK_STREAM, 0)), port(port), addr(){
  if(sock < 0)
  {
    perror("socket");
    exit(1);
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

void network::NetworkClient::connectTo(){
  if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("connect");
    exit(2);
  }
}

void network::NetworkClient::sendData(std::string& data){
  printf("The string received from the buffer: %s\n", data.c_str());
  int number = std::accumulate(data.begin(), data.end(), 0,[](int a, char b){return std::isdigit(b) ? a+(b-'0'): a;});

  std::string s = std::to_string(number);
  char const *packet = s.c_str();

  send(sock, packet, sizeof(packet), 0);
  char ans[1024];

  recv(sock, ans, sizeof(ans), 0);
  printf("%s", ans);
}

int network::NetworkClient::getSock(){
  return this->sock;
}

