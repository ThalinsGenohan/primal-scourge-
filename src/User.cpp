#include "User.h"

#include <SFML/Graphics.hpp>

#include "operators.hpp"

User::User() : _id(0), _username("") {}

User::User(int id, std::string username, sf::Color color) : _id(id), _username(username), _color(color) {}

int User::getId() const
{
  return this->_id;
}

std::string User::getUsername() const
{
  return this->_username;
}

sf::Color User::getColor() const
{
  return this->_color;
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

