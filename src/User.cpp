#include "User.h"

User::User() : username("") {}

bool User::operator == (sf::IpAddress& ip)
{
  return this->_ipAddress == ip;
}
bool User::operator == (User& u)
{
  return this->_ipAddress == u.ipAddress;
}
