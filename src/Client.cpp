#include <iostream>
#include "Client.h"
#include "CONSTANTS.h"
#include "Message.h"
#include "ClientWindow.h"

Client::Client(): _window(new ClientWindow(*this))
{
  if (this->_socket.connect(IP_ADDRESS, PORT) != sf::Socket::Done)
  {
    std::cout << "Server connection error!\n";
    return;
  }
  this->_socket.setBlocking(false);
  this->_window->run();
}

bool Client::send(sf::Packet& packet)
{
  if (this->_socket.send(packet) != sf::Socket::Done)
  {
    return false;
  }
  return true;
}

bool Client::receive()
{
  sf::Packet packet;
  if (this->_socket.receive(packet) != sf::Socket::Done)
  {
    std::cout << "Packet receive error!\n";
    return false;
  }
  Message message;
  if (!(packet >> message))
  {
    std::cout << "Packet receive error!\n";
    return false;
  }
  switch(message.getType())
  {
  case Message::MESSAGE:
    this->_window->addMessage(message);
    break;
  case Message::SERVER: break;
  case Message::CLIENT_COMMAND: break;
  case Message::SERVER_COMMAND: break;
  default: ;
  }

  return true;
}
