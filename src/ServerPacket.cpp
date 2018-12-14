#include "pch.h"
#include "ServerPacket.h"

ServerPacket::ServerPacket() {}

ServerPacket::ServerPacket(Message msg, std::vector<User> users, std::vector<Channel> channels) : _message(msg), _users(users), _channels(channels) {}

User ServerPacket::getUser(int id) const
{
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = *it;
    if (u.getId() == id)
    {
      return u;
    }
  }
  return User();
}

User ServerPacket::getUser(std::string username) const
{
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = *it;
    if (u.getUsername() == username)
    {
      return u;
    }
  }
  return User();
}

Channel ServerPacket::getChannel(std::string name) const
{
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = *it;
    if (c.getName() == name || c.getId() == name)
    {
      return c;
    }
  }
  return Channel();
}

template<typename T>
sf::Packet& operator<<(sf::Packet& p, const std::vector<T>& v)
{
  p << static_cast<sf::Uint32>(v.size());
  for (auto i = 0; i < int(v.size()); i++)
  {
    p << v[i];
  }
  return p;
}
template<typename T>
sf::Packet& operator>>(sf::Packet& p, std::vector<T>& v)
{
  sf::Uint32 size;
  p >> size;
  for (sf::Uint32 i = 0; i < size; i++)
  {
    T item;
    p >> item;
    v.push_back(item);
  }
  return p;
}

sf::Packet & operator<<(sf::Packet & p, const ServerPacket & sp)
{
  return p << sp._message << sp._users << sp._channels;
}

sf::Packet & operator>>(sf::Packet & p, ServerPacket & sp)
{
  return p >> sp._message >> sp._users >> sp._channels;
}
