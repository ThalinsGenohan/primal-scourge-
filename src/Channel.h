#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include "CONSTANTS.h"
#include "Message.h"

class Channel
{
public:
  Channel();
  Channel(std::string id, std::string name, ChannelType type = PUBLIC_OOC);

  std::string getId() const { return this->_id; }
  std::string getName() const { return this->_name; }
  ChannelType getType() const { return this->_type; }
  std::vector<Message> getMessages() const { return this->_messages; }

  void setId(std::string id) { this->_id = id; }
  void setName(std::string name) { this->_name = name; }
  void setType(ChannelType type) { this->_type = type; }

  void addMessage(Message message) { this->_messages.push_back(message); }

private:
  std::string _id;
  std::string _name;
  ChannelType _type;
  std::vector<Message> _messages;
};

extern Channel* generalChannel;

#endif
