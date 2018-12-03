#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <SFML/Network.hpp>

#include "ServerUser.h"
#include "Message.h"
#include <iostream>

class Message;

class Server
{
public:
  Server();

  bool connectUser(sf::TcpSocket* socket);
  bool disconnectUser(std::list<ServerUser*>::iterator user);

  char parseMessage(Message msg);
  template<typename T>
  bool send(Message msg, T extra = nullptr)
  {
    std::cout << msg.getUser().getUsername() << ": " << msg.getMessage() << std::endl;
    sf::Packet packet;
    packet << msg;
    if (extra != nullptr)
    {
      packet << extra;
    }
    for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
    {
      auto& user = **it;
      user.getSocket()->send(packet);
    }
    return false;
  }

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
