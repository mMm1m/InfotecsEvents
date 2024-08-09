#include <chrono>
#include <thread>
#include <iostream>

#include "ThreadsExecutor.h"

int main() {
  try {
    multithreading::ThreadsExecutor worker;
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