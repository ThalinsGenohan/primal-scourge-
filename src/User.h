#ifndef USER_H
#define USER_H

#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class User
{
public:
  User();
  User(int id, std::string username, sf::Color color = sf::Color::White);

  int getId() const { return this->_id; }
  std::string getUsername() const { return this->_username; }
  sf::Color getColor() const { return this->_color; }

  void setUsername(std::string username) { this->_username = username; }
  void setColor(sf::Color color) { this->_color = color; }

  friend std::ostream& operator<<(std::ostream& o, const User& user);

  friend sf::Packet& operator<<(sf::Packet& packet, const User& user);
  friend sf::Packet& operator>>(sf::Packet& packet, User& user);
  
protected:
  int _id;
  std::string _username;
  sf::Color _color;
  
};

std::ostream& operator<<(std::ostream& o, const User& user);

sf::Packet& operator<<(sf::Packet& packet, const User& user);
sf::Packet& operator>>(sf::Packet& packet, User& user);

#endif