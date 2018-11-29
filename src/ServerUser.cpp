#include "ServerUser.h"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Network.hpp>

//namespace fs = std::experimental::filesystem;

ServerUser::ServerUser(): _socket(nullptr)
{
  this->_ipAddress = "0.0.0.0";
  this->_id = 0000;
  this->_username = "User #0000";
  this->_color = sf::Color::White;
}

ServerUser::ServerUser(User user) : User(user), _socket(nullptr) {}

ServerUser::ServerUser(sf::TcpSocket* socket) : _socket(socket)
{
  this->_ipAddress = this->_socket->getRemoteAddress();
  const auto file = "users/" + std::to_string(this->_ipAddress.toInteger()) + ".user";
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

  std::ofstream of("users/" + std::to_string(this->_ipAddress.toInteger()) + ".user");
  if(!(of << *this))
  {
    std::cout << "Error writing to file!" << std::endl;
  }

  return false;
}

std::ostream & operator<<(std::ostream & os, const sf::Color & c)
{
  return os << c.r << "/" << c.g << "/" << c.b << "/" << c.a;
}

std::ostream & operator<<(std::ostream & os, const std::vector<std::string> v)
{
  os << int(v.size()) << "/";
  for (auto i = 0; i < int(v.size()); i++)
  {
    os << "/" << v[i];
  }
  return os;
}

std::ostream & operator<<(std::ostream & os, const ServerUser & su)
{
  return os << su._id << std::endl << su._username << std::endl << su._color << std::endl << su._channels;
}

std::istream & operator>>(std::istream & is, ServerUser & su)
{
  std::cout << "Loading ID..." << std::endl;
  std::string buf;
  getline(is, buf, '\n');
  std::istringstream istr(buf);
  istr >> su._id;

  std::cout << "Loading username..." << std::endl;
  getline(is, su._username, '\n');

  std::cout << "Loading color..." << std::endl;
  std::array<int, 4> c;
  for (auto i = 0; i < int(c.size()); i++)
  {
    buf = "";
    getline(is, buf, '/');
    std::istringstream iss(buf);
    iss >> c[i];
  }
  su._color = sf::Color(c[0], c[1], c[2], c[3]);

  std::cout << "Loading channel number..." << std::endl;
  buf = "";
  getline(is, buf, '/');
  std::istringstream iss(buf);
  auto size = 0;
  iss >> size;
  std::cout << "Loading channels..." << std::endl;
  for (auto i = 0; i < size; i++)
  {
    buf = "";
    getline(is, buf, '/');
    su._channels.push_back(buf);
  }

  return is;
}
