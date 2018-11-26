#include "Server.h"

#include <iostream>
#include <SFML/Network.hpp>

#include "CONSTANTS.h"
#include "Channel.h"
#include "Message.h"


Server::Server(): _serverUser(0, "[Server]", sf::Color::Cyan), _userCount(0)
{
  this->_listener.listen(PORT);
  this->_selector.add(this->_listener);
}

bool Server::connectUser(sf::TcpSocket* socket)
{
  this->_users.push_back(ServerUser(socket));
  this->_selector.add(*this->_users.back().getSocket());

  const auto username = this->_users.back().getUsername();
  this->send(Message(this->_serverUser, generalChannel, username + " has joined!", Message::SERVER));

  return true;
}

bool Server::disconnectUser(ServerUser user)
{
  const auto username = user.getUsername();

  this->send(Message(this->_serverUser, generalChannel, username + " has disconnected!", Message::SERVER));

  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    if (it->getIpAddress() == user.getIpAddress())
    {
      it->saveUser();
      it->getSocket()->disconnect();
      this->_selector.remove(*it->getSocket());
      this->_users.erase(it);
    }
  }

  return true;
}

bool Server::send(Message msg)
{
  std::cout << msg;
  sf::Packet packet;
  packet << msg;
  for (auto i = 0; i < int(this->_users.size()); i++)
  {
    auto& user = this->_users[i];
    user.getSocket()->send(packet);
  }
  return false;
}

void Server::run()
{
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
          connectUser(client);
        }
        else
        {
          delete client;
        }
      }
      else
      {
        for (auto i = 0; i < int(this->_users.size()); i++)
        {
          auto& u = this->_users[i];
          if (this->_selector.isReady(*u.getSocket()))
          {
            sf::Packet packet;
            if (u.getSocket()->receive(packet) == sf::Socket::Done)
            {
              Message msg;
              if (!(packet >> msg))
              {
                if (msg.getMessage()[0] == '/')
                {
                  switch (msg.getMessage()[1])
                  {
                  case 'd':
                    disconnectUser(u);
                    break;
                  default: ;
                  }
                }
                else
                {
                  this->send(msg);
                }
              }
            }
          }
        }
      }
    }
  }
  for (auto i = 0; i < int(this->_users.size()); i++)
  {
    this->_users[i].getSocket()->disconnect();
  }
  this->_selector.clear();
  this->_listener.close();
}
