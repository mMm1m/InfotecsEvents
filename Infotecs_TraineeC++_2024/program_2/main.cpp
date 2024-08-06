#include "NetworkServer.h"

int main()
{
  networking::NetworkServer server(3425);
  while(true)
  {
    server.connectTo();
  }
}
