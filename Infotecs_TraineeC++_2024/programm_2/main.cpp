#include <iostream>

#include "NetworkServer.h"

int main() {
  try {
    network_programm_2::NetworkServer server(3425);
    server.startListening();
  }
  catch(const std::exception& e) {
    std::cerr << "Caught server exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}