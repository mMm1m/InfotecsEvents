#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "NetworkServer.h"

networking::NetworkServer::NetworkServer(int port) : port(port),
sock(), listener(socket(AF_INET, SOCK_STREAM, 0)), addr(),dataHandler(handler::DataHandler()){
  if(listener < 0)
  {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("bind");
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
}

