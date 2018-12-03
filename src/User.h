#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

template class std::basic_string<char>;

namespace sf
{
  class Packet;
}

class User
{
public:
  User();
  User(int id, std::string username, sf::Color color = sf::Color::White);

  int getId() const { return this->_id; }
  std::string getIdString() const;
  std::string getUsername() const { return this->_username; }
  sf::Color getColor() const { return this->_color; }

  void setUsername(std::string username) { this->_username = username; }
  void setColor(sf::Color color) { this->_color = color; }
  void setColor(std::string color);

  friend sf::Packet& operator<<(sf::Packet& p, const User& u);
  friend sf::Packet& operator>>(sf::Packet& p, User& u);

protected:
  int _id;
  std::string _username;
  sf::Color _color;
  std::vector<std::string> _channels;
};

std::ostream& operator<<(std::ostream& os, const sf::Color& c);
sf::Packet& operator<<(sf::Packet& p, const sf::Color& c);
sf::Packet& operator>>(sf::Packet& p, sf::Color& c);
sf::Packet& operator<<(sf::Packet& p, const std::vector<std::string>& v);
sf::Packet& operator>>(sf::Packet& p, std::vector<std::string>& v);
sf::Packet& operator<<(sf::Packet& p, const User& u);
sf::Packet& operator>>(sf::Packet& p, User& u);

#endif
