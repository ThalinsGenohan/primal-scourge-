#include "CONSTANTS.h"

#if SERVER_MODE == false
#include <discord_rpc.h>
#include "discord.h"
#include "TextManager.h"
#include "Client.h"
#else
#include "Server.h"
#endif

int main()
{
#if SERVER_MODE == false
  const auto textManager = std::make_shared<TextManager>();
  discord::initDiscord();
  Client client(textManager);
  Discord_Shutdown();
#else
  Server server;
  server.run();
#endif

  return 0;
}
