#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

template <typename T>
std::vector<T> operator+(std::vector<T> vector1, std::vector<T> vector2);

std::ostream& operator<<(std::ostream& os, sf::Color c);
std::istream& operator>>(std::istream& is, sf::Color& c);

std::wostream& operator<<(std::wostream& os, std::map<std::string, std::wstring> m);

sf::Packet& operator<<(sf::Packet& packet, const sf::IpAddress& ip);
sf::Packet& operator>>(sf::Packet& packet, sf::IpAddress& ip);

sf::Packet& operator<<(sf::Packet& packet, const sf::Color& color);
sf::Packet& operator>>(sf::Packet& packet, sf::Color& color);

#endif