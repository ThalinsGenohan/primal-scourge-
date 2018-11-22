#include "Client.h"
#include "discord.h"
#include "TextManager.h"
#include "operators.hpp"

int main()
{
  auto textManager = std::make_shared<TextManager>();

  discord::initDiscord();

  Client client(textManager);

  Discord_Shutdown();
  return 0;
}
