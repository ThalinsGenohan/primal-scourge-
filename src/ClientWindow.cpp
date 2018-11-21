#include "ClientWindow.h"

#include "CONSTANTS.h"

ClientWindow::ClientWindow() : _window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar), _gui(this->_window)
{
  this->_lChannels.push_back("IC Channel 1");
  this->_lChannels.push_back("IC Channel 2");
  this->_rChannels.push_back("OOC Channel 1");
  this->_rChannels.push_back("OOC Channel 2");

  this->_theme.load("themes/Black.txt");

  this->_lTabs = tgui::Tabs::create();
  this->_lTabs->setRenderer(this->_theme.getRenderer("Tabs"));
  this->_lTabs->setSize(CHATBOX_WIDTH, TAB_HEIGHT);
  this->_lTabs->setTextSize(TEXT_SIZE);
  this->_lTabs->setPosition(MARGIN, MARGIN);
  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    this->_lTabs->add(this->_lChannels[i]);
  }
  this->_lTabs->select(this->_lChannels[0]);
  this->_gui.add(this->_lTabs);

  for (auto i = 0; i < int(this->_lChannels.size()); i++)
  {
    this->_lChatBox[this->_lChannels[i]] = tgui::ChatBox::create();
    this->_lChatBox[this->_lChannels[i]]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_lChatBox[this->_lChannels[i]]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_lChatBox[this->_lChannels[i]]->setTextSize(TEXT_SIZE);
    this->_lChatBox[this->_lChannels[i]]->setPosition(MARGIN, MARGIN + TAB_HEIGHT);
    this->_lChatBox[this->_lChannels[i]]->setLinesStartFromTop();
    this->_lChatBox[this->_lChannels[i]]->addLine("This is " + this->_lChannels[i], sf::Color::White);
    if (i > 0)
    {
      this->_lChatBox[this->_lChannels[i]]->setVisible(false);
    }
    this->_gui.add(this->_lChatBox[this->_lChannels[i]]);
  }

  this->_rTabs = tgui::Tabs::create();
  this->_rTabs->setRenderer(this->_theme.getRenderer("Tabs"));
  this->_rTabs->setSize(CHATBOX_WIDTH, TAB_HEIGHT);
  this->_rTabs->setTextSize(TEXT_SIZE);
  this->_rTabs->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN);
  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    this->_rTabs->add(this->_rChannels[i]);
  }
  this->_rTabs->select(this->_rChannels[0]);
  this->_gui.add(this->_rTabs);

  for (auto i = 0; i < int(this->_rChannels.size()); i++)
  {
    this->_rChatBox[this->_rChannels[i]] = tgui::ChatBox::create();
    this->_rChatBox[this->_rChannels[i]]->setRenderer(this->_theme.getRenderer("ChatBox"));
    this->_rChatBox[this->_rChannels[i]]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
    this->_rChatBox[this->_rChannels[i]]->setTextSize(TEXT_SIZE);
    this->_rChatBox[this->_rChannels[i]]->setPosition(MARGIN + CHATBOX_WIDTH + PADDING, MARGIN + TAB_HEIGHT);
    this->_rChatBox[this->_rChannels[i]]->setLinesStartFromTop();
    this->_rChatBox[this->_rChannels[i]]->addLine("This is " + this->_rChannels[i], sf::Color::White);
    if (i > 0)
    {
      this->_rChatBox[this->_rChannels[i]]->setVisible(false);
    }
    this->_gui.add(this->_rChatBox[this->_rChannels[i]]);
  }

  this->_memberList = tgui::ListBox::create();
  this->_memberList->setRenderer(this->_theme.getRenderer("ListBox"));
  this->_memberList->setSize(MEMBERLIST_WIDTH, CHATBOX_HEIGHT + TAB_HEIGHT);
  this->_memberList->setTextSize(TEXT_SIZE);
  this->_memberList->setPosition(MARGIN +  2 * CHATBOX_WIDTH + 1.5 * PADDING, MARGIN);
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
      for (auto i = 0; i < int(this->_lChannels.size()); i++)
      {
        if (this->_lChannels[i] != this->_lTabs->getSelected())
        {
          this->_lChatBox[this->_lChannels[i]]->setVisible(false);
        }
      }
      for (auto i = 0; i < int(this->_rChannels.size()); i++)
      {
        if (this->_rChannels[i] != this->_rTabs->getSelected())
        {
          this->_rChatBox[this->_rChannels[i]]->setVisible(false);
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

