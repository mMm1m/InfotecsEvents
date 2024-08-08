#include "NetworkServer.h"

int main()
{
  network_program_2::NetworkServer server(3425);
  server.startListening();
  return 0;
}