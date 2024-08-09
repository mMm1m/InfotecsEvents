#include <thread>
#include <iostream>
#include <csignal>
#include <unistd.h>

#include "../common/network.h"
#include "../common/handler.h"
#include "DataProcessor.h"
#include "ThreadsExecutor.h"

int multithreading::ThreadsExecutor::sock = -1;
multithreading::ThreadsExecutor* multithreading::ThreadsExecutor::instance = nullptr;

multithreading::ThreadsExecutor::ThreadsExecutor():
  inputHandler(handler::InputHandler()),
  dataProcessor(processor::DataProcessor()),
  networkClient(network::NetworkClient("127.0.0.1", 3425)),
  stopRequested(false),
  workerThreadException(nullptr)
{
  instance= this;
  setupSignalHandler();
}

multithreading::ThreadsExecutor::~ThreadsExecutor() {
  try {
    stop();
  }
  catch (const std::exception& e) {}
}

void multithreading::ThreadsExecutor::start() {
  try {
    stopRequested.store(false, std::memory_order_release);
    inputThreadHandle = std::thread(&ThreadsExecutor::inputThread, this);
    processingThreadHandle = std::thread(&ThreadsExecutor::processingThread, this);
  }
  catch (const std::exception& e) {
    std::cerr << "Exception in Worker::start\n";
    stop();
    throw;
  }
}

void multithreading::ThreadsExecutor::stop() {
  requestStop();
  if (inputThreadHandle.joinable()) {
    inputThreadHandle.join();
  }
  if (processingThreadHandle.joinable()) {
    processingThreadHandle.join();
  }
  if (workerThreadException != nullptr) {
    std::rethrow_exception(workerThreadException);
  }
}

void multithreading::ThreadsExecutor::requestStop() {
  {
    std::lock_guard<std::mutex> lock(queueMutex);
    stopRequested.store(true, std::memory_order_release);
    dataCondition.notify_all();
  }
}

void multithreading::ThreadsExecutor::inputThread() {
  try {
    while (!stopRequested.load(std::memory_order_acquire)) {
      std::unique_lock<std::mutex> lock(queueMutex);
      dataCondition.wait_for(lock, std::chrono::milliseconds(100), [this]{
        return stopRequested.load(std::memory_order_acquire);
      });
      if (stopRequested.load(std::memory_order_acquire)) {
        break;
      }
      std::string input = inputHandler.getInput();
      if(input.empty()) continue;
      std::string modified_string = dataProcessor.processData(input);
      dataQueue.emplace(input, modified_string);
      dataCondition.notify_one();
    }
  }
  catch (...) {
    workerThreadException = std::current_exception();
    requestStop();
  }
}

void multithreading::ThreadsExecutor::processingThread() {
  try {
    std::atomic< bool > isServerAvailable(false);
    std::pair< std::string, std::string > data;
    while (true) {
      std::unique_lock< std::mutex > lock(queueMutex);
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
  catch (...) {
    workerThreadException = std::current_exception();
    requestStop();
  }
}

void multithreading::ThreadsExecutor::setupSignalHandler() noexcept {
  std::signal(SIGINT, ThreadsExecutor::handleSignal);
}

void multithreading::ThreadsExecutor::handleSignal(int signal) {
  if (signal == SIGINT) {
    if (instance) {
      {
        std::unique_lock<std::mutex> lockGuard(instance->queueMutex);
        std::cout << "\nCaught SIGINT, closing socket and exiting...\n";
      }
      instance->requestStop();
      if (sock != -1) {
        close(sock);
        sock = -1;
      }
    }
  }
}

bool multithreading::ThreadsExecutor::getValue() const noexcept {
  return stopRequested.load();
}