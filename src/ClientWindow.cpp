#include "ClientWindow.h"

#include "CONSTANTS.h"
#include "TextManager.h"
#include <iostream>

struct ArgsContainer
{
  ArgsContainer(Client& c, tgui::TextBox::Ptr& t) : client(c), textbox(t) {}

  Client& client;
  tgui::TextBox::Ptr& textbox;
};

void sendToClient(ArgsContainer a)
{
  a.client.send(a.textbox);
  a.textbox->setText("");
}

Client::ClientWindow::ClientWindow(Client& client, TextManagerRef textManager) : _client(client), _textManager(textManager), _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->_textManager->getText("GAME_TITLE"), sf::Style::Close | sf::Style::Titlebar), _gui(this->_window)
{
  this->_lChannels.push_back(Channel("ic_1", "IC Channel 1", PUBLIC_IC));

  this->_theme.load("themes/Black.txt");

  this->_lTabs = tgui::Tabs::create();
  this->_lTabs->setRenderer(this->_theme.getRenderer("Tabs"));
  this->_lTabs->setSize(CHATBOX_WIDTH, TAB_HEIGHT);
  this->_lTabs->setTextSize(TEXT_SIZE);
  this->_lTabs->setPosition(MARGIN, MARGIN);
  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    this->_lTabs->add(this->_lChannels[i].getName());
  }
  this->_lTabs->select(this->_lChannels[0].getName());
  this->_gui.add(this->_lTabs);

  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    this->_lChatBox[this->_lChannels[i].getName()] = tgui::ChatBox::create();
    this->_lChatBox[this->_lChannels[i].getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_lChatBox[this->_lChannels[i].getName()]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_lChatBox[this->_lChannels[i].getName()]->setTextSize(TEXT_SIZE);
    this->_lChatBox[this->_lChannels[i].getName()]->setPosition(MARGIN, MARGIN + TAB_HEIGHT);
    this->_lChatBox[this->_lChannels[i].getName()]->setLinesStartFromTop();
    this->_lChatBox[this->_lChannels[i].getName()]->addLine("This is " + this->_lChannels[i].getId(), sf::Color::White);
    if (i > 0)
    {
      this->_lChatBox[this->_lChannels[i].getName()]->setVisible(false);
    }
    this->_gui.add(this->_lChatBox[this->_lChannels[i].getName()]);
  }


  this->_rTabs = tgui::Tabs::create();
  this->_rTabs->setRenderer(this->_theme.getRenderer("Tabs"));
  this->_rTabs->setSize(CHATBOX_WIDTH, TAB_HEIGHT);
  this->_rTabs->setTextSize(TEXT_SIZE);
  this->_rTabs->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN);
  this->addChannel(*generalChannel);
  this->_rTabs->select(this->_rChannels[0].getName());
  this->_gui.add(this->_rTabs);

  this->_memberList = tgui::ListBox::create();
  this->_memberList->setRenderer(this->_theme.getRenderer("ListBox"));
  this->_memberList->setSize(MEMBERLIST_WIDTH, CHATBOX_HEIGHT + TAB_HEIGHT);
  this->_memberList->setTextSize(TEXT_SIZE);
  this->_memberList->setPosition(float(MARGIN + 2 * CHATBOX_WIDTH + 1.5f * PADDING), MARGIN);
  this->_gui.add(this->_memberList);

  this->_typeBox = tgui::TextBox::create();
  this->_typeBox->setRenderer(this->_theme.getRenderer("TextBox"));
  this->_typeBox->setSize(TYPEBOX_WIDTH, TYPEBOX_HEIGHT);
  this->_typeBox->setTextSize(TEXT_SIZE);
  this->_typeBox->setPosition(MARGIN, MARGIN + CHATBOX_HEIGHT + TAB_HEIGHT + PADDING);
  this->_typeBox->setReadOnly(false);
  this->_gui.add(this->_typeBox);

  this->_sendButton = tgui::Button::create();
  this->_sendButton->setRenderer(this->_theme.getRenderer("Button"));
  this->_sendButton->setSize(TYPEBOX_HEIGHT, TYPEBOX_HEIGHT);
  this->_sendButton->setTextSize(TEXT_SIZE);
  this->_sendButton->setText(sf::String(this->_textManager->getText("SEND_BUTTON")));
  this->_sendButton->setPosition(MARGIN + TYPEBOX_WIDTH + PADDING, MARGIN + CHATBOX_HEIGHT + TAB_HEIGHT + PADDING);
  this->_sendButton->connect("pressed", sendToClient, ArgsContainer(this->_client, this->_typeBox));
  this->_gui.add(this->_sendButton);
}


