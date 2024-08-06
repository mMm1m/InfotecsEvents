#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <csignal>

#include "NetworkClient.h"
#include "InputHandler.h"
#include "DataProcessor.h"

int sock;
std::string buffer;
bool bufferIsNotEmpty = false;

namespace {
  void handleSignal(int signal)
  {
    if (signal == SIGINT)
    {
      std::cout << "\nCaught SIGINT, closing socket and exiting...\n" << std::endl;
      close(sock);
      exit(0);
    }
  }
}

int main()
{
  network::NetworkClient networkClient(3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;
  // 1 thread
  //char buf[1024];
  //int bytes_read;
  sock = networkClient.getSock();
  std::signal(SIGINT, ::handleSignal);
  networkClient.connectTo();

  while(true)
  {
    std::string input = inputHandler.getInput();
    if(input.empty()) continue;
    std::string modified_string = dataProcessor.processData(input);

    buffer = modified_string;
    bufferIsNotEmpty = true;

    // 2 thread
    std::string data = buffer;
    buffer.clear();
    bufferIsNotEmpty = false;

    networkClient.sendData(data);
  }
}

/*#include <boost/asio.hpp>

//using boost_tcp = boost::asio::ip::tcp;

}*/