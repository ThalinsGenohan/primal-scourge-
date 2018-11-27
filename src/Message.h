#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "Channel.h"
#include "User.h"

namespace sf
{
  class Packet;
}

class Message;
sf::Packet& operator<<(sf::Packet& packet, const Message& msg);
sf::Packet& operator>>(sf::Packet& packet, Message& msg);

class Message
{
public:
  enum MessageType
  {
    MESSAGE,
    SERVER,
    CLIENT_COMMAND,
    SERVER_COMMAND
  };

  Message();
  Message(User user, Channel channel, std::string message, MessageType type = MESSAGE);

  int getId() const { return this->_id; }
  User getUser() const { return this->_user; }
  Channel getChannel() const { return this->_channel; }
  std::string getMessage() const { return this->_message; }
  MessageType getType() const { return this->_type; }

  void setId(int id) { this->_id = id; }
  void setUser(User user) { this->_user = user; }
  void setChannel(Channel channel) { this->_channel = channel; }
  void setMessage(std::string message) { this->_message = message; }
  void setType(MessageType type) { this->_type = type; }

  friend sf::Packet& operator<<(sf::Packet& packet, const Message& msg);
  friend sf::Packet& operator>>(sf::Packet& packet, Message& msg);

private:
  int _id;
  User _user;
  Channel _channel;
  std::string _message;
  MessageType _type;
};

#endif
