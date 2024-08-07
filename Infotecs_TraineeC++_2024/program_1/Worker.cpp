

#include <thread>
#include <iostream>
#include <csignal>
#include <unistd.h>

#include "Worker.h"

int Worker::sock = -1;
Worker* Worker::instance = nullptr;

Worker::Worker(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor, network::NetworkClient& networkClient)
  : inputHandler(inputHandler), dataProcessor(dataProcessor), networkClient(networkClient), stopRequested(false)
  {
  instance= this;
  setupSignalHandler();
}

Worker::~Worker() {
  stop();
}

void Worker::start() {
  stopRequested.store(false, std::memory_order_release);
  inputThreadHandle = std::thread(&Worker::inputThread, this);
  processingThreadHandle = std::thread(&Worker::processingThread, this);
}

void Worker::stop() {
  requestStop();
  if (inputThreadHandle.joinable()) {
    inputThreadHandle.join();
  }
  if (processingThreadHandle.joinable()) {
    processingThreadHandle.join();
  }
}

void Worker::requestStop() {
  {
  std::lock_guard<std::mutex> lock(queueMutex);
  stopRequested.store(true, std::memory_order_release);
  dataCondition.notify_all();
  }
}

  void Worker::inputThread() {
    while (!stopRequested.load(std::memory_order_acquire)) {
      std::unique_lock<std::mutex> lock(queueMutex);
      dataCondition.wait_for(lock, std::chrono::milliseconds(100), [this] { return stopRequested.load(std::memory_order_acquire); });
      if (stopRequested.load(std::memory_order_acquire)) {
        break;
      }
      std::string input = inputHandler.getInput();
      if (input.empty()) continue;
      std::string modified_string = dataProcessor.processData(input);
      dataQueue.emplace(input, modified_string);
      dataCondition.notify_one();
    }
  }

void Worker::processingThread() {
  std::atomic<bool> isServerAvailable(false);
  std::pair<std::string, std::string> data;
  while (true) {
    std::unique_lock<std::mutex> lock(queueMutex);
    dataCondition.wait(lock, [this] {
      return stopRequested.load(std::memory_order_acquire) || !dataQueue.empty();
    });

    if (stopRequested.load(std::memory_order_acquire) && dataQueue.empty()) {
      break;
    }

    if (!dataQueue.empty()) {
      data = dataQueue.front();
      dataQueue.pop();
    }
    if (networkClient.connectTo()) {
      if (isServerAvailable) {
        std::cout << "\nServer Available again!\n";
        isServerAvailable = false;
      }
      std::cout << "\nInput string: " << data.first;
      lock.unlock();
      networkClient.sendData(data.second);
      lock.lock();
    } else {
      std::cout << "\nServer Unavailable\n";
      isServerAvailable = true;
    }
  }
}

void Worker::setupSignalHandler() {
  std::signal(SIGINT, Worker::handleSignal);
}

void Worker::handleSignal(int signal) {
  if (signal == SIGINT) {
    if (instance) {
      instance->requestStop();
      if (sock != -1) {
        close(sock);
        sock = -1;
      }
    }
  }
}


