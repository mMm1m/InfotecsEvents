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

int sock;

std::queue<std::pair<std::string, std::string>> dataQueue;
std::mutex queueMutex;
std::mutex otherMutex;
std::condition_variable dataCondition;
std::atomic<bool> stopRequested(false);

void handleSignal(int signal) {
  if (signal == SIGINT) {
    std::unique_lock<std::mutex> lockGuard(queueMutex);
    std::cout << "\nCaught SIGINT, closing socket and exiting...\n" << std::endl;
    stopRequested.store(true);
    dataCondition.notify_all();
    if (sock != -1) {
      close(sock);
      sock = -1;
    }
  }
}

void inputThread(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor) {
  std::unique_lock<std::mutex> lockGuard(queueMutex);
  while (!stopRequested.load()) {
    dataCondition.wait_for(lockGuard, std::chrono::milliseconds(100), [] { return stopRequested.load(); });
    if (stopRequested.load()) {
      break;
    }
    std::string input, modified_string;
    {
      std::unique_lock< std::mutex > guard(otherMutex);
      input = inputHandler.getInput();
      if (input.empty()) continue;
    }
    modified_string = dataProcessor.processData(input);
    dataQueue.emplace(input, modified_string);
    dataCondition.notify_one();
  }
}

void processingThread(network::NetworkClient& networkClient){
  /*bool isServerAvailable = false;

  while (!stopRequested.load() || !dataQueue.empty()) {
    std::pair<std::string, std::string> front;
    bool serverAvailable = networkClient.connectTo();

    {
      std::unique_lock<std::mutex> lock(queueMutex);

      if (serverAvailable) {
        if (isServerAvailable) {
          std::cout << "\nServer Available again!\n";
        }
        isServerAvailable = true;

        // Отправка всех данных из очереди
        while (!dataQueue.empty()) {
          front = dataQueue.front();
          dataQueue.pop();
          std::cout << "\nInput string: " << front.first;
          networkClient.sendData(front.second);
        }
      } else {
        if (isServerAvailable) {
          std::cout << "\nServer Unavailable\n";
        }
        isServerAvailable = false;
        std::this_thread::sleep_for(std::chrono::seconds(2));
      }
    }
  }*/
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
}