void Client::ClientWindow::addChannel(Channel channel)
{
  switch (channel.getType())
  {
  case PUBLIC_OOC:
  case PRIVATE_OOC:
    this->_rChannels.push_back(channel);
    this->_rChatBox[channel.getName()] = tgui::ChatBox::create();
    this->_rChatBox[this->_rChannels.back().getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_rChatBox[this->_rChannels.back().getName()]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_rChatBox[this->_rChannels.back().getName()]->setTextSize(TEXT_SIZE);
    this->_rChatBox[this->_rChannels.back().getName()]->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN + TAB_HEIGHT);
    this->_rChatBox[this->_rChannels.back().getName()]->setLinesStartFromTop();
    this->_rChatBox[this->_rChannels.back().getName()]->addLine("This is " + this->_rChannels.back().getId(), sf::Color::White);
    for (auto i = 0; i < int(_rChannels.size()) - 1; i++)
    {
      this->_rChatBox[this->_rChannels[i].getName()]->setVisible(false);
    }
    this->_rChatBox[this->_rChannels.back().getName()]->setVisible(true);
    this->_gui.add(this->_rChatBox[this->_rChannels.back().getName()]);
    this->_rTabs->add(this->_rChannels.back().getName());

    break;
  case PUBLIC_IC:
  case PRIVATE_IC:
    this->_lChannels.push_back(channel);
    this->_lChatBox[channel.getName()] = tgui::ChatBox::create();
    this->_lChatBox[this->_lChannels.back().getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_lChatBox[this->_lChannels.back().getName()]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_lChatBox[this->_lChannels.back().getName()]->setTextSize(TEXT_SIZE);
    this->_lChatBox[this->_lChannels.back().getName()]->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN + TAB_HEIGHT);
    this->_lChatBox[this->_lChannels.back().getName()]->setLinesStartFromTop();
    this->_lChatBox[this->_lChannels.back().getName()]->addLine("This is " + this->_lChannels.back().getId(), sf::Color::White);
    for (auto i = 0; i < int(_lChannels.size()) - 1; i++)
    {
      this->_lChatBox[this->_lChannels[i].getName()]->setVisible(false);
    }
    this->_lChatBox[this->_lChannels.back().getName()]->setVisible(true);
    this->_gui.add(this->_lChatBox[this->_lChannels.back().getName()]);
    this->_lTabs->add(this->_lChannels.back().getName());
    break;
  default: ;
  }
}

void Client::ClientWindow::removeChannel(std::string id)
{
  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    if (this->_lChannels[i].getId() == id)
    {
      this->_lChatBox.erase(this->_lChatBox.find(this->_lChannels[i].getName()));
      this->_lTabs->remove(this->_lChannels[i].getName());
      this->_lChannels.erase(this->_lChannels.begin() + i);
    }
  }
  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    if (this->_rChannels[i].getId() == id)
    {
      this->_rChatBox.erase(this->_rChatBox.find(this->_rChannels[i].getName()));
      this->_rTabs->remove(this->_rChannels[i].getName());
      this->_rChannels.erase(this->_rChannels.begin() + i);
    }
  }
}

void Client::ClientWindow::removeChannel(Channel channel)
{
  this->removeChannel(channel.getId());
}

void Client::ClientWindow::addUser(std::string username) const
{
  this->_memberList->addItem(username);
}

void Client::ClientWindow::removeUser(std::string username) const
{
  this->_memberList->removeItem(username);
}

void Client::ClientWindow::addMessage(Message message)
{
  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    if (message.getChannel()->getId() == this->_lChannels[i].getId())
    {
      this->_lChannels[i].addMessage(message);
    }
  }
  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    if (message.getChannel()->getId() == this->_rChannels[i].getId())
    {
      this->_rChannels[i].addMessage(message);
    }
  }
}

void Client::ClientWindow::sendButtonClick()
{
  Message message(_client.getUser(), new Channel(this->_rChannels[this->_rTabs->getSelectedIndex()]), this->_typeBox->getText());
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

      this->_gui.handleEvent(event);
      for (auto i = 0; i < int(this->_lChannels.size()); i++)
      {
        if (this->_lChannels[i].getName() != this->_lTabs->getSelected())
        {
          this->_lChatBox[this->_lChannels[i].getName()]->setVisible(false);
        }
      }
      for (auto i = 0; i < int(this->_rChannels.size()); i++)
      {
        if (this->_rChannels[i].getName() != this->_rTabs->getSelected())
        {
          this->_rChatBox[this->_rChannels[i].getName()]->setVisible(false);
        }
      }
      this->_lChatBox[this->_lTabs->getSelected()]->setVisible(true);
      this->_rChatBox[this->_rTabs->getSelected()]->setVisible(true);
    }

    this->_window.clear();
    this->_gui.draw();
    this->_window.display();
  }
}

