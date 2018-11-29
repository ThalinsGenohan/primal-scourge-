#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <SFML/Network.hpp>

#include "ServerUser.h"

class Message;

class Server
{
public:
  Server();

  bool connectUser(sf::TcpSocket* socket);
  bool disconnectUser(std::list<ServerUser*>::iterator user);

  bool parseMessage(Message msg);
  bool send(Message msg);

  void run();

private:
  User _serverProfile;

  sf::IpAddress _ipAddress;
  sf::TcpListener _listener;
  sf::SocketSelector _selector;

  int _userCount;
  std::list<ServerUser*> _users;

};

#endif
