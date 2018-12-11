#include "pch.h"
#include "CONSTANTS.h"

#ifdef _CLIENT
#include <discord_rpc.h>
#include "discord.h"
#include "TextManager.h"
#include "Client.h"
#elif defined(_SERVER)
#include "Server.h"
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int /*argc*/, char** /*argv*/)
{
#ifdef _SERVER
#ifdef _WIN32
#ifdef NDEBUG
  ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#endif
#endif
  srand(unsigned(time(nullptr)));

#ifdef _CLIENT
  std::cout << "Starting Client..." << std::endl;
  const auto textManager = std::make_shared<TextManager>();
  discord::initDiscord();
  Client client(textManager);
  client.disconnect();
  Discord_Shutdown();
#elif defined(_SERVER)
  Server server;
  server.run();
#else
  std::cout << "Neither _CLIENT nor _SERVER are defined!" << std::endl;
#endif
  std::cout << "End. Closing program..." << std::endl;
  return 0;
}
