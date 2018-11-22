#include "Client.h"
#include "discord.h"

int main()
{
  discord::initDiscord();

  Client client;

  Discord_Shutdown();

  return 0;
}
