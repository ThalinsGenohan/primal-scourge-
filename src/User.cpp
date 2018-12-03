#include "User.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <array>

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

int hexCharToInt(char c)
{
  switch (c)
  {
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  case 'A':
  case 'a':
    return 10;
  case 'B':
  case 'b':
    return 11;
  case 'C':
  case 'c':
    return 12;
  case 'D':
  case 'd':
    return 13;
  case 'E':
  case 'e':
    return 14;
  case 'F':
  case 'f':
    return 15;
  default:
    return 0;
  }
}

void User::setColor(std::string color)
{
  auto c = 0;
  for (auto i = 0; i < 6; i++)
  {
    c += hexCharToInt(color[i]);
  }
  this->setColor(sf::Color(c));
}

std::ostream & operator<<(std::ostream & os, const sf::Color & c)
{
  return os << int(c.r) << "/" << int(c.g) << "/" << int(c.b) << "/" << int(c.a);
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
