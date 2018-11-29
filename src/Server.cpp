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
  std::cout << "Added to list..." << std::endl;
  this->_selector.add(*this->_users.back()->getSocket());
  std::cout << "Added to selector" << std::endl;

  const auto username = this->_users.back()->getUsername();
  const auto str = username + " has joined!";
  std::cout << str << std::endl;
  this->send(Message(this->_serverProfile, generalChannel, str, Message::SERVER));

  return true;
}

bool Server::disconnectUser(ServerUser& user)
{
  std::cout << "Disconnecting user..." << std::endl;
  const auto username = user.getUsername();
  const auto str = username + " has disconnected!";
  this->send(Message(this->_serverProfile, generalChannel, str, Message::SERVER));

  std::cout << "Finding user in list..." << std::endl;
  std::list<ServerUser*>::iterator ux;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    if (u.getSocket() == user.getSocket())
    {
      std::cout << "Saving user info..." << std::endl;
      u.saveUser();
      std::cout << "Disconnecting socket..." << std::endl;
      u.getSocket()->disconnect();
      this->_selector.remove(*u.getSocket());
      std::cout << "Deleting user in list..." << std::endl;
    }
  }
  std::cout << "User disconnected!" << std::endl;

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

void Server::run()
{
  std::cout << "Server connected!" << std::endl;

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
                if (!parseMessage(msg))
                {
                  std::cout << "Client disconnecting..." << std::endl;
                  disconnectUser(u);
                  discon = true;
                  disconUser = it;
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
