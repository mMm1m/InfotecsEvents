#include <iostream>

#include "../common/network.h"

int main() {
  try {
    network::NetworkServer server(3425);
    server.startListening();
  }
  catch(const std::exception& e) {
    std::cerr << "Caught server exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}