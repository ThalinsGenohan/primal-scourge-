#include "Client.h"

#include <iostream>

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "CONSTANTS.h"
#include "ClientWindow.h"
#include "Message.h"
#include "discord.h"
#include "ServerPacket.h"

Client::Client(TextManagerRef textManager): _window(new ClientWindow(*this, textManager)), _textManager(textManager)
{
  discord::updatePresence(L"Connecting...");
  if (!this->connect(IP_ADDRESS.toString()))
  {
    std::cout << "Server connection error!\n";
    return;
  }
  this->_socket.setBlocking(false);
  discord::updatePresence(L"In Chat Room");
  this->_window->run();
}

bool Client::connect(std::string ipAddress)
{
  if (this->_socket.connect(ipAddress, PORT) != sf::Socket::Done)
  {
    return false;
  }
  std::cout << "Receiving User info..." << std::endl;
  this->_socket.setBlocking(true);
  sf::Packet p;
  if (this->_socket.receive(p) != sf::Socket::Done)
  {
    std::cout << "User info receive error!" << std::endl;
  }
  p >> this->_user;
  std::cout << "User info received!" << std::endl;
  return true;
}

void Client::disconnect()
{
  sf::Packet packet;
  packet << Message(this->_user, GENERAL_CHANNEL, "/d", Message::SERVER_COMMAND);
  this->send(packet);
  this->_socket.disconnect();
}

bool Client::send(sf::Packet& packet)
{
  if (this->_socket.send(packet) != sf::Socket::Done)
  {
    std::cout << "Send error!" << std::endl;
    return false;
  }
  return true;
}

bool Client::send(tgui::TextBox::Ptr& textbox)
{
  sf::Packet packet;
  packet << Message(this->_user, this->_window->getFocusedChannel(), textbox->getText());

  return this->send(packet);
}

bool Client::receive()
{
  sf::Packet packet;
  if (this->_socket.receive(packet) == sf::Socket::Done)
  {
    ServerPacket serverPacket;
    if (!(packet >> serverPacket))
    {
      std::cout << "Packet receive error!\n";
      return false;
    }
    this->_window->setUsers(serverPacket.getUsers());
    auto message = serverPacket.getMessage();
    this->_user = serverPacket.getUser(this->_user.getId());
    std::cout << message.getUser().getUsername() << ": " << message.getMessage() << std::endl;
    User u;
    this->_window->addMessage(message);
    //auto b = false;
    /*switch (message.getType())
    {
    case Message::SERVER:
    case Message::MESSAGE:
      this->_window->addMessage(message);
      break;
    case Message::CLIENT_COMMAND:

      break;
    case Message::SERVER_COMMAND: break;
    default:;
    }*/
    return true;
  }
  return false;
}
