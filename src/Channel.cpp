#include "pch.h"
#include "Channel.h"

Channel::Channel(std::string id, std::string name) : _id(id), _name(name) {}

sf::Packet & operator<<(sf::Packet & p, const Channel & c)
{
  return p << c._id << c._name;
}
sf::Packet & operator>>(sf::Packet & p, Channel & c)
{
  return p >> c._id >> c._name;
}
