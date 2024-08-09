#ifndef INFOTECSEVENTS_THREADSEXECUTOR_H
#define INFOTECSEVENTS_THREADSEXECUTOR_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <queue>
#include <exception>

#include "../common/handler.h"
#include "DataProcessor.h"
#include "../common/network.h"

namespace multithreading {
  class ThreadsExecutor {
    public:
     ThreadsExecutor();
     ThreadsExecutor(const ThreadsExecutor& other) = delete;
     ThreadsExecutor(ThreadsExecutor&& other) = delete;
     ~ThreadsExecutor();
     ThreadsExecutor& operator=(const ThreadsExecutor& other) = delete;
     ThreadsExecutor& operator=(ThreadsExecutor&& other) = delete;
     void start();
     void stop();
     void setupSignalHandler() noexcept;
     bool getValue() const noexcept;

    private:
     handler::InputHandler inputHandler;
     processor::DataProcessor dataProcessor;
     network::NetworkClient networkClient;
     std::thread inputThreadHandle;
     std::thread processingThreadHandle;
     std::exception_ptr workerThreadException;

     std::atomic< bool > stopRequested;
     std::queue< std::pair< std::string, std::string > > dataQueue;
     std::mutex queueMutex;
     std::condition_variable dataCondition;

     static ThreadsExecutor* instance;
     static int sock;

     void inputThread();
     void processingThread();
     void requestStop();
     static void handleSignal(int signal);
  };
}

#endif