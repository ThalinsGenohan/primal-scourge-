#include "pch.h"
#include "Server.h"

#include "CONSTANTS.h"
#include "Channel.h"
#include "Message.h"
#include "ServerUser.h"

std::list<User> serverUsersToUsers(std::list<ServerUser*> serverUsers)
{
  std::list<User> users;
  for (auto it = serverUsers.begin(); it != serverUsers.end(); ++it)
  {
    auto& su = **it;
    users.push_back(su);
  }
  return users;
}

Server::Server() : _serverProfile(0, "[Server]", sf::Color::Cyan), _userCount(0)
{
  this->_listener.listen(PORT);
  this->_selector.add(this->_listener);
  this->_connectionSocket.bind(PORT);
  this->_selector.add(this->_connectionSocket);
}

bool Server::connectUser(sf::TcpSocket* socket)
{
  this->_users.push_back(new ServerUser(socket));
  const auto su = this->_users.back();
  //std::cout << "Added to list..." << std::endl;
  this->_selector.add(*su->getSocket());
  //std::cout << "Added to selector" << std::endl;

  //std::cout << "Sending User info to Client..." << std::endl;
  sf::Packet p;
  const auto u = User(su->getId(), su->getUsername(), su->getColor());
  p << u;
  su->getSocket()->send(p);
  //std::cout << "User info sent!";

  const auto username = su->getUsername();
  const auto str = J_STR(username);
  this->send(
    ServerPacket(
      Message(
        this->_serverProfile,
        GENERAL_CHANNEL,
        str,
        Message::SERVER
      ),
      serverUsersToUsers(this->_users)
    )
  );

  return true;
}

bool Server::disconnectUser(std::list<ServerUser*>::iterator user)
{
  auto& u = **user;
  //std::cout << "Disconnecting user..." << std::endl;
  const auto str = D_STR(u.getUsername());
  std::list<User> users;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& su = **it;
    if (it != user)
    {
      users.push_back(su);
    }
  }
  this->send(
    ServerPacket(
      Message(
        this->_serverProfile,
        GENERAL_CHANNEL,
        str,
        Message::SERVER
      ),
      users
    )
  );
  //std::cout << "Saving user info..." << std::endl;
  u.saveUser();
  //std::cout << "Disconnecting socket..." << std::endl;
  this->_selector.remove(*u.getSocket());
  u.getSocket()->disconnect();
  //std::cout << "Deleting user in list..." << std::endl;
  //std::cout << "User disconnected!" << std::endl;

  return true;
}

std::vector<int> roll(int diceNum, int diceSides)
{
  std::cout << "Rolling " << diceNum << "d" << diceSides << "..." << std::endl;
  if (diceNum <= 0 || diceNum >= 1000 || diceSides <= 0 || diceSides >= 1000)
  {
    return { 0 };
  }
  std::vector<int> r;
  for (auto i = 0; i < diceNum; i++)
  {
    r.push_back(1 + rand() % diceSides);
  }
  return r;
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
      std::list<User> users;
      for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
      {
        auto& u = **it;
        if (u.getId() == msg.getUser().getId())
        {
          u.setUsername(msg.getMessage().substr(3));
        }
        users.push_back(u);
      }
      this->send(
        ServerPacket(
          Message(
            _serverProfile,
            GENERAL_CHANNEL,
            C_STR(msg.getUser().getUsername(), msg.getMessage().substr(3)),
            Message::SERVER
          ),
          users
        )
      );
      return 'u';
    }
    if (s == "c")
    {
      return 'c';
    }
    if (s == "desc")
    {
      this->send(
        ServerPacket(
          Message(
            User(0, "N/A", sf::Color::White),
            msg.getChannel(),
            msg.getMessage().substr(6),
            Message::CLIENT_COMMAND
          ),
          serverUsersToUsers(this->_users)
        )
      );
    }
    if (s == "me")
    {
      this->send(
        ServerPacket(
          Message(
            msg.getUser(),
            msg.getChannel(),
            msg.getUser().getUsername() + " " + msg.getMessage().substr(4),
            Message::CLIENT_COMMAND
          ),
          serverUsersToUsers(this->_users)
        )
      );
    }
    if (s == "roll")
    {
      auto dice = msg.getMessage().substr(msg.getMessage().find(' ') + 1);
      std::stringstream ss(dice.substr(0, dice.find('d')));
      std::cout << "'" << ss.str() << "'" << std::endl;
      auto diceNum = 0;
      ss >> diceNum;

      ss.clear();
      ss.str(dice.substr(dice.find('d') + 1));
      std::cout << "'" << ss.str() << "'" << std::endl;
      auto diceSides = 0;
      ss >> diceSides;

      std::cout << diceNum << "d" << diceSides << std::endl;
      auto r = roll(diceNum, diceSides);
      std::string str = "";
      auto rt = 0;
      for (auto i = 0; i < int(r.size()); i++)
      {
        str += std::to_string(r[i]);
        if (i != int(r.size()) - 1)
        {
          str += " + ";
        }
        rt += r[i];
      }
      this->send(
        ServerPacket(
          Message(
            msg.getUser(),
            msg.getChannel(),
            "Rolling " + dice + "...\n" + str + " = " + std::to_string(rt),
            Message::CLIENT_COMMAND
          ),
          serverUsersToUsers(this->_users)
        )
      );
    }
  }
  else
  {
    std::list<User> users;
    for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
    {
      auto& u = **it;
      users.push_back(u);
    }
    this->send(ServerPacket(msg, users));
  }
  return true;
}

//bool Server::send(Message msg)
//{
//  std::cout << msg.getUser().getUsername() << ": " << msg.getMessage() << std::endl;
//  sf::Packet packet;
//  packet << msg;
//  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
//  {
//    auto& user = **it;
//    user.getSocket()->send(packet);
//  }
//  return false;
//}
//
//bool Server::send(Message msg, User u)
//{
//  std::cout << msg.getUser().getUsername() << ": " << msg.getMessage() << std::endl;
//  sf::Packet packet;
//  packet << msg << u;
//  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
//  {
//    auto& user = **it;
//    user.getSocket()->send(packet);
//  }
//  return false;
//}

bool Server::send(ServerPacket packet)
{
  auto now = time(nullptr);
  const auto ltm = localtime(&now);

  const auto user = packet.getMessage().getUser().getUsername();
  const auto msg = packet.getMessage().getMessage();
  const auto chan = packet.getMessage().getChannel();
  std::ofstream ofs("logs/" + chan.getId() + " " + std::to_string(ltm->tm_year + 1900) + std::to_string(ltm->tm_mon + 1) + std::to_string(ltm->tm_mday), std::ios::app);
  ofs << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << " " << user << ": " << msg << std::endl;
  std::cout << user << " (" << chan.getName() << "): " << msg << std::endl;
  sf::Packet p;
  p << packet;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    u.getSocket()->send(p);
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
        if (this->_selector.isReady(this->_connectionSocket))
        {
          sf::Packet packet;
          sf::IpAddress ip;
          unsigned short port;
          if (this->_connectionSocket.receive(packet, ip, port))
          {
            std::string str = "";
            if (packet >> str && str == "ping")
            {
              std::cout << "Received ping!" << std::endl;
              packet.clear();
              packet << std::string("pong");
              this->_connectionSocket.send(packet, ip, port);
            }
          }
        }
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
