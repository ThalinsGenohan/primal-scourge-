#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <map>
#include <vector>

namespace sf
{
  class Color;
  class Packet;
  class IpAddress;
}

template <typename T>
std::vector<T>& operator+(const std::vector<T>& vector1, const std::vector<T>& vector2);

std::ostream& operator<<(std::ostream& os, const sf::Color& c);
std::istream& operator>>(std::istream& is, sf::Color& c);

std::wostream& operator<<(std::wostream& os, const std::map<std::string, std::wstring>& m);

sf::Packet& operator<<(sf::Packet& packet, const sf::Color& color);
sf::Packet& operator>>(sf::Packet& packet, sf::Color& color);

#endif