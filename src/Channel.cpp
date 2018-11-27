#include "Channel.h"

#include <SFML/Network.hpp>

Channel::Channel(): _type(PUBLIC_OOC) {}

Channel::Channel(std::string id, std::string name, ChannelType type) : _id(id), _name(name), _type(type) {}

Channel generalChannel("general", "General");

sf::Packet & operator>>(sf::Packet& packet, Channel::ChannelType& t)
{
  return packet << t;
}

sf::Packet & operator<<(sf::Packet& packet, const Channel& ch)
{
  return packet << ch._id << ch._name << ch._type;
}

sf::Packet & operator>>(sf::Packet& packet, Channel& ch)
{
  return packet >> ch._id >> ch._name >> ch._type;
}
