#ifndef USER_H
#define USER_H

#include <string>
#include <SFML/Network.hpp>

class User
{
public:
  User();

  bool operator == (sf::IpAddress& ip);
  bool operator == (User& u);
  
private:
  sf::IpAddress ipAddress;
  std::string username;
  sf::Color color;
  
};

#endif