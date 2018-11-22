#include "ServerUser.h"

#include <iostream>

ServerUser::ServerUser(): _socket(nullptr) {}

ServerUser::ServerUser(User user) : User(user), _socket()
{
  std::cout << this->_id;
}
