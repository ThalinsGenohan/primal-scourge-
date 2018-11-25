#include "discord.h"
#include "TextManager.h"
#include "operators.hpp"
#include "Server.h"

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
