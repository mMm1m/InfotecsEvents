#include "NetworkServer.h"

int main()
{
  network::NetworkServer server(3425);
  server.startListening();
  return 0;
}
