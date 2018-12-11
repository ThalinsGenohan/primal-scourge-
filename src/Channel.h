#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>

namespace sf
{
  class Packet;
}

class Channel
{
public:
  Channel() {}
  Channel(std::string id, std::string name);

  std::string getId() const { return this->_id; }
  std::string getName() const { return this->_name; }

  void setId(std::string id) { this->_id = id; }
  void setName(std::string name) { this->_name = name; }

  friend sf::Packet& operator<<(sf::Packet& p, const Channel& c);
  friend sf::Packet& operator>>(sf::Packet& p, Channel& c);

private:
  std::string _id;
  std::string _name;
};

sf::Packet& operator<<(sf::Packet& p, const Channel& c);
sf::Packet& operator>>(sf::Packet& p, Channel& c);

#endif
