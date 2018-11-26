#include "User.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "operators.h"

User::User() : _id(0), _username("") {}

User::User(int id, std::string username, sf::Color color) : _id(id), _username(username), _color(color) {}

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

std::ostream& operator<<(std::ostream& o, const User& user)
{
  return o << user._username << "#" << user._id;
}

sf::Packet& operator<<(sf::Packet& packet, const User& user)
{
  packet << user._id << user._username << user._color;
  return packet;
}
sf::Packet& operator>>(sf::Packet& packet, User& user)
{
  return packet >> user._id >> user._username >> user._color;
}

