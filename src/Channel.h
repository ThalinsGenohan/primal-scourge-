#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>

#include "CONSTANTS.h"

class Channel
{
public:
  Channel();
  Channel(std::string id, std::string name, ChannelType type = PUBLIC_OOC);

  std::string getId() const { return this->_id; }
  std::string getName() const { return this->_name; }
  ChannelType getType() const { return this->_type; }

  void setId(std::string id) { this->_id = id; }
  void setName(std::string name) { this->_name = name; }
  void setType(ChannelType type) { this->_type = type; }

private:
  std::string _id;
  std::string _name;
  ChannelType _type;
};

extern Channel generalChannel;

#endif
