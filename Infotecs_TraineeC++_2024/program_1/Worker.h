#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

#ifndef INFOTECSEVENTS_WORKER_H
#define INFOTECSEVENTS_WORKER_H
#include "InputHandler.h"
#include "DataProcessor.h"
#include "NetworkClient.h"


class Worker {
  public:
   Worker(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor, network::NetworkClient& networkClient);
   ~Worker();
   void start();
   void stop();
   void setupSignalHandler();

   std::atomic<bool> stopRequested;

  private:
   void inputThread();
   void processingThread();
   void requestStop();

   static void handleSignal(int signal);

   handler::InputHandler& inputHandler;
   processor::DataProcessor& dataProcessor;
   network::NetworkClient& networkClient;
   std::thread inputThreadHandle;
   std::thread processingThreadHandle;

   std::queue<std::pair<std::string, std::string>> dataQueue;
   std::mutex queueMutex;
   std::condition_variable dataCondition;

   static Worker* instance;
   static int  sock;
};

#endif
