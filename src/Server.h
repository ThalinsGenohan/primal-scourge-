#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <SFML/Network.hpp>

#include "ServerUser.h"
#include "Message.h"
#include "ServerPacket.h"

class Message;

class Server
{
  std::promise<void> _exitSignal;
  std::future<void> _futureObj;
public:
  Server();

  bool connectUser(sf::TcpSocket* socket);
  bool disconnectUser(std::list<ServerUser*>::iterator user);

  char parseMessage(Message msg);
  //bool send(Message msg);
  //bool send(Message msg, User u);
  bool send(ServerPacket packet);

  void run();
  void close();

  void operator()() { this->run(); }

  bool stopRequested() const;
  void stop() { _exitSignal.set_value(); }

private:
  User _serverProfile;

  sf::IpAddress _ipAddress;
  sf::TcpListener _listener;
  sf::SocketSelector _selector;

  sf::UdpSocket _connectionSocket;

  int _userCount;
  std::list<ServerUser*> _users;
  std::list<Channel*> _channels;

  bool _running;
};

#endif
