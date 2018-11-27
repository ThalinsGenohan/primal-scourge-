#include "Client.h"

#include <iostream>

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "CONSTANTS.h"
#include "ClientWindow.h"
#include "Message.h"
#include "discord.h"

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
  return true;
}

void Client::disconnect()
{
  sf::Packet packet;
  packet << Message(this->_user, generalChannel, "/d", Message::SERVER_COMMAND);
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
  packet << Message(this->_user, Channel("general", "General"), textbox->getText());

  return this->send(packet);
}

bool Client::receive()
{
  sf::Packet packet;
  if (this->_socket.receive(packet) == sf::Socket::Done)
  {
    Message message;
    if (!(packet >> message))
    {
      std::cout << "Packet receive error!\n";
      return false;
    }
    std::cout << "In: " << message.getMessage() << std::endl;
    switch (message.getType())
    {
    case Message::MESSAGE:
    case Message::SERVER:
      this->_window->addMessage(message);
      break;
    case Message::CLIENT_COMMAND: break;
    case Message::SERVER_COMMAND: break;
    default:;
    }
    return true;
  }
  return false;
}