int main() {
  std::signal(SIGINT, handleSignal);
  network::NetworkClient networkClient("127.0.0.1", 3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;

  //sock = networkClient.getSock();
  //networkClient.connectTo();

  std::thread inputT(inputThread, std::ref(inputHandler), std::ref(dataProcessor));
  std::thread processingT(processingThread, std::ref(networkClient));

  inputT.join();
  processingT.join();
  return 0;
}


/*namespace multithreading{
  void printMessage(const std::string& string){
    std::unique_lock<std::mutex> lockGuard(coutMutex);
    std::cout << string;
  }

  void pushToQueue(const std::string& input, const std::string& output){
    {
      std::unique_lock< std::mutex > lockGuard(queueMutex);
      dataQueue.emplace(input, output);
    }
    dataCondition.notify_all();
  }
}

namespace {
  void handleSignal(int signal)
  {
    if (signal == SIGINT)
    {
      multithreading::printMessage("\nCaught SIGINT, closing socket and exiting...\n");
      //running = true;
      {
        std::unique_lock<std::mutex> lockGuard(otherMutex);
        stopRequested = true;
      }
      {
        std::unique_lock<std::mutex> lockGuard(otherMutex);
        dataCondition.notify_all();
      }
      close(sock);
    }
  }
}

void inputThread(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor) {
  //while(!running.load()){
  while(!stopRequested){
    {
      std::unique_lock<std::mutex> lockGuard(otherMutex);
      dataCondition.wait_for(lockGuard, std::chrono::milliseconds(100), [] { return !dataQueue.empty() || stopRequested; });
      if(stopRequested) break;
    }
  //if(running.load()) break;
    std::string input, modified_string;
    {
      std::unique_lock< std::mutex > lockGuard(otherMutex);
      input = inputHandler.getInput();
      if (input.empty()) continue;
    }
    modified_string = dataProcessor.processData(input);
    {
      std::lock_guard<std::mutex> lock(queueMutex);
      dataQueue.emplace(input, modified_string);
    }
  }
}*/

// Пространство имен multithreading для функций печати и работы с очередью
/*namespace multithreading {
  void printMessage(const std::string& message) {
    std::unique_lock<std::mutex> lockGuard(coutMutex);
    std::cout << message;
  }

  void pushToQueue(const std::string& input, const std::string& output) {
    {
      std::lock_guard<std::mutex> lockGuard(queueMutex);
      dataQueue.emplace(input, output);
    }
    dataCondition.notify_one();
  }
}

// Анонимное пространство имен для функции обработки сигнала
namespace {
  void handleSignal(int signal) {
    if (signal == SIGINT) {
      multithreading::printMessage("\nCaught SIGINT, exiting...\n");
      {
        std::unique_lock<std::mutex> lockGuard(otherMutex);
        stopRequested.store(true);
      }
      {
        std::lock_guard<std::mutex> lockGuard(otherMutex);
        dataCondition.notify_all();
      }
      close(sock); // Убедитесь, что функция закрывает все ресурсы
    }
  }
}

// Функция для потока ввода данных
void inputThread(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor) {
  while (!stopRequested.load()) {
    std::unique_lock<std::mutex> lockGuard(queueMutex);
    dataCondition.wait_for(lockGuard, std::chrono::milliseconds(100), [] { return !dataQueue.empty() || stopRequested.load(); });
    if (stopRequested.load()) break;
    std::string input, modified_string;
    {
      std::lock_guard<std::mutex> guard(otherMutex);
      input = inputHandler.getInput();
      if(input.empty()) continue;
    }
    modified_string = dataProcessor.processData(input);
    multithreading::pushToQueue(input,modified_string);
  }
}

void processingThread(network::NetworkClient& networkClient){

}

int main()
{
  network::NetworkClient networkClient("127.0.0.1", 3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;

  // 1 thread
  sock = networkClient.getSock();
  std::signal(SIGINT, ::handleSignal);
  //networkClient.connectTo();
  std::thread inputThreadHandle(inputThread, std::ref(inputHandler), std::ref(dataProcessor));
  std::thread processingThreadHandle(processingThread, std::ref(networkClient));

  inputThreadHandle.join();
  processingThreadHandle.join();
}*/

  /*while(true)
  {



  }*/


















namespace {
  /*void handleSignal(int signal)
  {
    if (signal == SIGINT)
    {
      std::cout << "\nCaught SIGINT, closing socket and exiting...\n" << std::endl;
      close(sock);
      exit(0);
    }
  }*/
}

/*void inputThread(handler::InputHandler& inputHandler, processor::DataProcessor& dataProcessor) {
  while (!stopRequested) {
    {
      std::unique_lock< std::mutex > lock(queueMutex);
      dataCondition.wait(lock, [] { return !dataQueue.empty() || stopRequested; });
      if (stopRequested) break;
    }
    std::string input = inputHandler.getInput();
    if (input.empty()) continue;
    std::string modified_string = dataProcessor.processData(input);

    {
      std::lock_guard<std::mutex> lock(queueMutex);
      dataQueue.push(modified_string);
    }

    dataCondition.notify_one();
  }
}

void networkThread(network::NetworkClient& networkClient) {
  bool isAppear = false;
  while (!stopRequested) {
    std::unique_lock<std::mutex> lock(queueMutex);
    dataCondition.wait(lock, [] { return !dataQueue.empty() || stopRequested; });
    if (stopRequested) break;

    while (!dataQueue.empty()) {
      std::string data = dataQueue.front();
      dataQueue.pop();
      lock.unlock();

      if (networkClient.connectTo()) {
        if (isAppear) {
          std::cout << "\nServer Available again!\n";
          isAppear = false;
        }
        std::cout << "\nSending data: " << data;
        networkClient.sendData(data);
      } else {
        if (!isAppear) {
          std::cout << "\nServer Unavailable\n";
          isAppear = true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
      }

      lock.lock();
    }
  }
}

int ma()
{
  network::NetworkClient networkClient("127.0.0.1", 3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;

  sock = networkClient.getSock();
  std::signal(SIGINT, ::handleSignal);

  std::thread inputThreadHandle(inputThread, std::ref(inputHandler), std::ref(dataProcessor));
  std::thread networkThreadHandle(networkThread, std::ref(networkClient));

  inputThreadHandle.join();
  networkThreadHandle.join();

  return 0;
}

  // 1 thread
  /*sock = networkClient.getSock();
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
  }*/



/*

/*int sock;
std::queue<std::string> dataQueue;
std::mutex queueMutex;
std::mutex cout_mutex;
std::condition_variable queueCondition;
std::atomic<bool> running(true); // Atomic flag to signal threads

namespace multithreading {
  void printMessages(const std::string& message) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << message;
  }
}


int main() {
  network::NetworkClient networkClient("127.0.0.1", 3425);
  handler::InputHandler inputHandler;
  processor::DataProcessor dataProcessor;

  sock = networkClient.getSock();
  std::signal(SIGINT, ::handleSignal);
  networkClient.connectTo();

  std::thread inputT(inputThread, std::ref(networkClient), std::ref(inputHandler), std::ref(dataProcessor));
  std::thread networkT(networkThread, std::ref(networkClient));

  // Wait for threads to finish
    inputT.join();
    networkT.join();

  return 0;
}*/

/*std::mutex mtx;

void runA(bool& value, int i) {
  std::lock_guard<std::mutex> lock(mtx); // Захватываем мьютекс
  if (value) {
    // Значение всегда должно быть равным 1
    std::string out = "[ " + std::to_string(i) + " ] value " + std::to_string(value)  + "\n";
    std::cout << out;
  }
}

 void runB(bool& value) {
  std::lock_guard<std::mutex> lock(mtx); // Захватываем мьютекс
  std::cout << "smth" << '\n';
  value = false;
}

int main() {
  for(int i = 0; i < 20;++i) {
    bool value = true;
    std::thread tA(runA, std::ref(value), i);
    std::thread tB(runB, std::ref(value));
    tA.join();
    tB.join();
  }
  return 0;
}*/
