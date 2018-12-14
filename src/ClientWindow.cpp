#include "pch.h"
#include "ClientWindow.h"

#include "CONSTANTS.h"
#include "ChatDisplay.h"
#include "TextManager.h"

ClientWindow::ClientWindow(Client& client, TextManagerRef textManager) : _client(client), _textManager(textManager), _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->_textManager->getText("GAME_TITLE"), sf::Style::Close | sf::Style::Titlebar), _gui(this->_window), _theme("assets/themes/Black.txt")
{
  std::cout << "Creating ClientWindow..." << std::endl;
  this->_window.setFramerateLimit(60);
}

void ClientWindow::run()
{
  while (this->_window.isOpen())
  {
    sf::Event event;
    while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        this->_window.close();
      }

      this->_gui.handleEvent(event);
    }

    this->_client.receive();

    this->_window.clear();
    this->_gui.draw();
    this->_window.draw(this->_client.getUser().getCharacter());
    this->_window.display();
  }
}
