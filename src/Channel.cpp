#include "Channel.h"

#include <SFML/Network.hpp>

Channel::Channel(): _type(PUBLIC_OOC) {}

Channel::Channel(std::string id, std::string name, ChannelType type) : _id(id), _name(name), _type(type) {}

Channel noIcChannel("na", "N/A", Channel::PUBLIC_IC);
Channel noOocChannel("na", "N/A");
Channel generalChannel("general", "General");

sf::Packet & operator<<(sf::Packet & p, const Channel::ChannelType & t)
{
  return p << int(t);
}
sf::Packet & operator>>(sf::Packet & p, Channel::ChannelType& t)
{
  int x;
  p >> x;
  t = Channel::ChannelType(x);
  return p;
}
sf::Packet & operator<<(sf::Packet & p, const Channel & c)
{
  return p << c._id << c._name << c._type;
}
sf::Packet & operator>>(sf::Packet & p, Channel & c)
{
  return p >> c._id >> c._name >> c._type;
}
