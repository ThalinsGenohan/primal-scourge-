#include "User.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

User::User() : _id(0), _username(""), _channels({ "general" }) {}

User::User(int id, std::string username, sf::Color color) : _id(id), _username(username), _color(color), _channels({ "general" }) {}

std::string User::getIdString() const
{
  std::string str = "";
  if (this->_id < 1000)
  {
    str += "0";
  }
  if (this->_id < 100)
  {
    str += "0";
  }
  if (this->_id < 10)
  {
    str += "0";
  }
  str += std::to_string(this->_id);
  return str;
}

sf::Packet & operator<<(sf::Packet & p, const sf::Color & c)
{
  return p << c.r << c.g << c.b << c.a;
}
sf::Packet & operator>>(sf::Packet & p, sf::Color & c)
{
  return p >> c.r >> c.g >> c.b >> c.a;
}
sf::Packet & operator<<(sf::Packet & p, const std::vector<std::string>& v)
{
  p << static_cast<sf::Uint32>(v.size());
  for (auto it = v.begin(); it != v.end(); ++it)
  {
    p << *it;
  }
  return p;
}
sf::Packet & operator>>(sf::Packet & p, std::vector<std::string>& v)
{
  sf::Uint32 size;
  p >> size;
  for (sf::Uint32 i = 0; i < size; ++i)
  {
    std::string item;
    p >> item;
    v.push_back(item);
  }
  return p;
}
sf::Packet & operator<<(sf::Packet & p, const User & u)
{
  return p << u._id << u._username << u._color << u._channels;
}
sf::Packet & operator>>(sf::Packet & p, User & u)
{
  return p >> u._id >> u._username >> u._color >> u._channels;
}
