#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <csignal>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "NetworkClient.h"
#include "InputHandler.h"
#include "DataProcessor.h"
#include "Worker.h"

//int sock;

std::queue<std::pair<std::string, std::string>> dataQueue;
std::mutex queueMutex;
std::condition_variable dataCondition;
std::atomic<bool> stopRequested(false);

/*void handleSignal(int signal) {
  if (signal == SIGINT) {
    std::lock_guard<std::mutex> lock(queueMutex);
    std::cout << "\nCaught SIGINT, closing socket and exiting...\n";
    stopRequested = true;
    dataCondition.notify_all();
    //buffer_.requestStop();
    if (sock != -1) {
      close(sock);
      sock = -1;
    }
  }
}*/

/*void inputThread(Buffer& buffer, handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor) {
  std::unique_lock<std::mutex> lockGuard(queueMutex);
  while (!stopRequested.load()) {
    dataCondition.wait_for(lockGuard, std::chrono::milliseconds(100), [] { return stopRequested.load(); });
    if (stopRequested.load()) {
      break;
    }
    std::string input, modified_string;
    {
      std::mutex otherMutex;
      std::unique_lock< std::mutex > guard(otherMutex);
      input = inputHandler.getInput();
      if (input.empty()) continue;
    }
    modified_string = dataProcessor.processData(input);
    dataQueue.emplace(input, modified_string);
    dataCondition.notify_one();
  }
}

void processingThread(Buffer& buffer ,network::NetworkClient& networkClient){
  bool isServerAvailable = false;

  while (!stopRequested.load() || !dataQueue.empty()) {
    std::pair<std::string, std::string> front;
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      dataCondition.wait(lock, [] { return stopRequested.load() || !dataQueue.empty(); });

      if (!dataQueue.empty()) {
        front = dataQueue.front();
        dataQueue.pop();
      } else {
        continue;
      }
    }

    if (networkClient.connectTo()) {
      if (isServerAvailable) {
        std::cout << "\nServer Available again!\n";
        isServerAvailable = false;
      }
      std::cout << "\nInput string: " << front.first;
      networkClient.sendData(front.second);
    } else {
      std::cout << "\nServer Unavailable\n";
      isServerAvailable = true;
    }
  }
}*/

int main() {
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;
  network::NetworkClient networkClient("127.0.0.1", 3425);

  Worker worker(inputHandler, dataProcessor, networkClient);
  worker.start();
  while (!worker.stopRequested.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  worker.stop();
  return 0;
}