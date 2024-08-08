#include <chrono>
#include <thread>
#include <iostream>

#include "NetworkClient.h"
#include "InputHandler.h"
#include "DataProcessor.h"
#include "Worker.h"

int main() {
  try {
    handler_programm_1::InputHandler inputHandler;
    processor_programm_1::DataProcessor dataProcessor;
    network_programm_1::NetworkClient networkClient("127.0.0.1", 3425);

    multithreading_programm_1::Worker worker(inputHandler, dataProcessor, networkClient);
    worker.start();
    while (!worker.getValue()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    worker.stop();
  }
  catch(const std::exception& e) {
    std::cerr << "Exception caught: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}