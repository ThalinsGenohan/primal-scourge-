#include "ServerUser.h"

#include <iostream>
#include <fstream>
//#include <experimental/filesystem>
#include "operators.h"
#include <array>
#include <sstream>

//namespace fs = std::experimental::filesystem;

ServerUser::ServerUser(): _socket(nullptr)
{
  this->_ipAddress = "0.0.0.0";
  this->_id = 0000;
  this->_username = "User #0000";
  this->_color = sf::Color::White;
}

ServerUser::ServerUser(User user) : User(user), _socket(nullptr) {}

ServerUser::ServerUser(sf::TcpSocket* socket) : _socket(socket), _ipAddress(this->_socket->getRemoteAddress())
{
  const auto file = "users/" + std::to_string(this->_ipAddress.toInteger()) + ".txt";
  std::ifstream ifs(file);
  if (!(ifs >> *this))
  {
    this->_id = rand() % 9999;
    this->_color = sf::Color::White;
    this->_username = "User #" + this->_id;
  }
}

bool ServerUser::saveUser() const
{
  /*if (!fs::is_directory("users") || !fs::exists("users"))
  {
    fs::create_directory("users");
  }*/

  std::ofstream of("users/" + std::to_string(this->_ipAddress.toInteger()) + ".txt");
  if(!(of << *this))
  {
    std::cout << "Error writing to file!" << std::endl;
  }

  return false;
}

std::ostream& operator<<(std::ostream & os, ServerUser u)
{
  return os << "IP: " << u._ipAddress << std::endl << "ID: " << u.getIdString() << std::endl << "Username: " << u._username << std::endl << "Color: " << u._color << std::endl;
}

std::ofstream & operator<<(std::ofstream & ofs, ServerUser u)
{
  ofs << u.getIdString() << std::endl << u._username << std::endl << u._color;
  return ofs;
}

std::istream& operator>>(std::istream & is, ServerUser & u)
{
  std::string buf;
  getline(is, buf, '\n');
  std::istringstream istr(buf);
  istr >> u._id;

  getline(is, u._username, '\n');

  std::array<int, 4> c;
  for (auto i = 0; i < int(c.size()); i++)
  {
    buf = "";
    getline(is, buf, '/');
    std::istringstream iss(buf);
    iss >> c[i];
  }
  u._color.r = c[0];
  u._color.g = c[1];
  u._color.b = c[2];
  u._color.a = c[3];

  return is;
}
