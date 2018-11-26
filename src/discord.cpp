#include "discord.h"

#include <iostream>
#include <discord_rpc.h>

#include "CONSTANTS.h"

namespace discord
{
  void handleDiscordReady(const DiscordUser* connectedUser)
  {
    std::cout << "Discord: Connected to user " << connectedUser->username << connectedUser->discriminator << connectedUser->userId << std::endl;
  }

  void handleDiscordErrored(int errcode, const char* message)
  {
    std::cout << "Discord: Error! (" << errcode << ": " << message << ")" << std::endl;
  }

  void handleDiscordDisconnected(int errcode, const char * message)
  {
    std::cout << "Discord: Disconnected. (" << errcode << ": " << message << ")" << std::endl;
  }

  void initDiscord()
  {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof handlers);
    handlers.ready = handleDiscordReady;
    handlers.errored = handleDiscordErrored;
    handlers.disconnected = handleDiscordDisconnected;

    // Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
    Discord_Initialize("515243124533231628", &handlers, 1, "1234");
  }

  void updatePresence(std::wstring status)
  {
    std::string s_status(status.begin(), status.end());

    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof discordPresence);
    discordPresence.state = s_status.c_str();
    discordPresence.details = DISCORD_DETAILS;
    discordPresence.largeImageKey = "canary-large";
    discordPresence.smallImageKey = "ptb-small";
    discordPresence.instance = 1;
    Discord_UpdatePresence(&discordPresence);
  }
}
