#include <discord_rpc.h>

#include "discord.h"
#include "Server.h"
#include "TextManager.h"

int main()
{
  const auto textManager = std::make_shared<TextManager>();

  discord::initDiscord();

  Server server;
  server.run();

  //Client client(textManager);

  Discord_Shutdown();
  return 0;
}
