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

  int getId() const;
  std::string getUsername() const;
  sf::Color getColor() const;

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