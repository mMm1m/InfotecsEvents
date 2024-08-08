#include <chrono>
#include <thread>

#include "NetworkClient.h"
#include "InputHandler.h"
#include "DataProcessor.h"
#include "Worker.h"

int main() {
  handler_program_1::InputHandler inputHandler;
  processor_program_1::DataProcessor dataProcessor;
  network_program_1::NetworkClient networkClient("127.0.0.1", 3425);

  multithreading_program_1::Worker worker(inputHandler, dataProcessor, networkClient);
  worker.start();
  while (!worker.stopRequested.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  worker.stop();
  return 0;
}