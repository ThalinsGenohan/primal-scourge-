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
  const auto su = this->_users.back();
  std::cout << "Added to list..." << std::endl;
  this->_selector.add(*su->getSocket());
  std::cout << "Added to selector" << std::endl;

  std::cout << "Sending User info to Client..." << std::endl;
  sf::Packet p;
  const auto u = User(su->getId(), su->getUsername(), su->getColor());
  p << u;
  su->getSocket()->send(p);
  std::cout << "User info sent!";

  const auto username = su->getUsername();
  const auto str = username + J_STR;
  this->send(Message(this->_serverProfile, generalChannel, str, Message::SERVER), u);

  return true;
}

bool Server::disconnectUser(std::list<ServerUser*>::iterator user)
{
  auto& u = **user;
  std::cout << "Disconnecting user..." << std::endl;
  const auto str = u.getUsername() + D_STR;
  this->send(Message(this->_serverProfile, generalChannel, str, Message::SERVER), User(u.getId(), u.getUsername(), u.getColor()));
  std::cout << "Saving user info..." << std::endl;
  u.saveUser();
  std::cout << "Disconnecting socket..." << std::endl;
  this->_selector.remove(*u.getSocket());
  u.getSocket()->disconnect();
  std::cout << "Deleting user in list..." << std::endl;
  std::cout << "User disconnected!" << std::endl;

  return true;
}

char Server::parseMessage(Message msg)
{
  if (msg.getMessage()[0] == '/')
  {
    const auto s = msg.getMessage().substr(1, msg.getMessage().find_first_of(" ") - 1);
    
    if (s == "d")
    {
      return 'd';
    }
    if (s == "u")
    {
      this->send(Message(_serverProfile, generalChannel, msg.getUser().getUsername() + C_STR + msg.getMessage().substr(3), Message::SERVER), User(msg.getUser().getId(), msg.getMessage().substr(3), msg.getUser().getColor()));
      return 'u';
    }
    if (s == "c")
    {
      return 'c';
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
  std::cout << msg.getUser().getUsername() << ": " << msg.getMessage() << std::endl;
  sf::Packet packet;
  packet << msg;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& user = **it;
    user.getSocket()->send(packet);
  }
  return false;
}

bool Server::send(Message msg, User u)
{
  std::cout << msg.getUser().getUsername() << ": " << msg.getMessage() << std::endl;
  sf::Packet packet;
  packet << msg << u;
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

  // ReSharper disable once CppLocalVariableMayBeConst
  auto loop = true;
  auto discon = false;
  std::list<ServerUser*>::iterator disconUser;
  while (loop)
  {
    if (discon)
    {
      this->_users.erase(disconUser);
      discon = false;
    }

    if (this->_selector.wait())
    {
      if (this->_selector.isReady(this->_listener))
      {
        const auto client = new sf::TcpSocket;
        if (this->_listener.accept(*client) == sf::Socket::Done)
        {
          std::cout << "Client connecting..." << std::endl;
          connectUser(client);
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
              std::cout << "Incoming message!" << std::endl;
              Message msg;
              if (packet >> msg)
              {
                switch (parseMessage(msg))
                {
                case 'd':
                  std::cout << "Client disconnecting..." << std::endl;
                  disconnectUser(it);
                  discon = true;
                  disconUser = it;
                  break;
                case 'u':
                  u.setUsername(msg.getMessage().substr(3));
                  break;
                case 'c':
                  u.setColor(msg.getMessage().substr(3));
                  break;
                default:;
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
