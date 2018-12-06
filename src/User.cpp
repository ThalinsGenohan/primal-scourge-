#include "User.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <array>
#include <iostream>

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
  int r;
  switch (c)
  {
  case '1':
    r = 1;
    break;
  case '2':
    r = 2;
    break;
  case '3':
    r = 3;
    break;
  case '4':
    r = 4;
    break;
  case '5':
    r = 5;
    break;
  case '6':
    r = 6;
    break;
  case '7':
    r = 7;
    break;
  case '8':
    r = 8;
    break;
  case '9':
    r = 9;
    break;
  case 'A':
  case 'a':
    r = 10;
    break;
  case 'B':
  case 'b':
    r = 11;
    break;
  case 'C':
  case 'c':
    r = 12;
    break;
  case 'D':
  case 'd':
    r = 13;
    break;
  case 'E':
  case 'e':
    r = 14;
    break;
  case 'F':
  case 'f':
    r = 15;
    break;
  default:
    r = 0;
  }
  return r;
}

void User::setColor(std::string color)
{
  const auto r = hexCharToInt(color[0]) * 16 + hexCharToInt(color[1]);
  const auto g = hexCharToInt(color[2]) * 16 + hexCharToInt(color[3]);
  const auto b = hexCharToInt(color[4]) * 16 + hexCharToInt(color[5]);
  std::cout << r << "/" << g << "/" << b << std::endl;
  this->setColor(sf::Color(r, g, b, 255));
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
  const sf::Uint32 test = 3435973836;
  p >> size;
  if (size == test)
  {
    std::cout << "Error!" << std::endl;
  }
  else {
    for (sf::Uint32 i = 0; i < size; ++i)
    {
      std::string item;
      p >> item;
      v.push_back(item);
    }
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
