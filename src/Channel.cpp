#include "Channel.h"

Channel::Channel(): _type(PUBLIC_OOC) {}

Channel::Channel(std::string id, std::string name, ChannelType type) : _id(id), _name(name), _type(type) {}

Channel* generalChannel(new Channel("general", "General"));
