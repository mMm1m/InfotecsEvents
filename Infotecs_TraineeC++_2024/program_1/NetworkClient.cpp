#include <sys/socket.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <numeric>
#include <arpa/inet.h>
#include "assert.h"

#include "NetworkClient.h"

network_program_1::NetworkClient::NetworkClient(const std::string& server_ip, int port):
  server_ip(server_ip),
  sock(-1)
{
  assert(port >= 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (inet_pton(AF_INET, server_ip.c_str(), &addr.sin_addr) <= 0) {
    std::cerr << "\nInvalid address/ Address not supported\n";
    exit(1);
  }
}

bool network_program_1::NetworkClient::connectTo(){
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

void network_program_1::NetworkClient::sendData(std::string& data){
  printf("\nThe string received from the buffer: %s", data.c_str());
  int number = std::accumulate(data.begin(), data.end(), 0,[](int a, char b){
    return std::isdigit(b) ? a+(b-'0'): a;
  });

  std::string s = std::to_string(number);
  char const *packet = s.c_str();

  send(sock, packet, sizeof(packet), 0);
  char ans[1024];

  recv(sock, ans, sizeof(ans), 0);
  printf("\n%s\n", ans);
}

int network_program_1::NetworkClient::getSock() const{
  return this->sock;
}