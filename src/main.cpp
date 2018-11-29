#ifdef _CLIENT
#include <discord_rpc.h>
#include "discord.h"
#include "TextManager.h"
#include "Client.h"
#elif defined(_SERVER)
#include "Server.h"
#endif

int main()
{
  srand(unsigned(time(nullptr)));
#ifdef _CLIENT
  const auto textManager = std::make_shared<TextManager>();
  discord::initDiscord();
  Client client(textManager);
  client.disconnect();
  Discord_Shutdown();
#elif defined(_SERVER)
  Server server;
  server.run();
#endif

  return 0;
}
