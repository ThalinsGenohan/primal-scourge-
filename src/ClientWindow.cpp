#include "ClientWindow.h"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "CONSTANTS.h"
#include "ChatDisplay.h"
#include "TextManager.h"

Client::ClientWindow::ClientWindow(Client& client, TextManagerRef textManager) : _client(client), _textManager(textManager), _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->_textManager->getText("GAME_TITLE"), sf::Style::Close | sf::Style::Titlebar), _gui(this->_window), _theme("themes/Black.txt"), _ic(new ChatDisplay(this->_client, "IC Channels")), _ooc(new ChatDisplay(this->_client, "OOC Channels"))
{
  auto v = this->_ic->getWidgets();
  for (auto i = 0; i < int(v.size()); i++)
  {
    this->_gui.add(v[i]);
  }
  v = this->_ooc->getWidgets();
  for (auto i = 0; i < int(v.size()); i++)
  {
    this->_gui.add(v[i]);
  }

  this->addChannel(NO_CHANNEL(Channel::PUBLIC_IC));
  this->addChannel(GENERAL_CHANNEL);
  this->_ic->setPosition({ MARGIN, MARGIN });
  this->_ooc->setPosition({ this->_ic->getPosition().x + this->_ic->getSize().x + 2.f * PADDING, MARGIN });
}

void Client::ClientWindow::addChannel(Channel channel)
{
  switch (channel.getType())
  {
  case Channel::PUBLIC_OOC:
  case Channel::PRIVATE_OOC:
    this->_ooc->addChannel(new Channel(channel));
    this->_gui.add(this->_ooc->getChatBoxes()[channel.getName()]);
    break;

  case Channel::PUBLIC_IC:
  case Channel::PRIVATE_IC:
    this->_ic->addChannel(new Channel(channel));
    this->_gui.add(this->_ic->getChatBoxes()[channel.getName()]);
    break;
  default:;
  }
}

void Client::ClientWindow::addUser(User user) const
{
  this->_ooc->addUser(new User(user));
}

void Client::ClientWindow::removeUser(User user) const
{
  this->_ooc->removeUser(new User(user));
}

void Client::ClientWindow::setUsers(std::list<User> users) const
{
  this->_ooc->setUsers(users);
}

void Client::ClientWindow::addMessage(Message message) const
{
  switch (message.getChannel().getType())
  {
  case Channel::PUBLIC_OOC:
  case Channel::PRIVATE_OOC:
    this->_ooc->addMessage(message);
    break;

  case Channel::PUBLIC_IC:
  case Channel::PRIVATE_IC:
    this->_ic->addMessage(message);
    break;
  default: ;
  }
}

void Client::ClientWindow::setIcFocus(const bool b)
{
  this->_icFocus = b;
  this->_ic->setFocus(b);
  this->_ooc->setFocus(!b);
}

void Client::ClientWindow::toggleIcFocus()
{
  setIcFocus(!this->_icFocus);
}

void Client::ClientWindow::run()
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

      if (event.type == sf::Event::KeyPressed && (this->_ic->isFocused() || this->_ooc->isFocused()))
      {
        switch (event.key.code)
        {
        case sf::Keyboard::Tab:
          //toggleIcFocus();
          break;
        default:;
        }
      }

      this->_gui.handleEvent(event);

      this->_ic->switchChatBox();
      this->_ooc->switchChatBox();
      /*for (auto i = 0; i < int(this->_ic->getChannels().size()); i++)
      {
        if (this->_ic->getChannels()[i].getName() != this->_ic->getTabs()->getSelected())
        {
          this->_ic->getChatBoxes()[this->_ic->getChannels()[i].getName()]->setVisible(false);
        }
      }
      for (auto i = 0; i < int(this->_ooc->getChannels().size()); i++)
      {
        if (this->_ooc->getChannels()[i].getName() != this->_ooc->getTabs()->getSelected())
        {
          this->_ooc->getChatBoxes()[this->_ooc->getChannels()[i].getName()]->setVisible(false);
        }
      }
      if (int(this->_ic->getChannels().size()) > 0)
      {
        this->_ic->getChatBoxes()[this->_ic->getTabs()->getSelected()]->setVisible(true);
      }
      if (int(this->_ooc->getChannels().size()) > 0)
      {
        this->_ooc->getChatBoxes()[this->_ooc->getTabs()->getSelected()]->setVisible(true);
      }*/

      this->_ic->checkInput(event);
      this->_ooc->checkInput(event);
    }

    this->_client.receive();

    this->_window.clear();
    this->_gui.draw();
    this->_window.display();
  }
}
