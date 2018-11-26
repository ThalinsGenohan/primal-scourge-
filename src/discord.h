#ifndef DISCORD_H
#define DISCORD_H

#include <string>

class DiscordUser;

namespace discord
{
  void handleDiscordReady(const DiscordUser* connectedUser);
  void handleDiscordErrored(int errcode, const char* message);
  void handleDiscordDisconnected(int errcode, const char* message);
  //void handleDiscordJoinGame(const char* secret);
  //void handleDiscordSpectateGame(const char* secret);
  //void handleDiscordJoinRequest(const DiscordUser* request);

  void initDiscord();
  void updatePresence(std::wstring status);
}

#endif
