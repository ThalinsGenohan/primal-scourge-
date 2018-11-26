#ifndef USER_H
#define USER_H

#include <ostream>
#include <string>
#include <SFML/Graphics/Color.hpp>

namespace sf
{
  class Packet;
}

class User;
std::ostream& operator<<(std::ostream& o, User& user);
sf::Packet& operator<<(sf::Packet& packet, User& user);
sf::Packet& operator>>(sf::Packet& packet, User& user);

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

  friend std::ostream& operator<<(std::ostream& o, User& user);
  friend sf::Packet& operator<<(sf::Packet& packet, User& user);
  friend sf::Packet& operator>>(sf::Packet& packet, User& user);
  
protected:
  int _id;
  std::string _username;
  sf::Color _color;
  
};

#endif