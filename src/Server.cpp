#include "Server.h"

#include <iostream>
#include <SFML/Network.hpp>

#include "CONSTANTS.h"
#include "Channel.h"
#include "Message.h"
#include "ServerUser.h"


Server::Server() : _serverProfile(0, "[Server]", sf::Color::Cyan), _userCount(0)
{
  this->_listener.listen(PORT);
  this->_selector.add(this->_listener);
}

bool Server::connectUser(sf::TcpSocket* socket)
{
  this->_users.push_back(new ServerUser(socket));
  this->_selector.add(*this->_users.back()->getSocket());

  const auto username = this->_users.back()->getUsername();
  this->send(Message(this->_serverProfile, generalChannel, username + " has joined!", Message::SERVER));

  return true;
}

bool Server::disconnectUser(ServerUser user)
{
  const auto username = user.getUsername();

  this->send(Message(this->_serverProfile, generalChannel, username + " has disconnected!", Message::SERVER));

  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    if (u.getIpAddress() == user.getIpAddress())
    {
      u.saveUser();
      u.getSocket()->disconnect();
      this->_selector.remove(*u.getSocket());
      this->_users.erase(it);
    }
  }

  return true;
}

bool Server::parseMessage(Message msg)
{
  if (msg.getMessage()[0] == '/')
  {
    switch (msg.getMessage()[1])
    {
    case 'd':
      return false;
    default:;
    }
  }
  else
  {
    this->send(msg);
  }
  return true;
}

bool Server::send(Message msg)
{
  std::cout << msg.getUser().getUsername() << msg.getMessage() << std::endl;
  sf::Packet packet;
  packet << msg;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& user = **it;
    user.getSocket()->send(packet);
  }
  return false;
}

void Server::run()
{
  std::cout << "Server connected!" << std::endl;

  auto loop = true;
  while (loop)
  {
    if (this->_selector.wait())
    {
      if (this->_selector.isReady(this->_listener))
      {
        const auto client = new sf::TcpSocket;
        if (this->_listener.accept(*client) == sf::Socket::Done)
        {
          /*this->_users.push_back(new ServerUser(client));
          this->_selector.add(*client);*/

          const auto username = this->_users.back()->getUsername();
          this->send(Message(this->_serverProfile, generalChannel, username + " has joined!", Message::SERVER));
        }
        else
        {
          delete client;
        }
      }
      else
      {
        for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
        {
          auto& u = **it;
          if (this->_selector.isReady(*u.getSocket()))
          {
            sf::Packet packet;
            if (u.getSocket()->receive(packet) == sf::Socket::Done)
            {
              Message msg;
              if (packet >> msg)
              {
                if (!parseMessage(msg))
                {
                  disconnectUser(u);
                }
              }
            }
          }
        }
      }
    }
  }
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    u.getSocket()->disconnect();
  }
  this->_selector.clear();
  this->_listener.close();
}
