#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <SFML/Network.hpp>
#include "User.h"

class Message
{
public:
  Message();
  Message(User user, std::string message);

  User getUser() const;
  std::string getMessage() const;

  friend std::ostream& operator<<(std::ostream& o, const Message& msg);
  friend sf::Packet& operator<<(sf::Packet& packet, const Message& msg);
  friend sf::Packet& operator>>(sf::Packet& packet, Message& msg);

private:
  User _user;
  std::string _message;

};

std::ostream& operator<<(std::ostream& o, const Message& msg);
sf::Packet& operator<<(sf::Packet& packet, const Message& msg);
sf::Packet& operator>>(sf::Packet& packet, Message& msg);

#endif
