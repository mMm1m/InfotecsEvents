#ifndef INFOTECSEVENTS_WORKER_H
#define INFOTECSEVENTS_WORKER_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>
#include <exception>

#include "InputHandler.h"
#include "DataProcessor.h"
#include "NetworkClient.h"

using dataProc = processor_programm_1::DataProcessor;
using netClient = network_programm_1::NetworkClient;
using inHandler = handler_programm_1::InputHandler;

namespace multithreading_programm_1 {
  class Worker {
    public:
     Worker() = delete;
     Worker(const Worker& other) = delete;
     Worker(Worker&& other) = delete;
     Worker(inHandler& inputHandler, dataProc& dataProcessor,netClient& networkClient);
     ~Worker();
     Worker& operator=(const Worker& other) = delete;
     Worker& operator=(Worker&& other) = delete;
     void start();
     void stop();
     void setupSignalHandler() noexcept;
     bool getValue() const noexcept;

    private:
     handler_programm_1::InputHandler& inputHandler;
     processor_programm_1::DataProcessor& dataProcessor;
     network_programm_1::NetworkClient& networkClient;
     std::thread inputThreadHandle;
     std::thread processingThreadHandle;
     std::exception_ptr workerThreadException;

     std::atomic< bool > stopRequested;
     std::queue< std::pair< std::string, std::string > > dataQueue;
     std::mutex queueMutex;
     std::condition_variable dataCondition;

     static Worker* instance;
     static int sock;

     void inputThread();
     void processingThread();
     void requestStop();
     static void handleSignal(int signal);
  };
}

#endif