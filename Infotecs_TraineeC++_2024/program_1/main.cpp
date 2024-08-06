#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <csignal>
#include <queue>
#include <chrono>
#include <thread>

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
  network::NetworkClient networkClient("127.0.0.1", 3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;
  std::queue<std::string> dataQueue;

  // 1 thread
  sock = networkClient.getSock();
  std::signal(SIGINT, ::handleSignal);
  networkClient.connectTo();

  while(true)
  {
    std::string input = inputHandler.getInput();
    if(input.empty()) continue;
    std::string modified_string = dataProcessor.processData(input);
    dataQueue.push(modified_string);

    bool isAppear = false;
    while (!dataQueue.empty()) {
      if (networkClient.connectTo()) {
        while (!dataQueue.empty()) {
          if(isAppear){
            std::cout << "\nServer Available again!\n";
            isAppear = true;
          }
          std::string front = dataQueue.front();
          dataQueue.pop();
          std::cout << "\nInput string: " << input;
          networkClient.sendData(front);
        }
      } else {
        if(!isAppear){
          std::cout << "\nServer Unavailable\n";
          isAppear = true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
      }
    }
  }
}

/*#include <boost/asio.hpp>

//using boost_tcp = boost::asio::ip::tcp;

}*/