#ifndef SERVERPACKET_H
#define SERVERPACKET_H

#include <list>
#include <SFML/Network.hpp>

#include "Channel.h"
#include "Message.h"
#include "User.h"

class ServerPacket
{
public:
  ServerPacket();
  explicit ServerPacket(Message msg, std::vector<User> users = {}, std::vector<Channel> channels = {});

  Message getMessage() const { return this->_message; }
  void setMessage(const Message msg) { this->_message = msg; }
  std::vector<User> getUsers() const { return this->_users; }
  User getUser(int id) const;
  User getUser(std::string username) const;
  std::vector<Channel> getChannels() const { return this->_channels; }
  Channel getChannel(std::string name) const;

  friend sf::Packet& operator<<(sf::Packet& p, const ServerPacket& sp);
  friend sf::Packet& operator>>(sf::Packet& p, ServerPacket& sp);

private:
  Message _message;
  std::vector<User> _users;
  std::vector<Channel> _channels;
};

template<typename T>
sf::Packet& operator<<(sf::Packet& p, const std::list<T>& l)
{
  p << static_cast<sf::Uint32>(l.size());
  for (auto it = l.begin(); it != l.end(); ++it)
  {
    p << *it;
  }
  return p;
}
template<typename T>
sf::Packet& operator>>(sf::Packet& p, std::list<T>& l)
{
  sf::Uint32 size;
  p >> size;
  for (auto i = 0; i < int(size); i++)
  {
    T item;
    p >> item;
    l.push_back(item);
  }
  return p;
}

sf::Packet& operator<<(sf::Packet& p, const ServerPacket& sp);
sf::Packet& operator>>(sf::Packet& p, ServerPacket& sp);

#endif
