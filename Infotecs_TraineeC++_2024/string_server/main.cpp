#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/stdc++.h>

int sock;
std::string buffer;
bool bufferIsNotEmpty = false;

namespace g_string{
  template< class UnaryPred >
  std::string replace_if_custom(std::string& input_string, UnaryPred p, const std::string& replacement, size_t evenCount)
  {
    std::string modified_string;
    modified_string.reserve(input_string.size()+evenCount);
    std::for_each(input_string.begin(), input_string.end(), [&](char c) {
      std::string tmp_string = !p(c) ? std::to_string(c-'0') : replacement;
      modified_string += tmp_string;
    });
    return modified_string;
  }

  bool isEven(char c)
  {
    return ((c - '0') & 1) == 0;
  }

  bool checkInput(const std::string& str)
  {
    for(auto& a : str){
      if(!isdigit(a)){
        return false;
      }
    }
    return true;
  }
  int exp(int a, int b){
    if(b == 1) return a;
    if(b%2 == 0) return ((exp(a,b/2))*(exp(a,b/2)));
    return (a*(exp(a,b-1)));
  }
  void handle_signal(int signal)
  {
    if (signal == SIGINT)
    {
      std::cout << "Caught SIGINT, closing socket and exiting..." << std::endl;
      close(sock);
      exit(0);
    }
  }

}

int main()
{
  struct sockaddr_in addr;
  char buf[1024];
  int bytes_read;
  std::signal(SIGINT, g_string::handle_signal);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("connect");
    exit(2);
  }

  while(true)
  {
    std::string str;
    std::getline(std::cin, str);
    if(str.size() > 64 || !g_string::checkInput(str)){
      std::cerr << "Incorrect input string";
      continue;
    }
    size_t evenCount = std::count_if(str.begin(), str.end(), g_string::isEven);
    std::sort(str.rbegin(), str.rend());
    std::string output_string = g_string::replace_if_custom(str,g_string::isEven,"KB", evenCount);

    buffer = output_string;
    bufferIsNotEmpty = true;

    std::string data = buffer;
    buffer.clear();
    bufferIsNotEmpty = false;
    int number = std::accumulate(data.begin(), data.end(), 0,[](int a, char b){return std::isdigit(b) ? a+(b-'0'): a;});

    std::string s = std::to_string(number);
    char const *packet = s.c_str();

    send(sock, packet, sizeof(packet), 0);
    char ans[1024];

    recv(sock, ans, sizeof(ans), 0);
    printf("%s", ans);
  }
}

/*#include <boost/asio.hpp>

//using boost_tcp = boost::asio::ip::tcp;

}*/