#include "ClientWindow.h"

#include "CONSTANTS.h"

Client::ClientWindow::ClientWindow(Client& client) : _client(client), _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar), _gui(this->_window)
{
  this->_lChannels.push_back(Channel("ic_1", "IC Channel 1", PUBLIC_IC));
  this->_rChannels.push_back(Channel("ooc_1", "OOC Channel 1"));

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
  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    this->_rTabs->add(this->_rChannels[i].getName());
  }
  this->_rTabs->select(this->_rChannels[0].getName());
  this->_gui.add(this->_rTabs);

  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    this->_rChatBox[this->_rChannels[i].getName()] = tgui::ChatBox::create();
    this->_rChatBox[this->_rChannels[i].getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_rChatBox[this->_rChannels[i].getName()]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_rChatBox[this->_rChannels[i].getName()]->setTextSize(TEXT_SIZE);
    this->_rChatBox[this->_rChannels[i].getName()]->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN + TAB_HEIGHT);
    this->_rChatBox[this->_rChannels[i].getName()]->setLinesStartFromTop();
    this->_rChatBox[this->_rChannels[i].getName()]->addLine("This is " + this->_rChannels[i].getId(), sf::Color::White);
    if (i > 0)
    {
      this->_rChatBox[this->_rChannels[i].getName()]->setVisible(false);
    }
    this->_gui.add(this->_rChatBox[this->_rChannels[i].getName()]);
  }

  this->_memberList = tgui::ListBox::create();
  this->_memberList->setRenderer(this->_theme.getRenderer("ListBox"));
  this->_memberList->setSize(MEMBERLIST_WIDTH, CHATBOX_HEIGHT + TAB_HEIGHT);
  this->_memberList->setTextSize(TEXT_SIZE);
  this->_memberList->setPosition(MARGIN + 2 * CHATBOX_WIDTH + 1.5 * PADDING, MARGIN);
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
  this->_sendButton->setText("Send");
  this->_sendButton->setPosition(MARGIN + TYPEBOX_WIDTH + PADDING, MARGIN + CHATBOX_HEIGHT + TAB_HEIGHT + PADDING);
  this->_gui.add(this->_sendButton);
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

