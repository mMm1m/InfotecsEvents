#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace g_output{
  int digitsCount(int number){
    int symCount = 0;
    while (number > 0)
    {
      ++symCount;
      number /= 10;
    }
    return symCount;
  }
  int exp(int a, int b){
    if(b == 1) return a;
    if(b%2 == 0) return ((exp(a,b/2))*(exp(a,b/2)));
    return (a*(exp(a,b-1)));
  }
}


int main()
{
  int sock, listener;
  struct sockaddr_in addr;
  char buf[1024];
  int bytes_read;

  listener = socket(AF_INET, SOCK_STREAM, 0);
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

  while(true)
  {
    sock = accept(listener, NULL, NULL);
    if(sock < 0)
    {
      perror("accept");
      exit(3);
    }

    while(true)
    {
      bytes_read = recv(sock, buf, sizeof(buf), 0);
      if(bytes_read <= 0) break;

      char ans[1024];
      int sum = std::atoi(buf);
      if(sum > 99 && ((sum&31) == 0)){
        sprintf(ans, "Received value is %d , amount of symbols is %d\n", sum, g_output::digitsCount(sum));
      }
      else{
        strcpy(ans , "Invalid output data\n");
        std::cerr << "Invalid output data" << '\n';
      }
      send(sock, ans, sizeof(ans), 0);
    }
    close(sock);
  }
}
