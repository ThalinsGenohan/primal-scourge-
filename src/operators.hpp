#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

inline sf::Packet& operator<<(sf::Packet& packet, const sf::IpAddress& ip)
{
  return packet << ip.toString();
}
inline sf::Packet& operator>>(sf::Packet& packet, sf::IpAddress& ip)
{
  std::string str;
  packet >> str;
  ip = str;
  return packet;
}

inline sf::Packet& operator<<(sf::Packet& packet, const sf::Color& color)
{
  return packet << color.r << color.g << color.b << color.a;
}
inline sf::Packet& operator>>(sf::Packet& packet, sf::Color& color)
{
  return packet >> color.r >> color.g >> color.b >> color.a;
}

#endif