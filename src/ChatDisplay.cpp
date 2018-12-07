#include "pch.h"
#include "ChatDisplay.h"

#include "CONSTANTS.h"

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

Client::ClientWindow::ChatDisplay::ChatDisplay(Client & client, tgui::Theme theme, std::string title) : _theme(theme), _focusedChat(0), _typeFocus(false), _tabs(tgui::Tabs::create()), _label(tgui::Label::create()), _memberList(tgui::ListBox::create()), _memberListLabel(tgui::Label::create()), _typeBox(tgui::TextBox::create()), _sendButton(tgui::Button::create()), _client(client)
{
  std::cout << "Creating ChatDisplay..." << std::endl;
  this->_tabs->setSize(CHATBOX_WIDTH, TAB_HEIGHT);
  this->_tabs->setTextSize(TEXT_SIZE);

  this->_label->setTextSize(TEXT_SIZE);
  this->_label->setText(this->_title);

  this->_memberList->setSize(MEMBERLIST_WIDTH, CHATBOX_HEIGHT + TAB_HEIGHT);
  this->_memberList->setTextSize(TEXT_SIZE);

  this->_memberListLabel->setTextSize(TEXT_SIZE);
  this->_memberListLabel->setText("Members");

  this->_typeBox->setSize(TYPEBOX_WIDTH, TYPEBOX_HEIGHT);
  this->_typeBox->setTextSize(TEXT_SIZE);
  this->_typeBox->setReadOnly(false);

  this->_sendButton->setSize(TYPEBOX_HEIGHT, TYPEBOX_HEIGHT);
  this->_sendButton->setTextSize(TEXT_SIZE);
  this->_sendButton->setText("Send");
  this->_sendButton->connect("pressed", sendToClient, ArgsContainer(this->_client, this->_typeBox));

  this->setTitle(title);
  this->setTheme(this->_theme);
  this->setPosition({ 0.f, 0.f });
}

void Client::ClientWindow::ChatDisplay::setPosition(const sf::Vector2f position)
{
  this->_position = position;
  this->_tabs->setPosition(position);
  if (int(this->_channels.size()) > 0)
  {
    for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
    {
      auto& c = **it;
      this->_chatBoxes[c.getName()]->setPosition(position.x, position.y + this->_tabs->getSize().y);
    }
  }
  this->_label->setPosition(this->_tabs->getPosition().x + this->_tabs->getSize().x / 2.f - this->_label->getSize().x / 2.f, this->_tabs->getPosition().y - this->_label->getSize().y);
  this->_memberList->setPosition(position.x + this->_tabs->getSize().x + PADDING, position.y);
  this->_memberListLabel->setPosition(this->_memberList->getPosition().x + this->_memberList->getSize().x / 2.f - this->_memberListLabel->getSize().x / 2.f, this->_memberList->getPosition().y - this->_memberListLabel->getSize().y);
  this->_typeBox->setPosition(position.x, this->_memberList->getPosition().y + this->_memberList->getSize().y + PADDING);
  this->_sendButton->setPosition(position.x + this->_typeBox->getSize().x + PADDING, this->_typeBox->getPosition().y);
}

void Client::ClientWindow::ChatDisplay::setTheme(const tgui::Theme theme)
{
  this->_theme = theme;
  this->_tabs->setRenderer(this->_theme.getRenderer("Tabs"));
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    this->_chatBoxes[c.getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
  }
  this->_label->setRenderer(this->_theme.getRenderer("Label"));
  this->_memberList->setRenderer(this->_theme.getRenderer("ListBox"));
  this->_memberListLabel->setRenderer(this->_theme.getRenderer("Label"));
  this->_typeBox->setRenderer(this->_theme.getRenderer("TextBox"));
  this->_sendButton->setRenderer(this->_theme.getRenderer("Button"));
}

void Client::ClientWindow::ChatDisplay::setTitle(const std::string title)
{
  this->_title = title;
  this->_label->setText(title);
}

void Client::ClientWindow::ChatDisplay::setChannels(const std::list<Channel*> channels)
{
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    this->removeChannel(new Channel(c));
  }
  for (auto it = channels.begin(); it != channels.end(); ++it)
  {
    auto& c = **it;
    this->addChannel(new Channel(c));
  }
}

void Client::ClientWindow::ChatDisplay::setUsers(const std::list<User> users)
{
  this->_users.clear();
  this->_memberList->removeAllItems();
  for (auto it = users.begin(); it != users.end(); ++it)
  {
    auto& u = *it;
    this->_users.push_back(new User(u));
  }
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    this->_memberList->addItem(u.getUsername());
  }
}

void Client::ClientWindow::ChatDisplay::addMessage(Message message)
{
  if (message.getUser().getUsername() != this->_lastUser && message.getType() != Message::SERVER_COMMAND && message.getType() != Message::CLIENT_COMMAND)
  {
    this->_chatBoxes[message.getChannel().getName()]->addLine("\n" + message.getUser().getUsername(), message.getUser().getColor(), sf::Text::Bold);
    this->_lastUser = message.getUser().getUsername();
  }
  if (message.getType() == Message::CLIENT_COMMAND)
  {
    this->_chatBoxes[message.getChannel().getName()]->addLine("\n" + message.getMessage(), message.getUser().getColor(), sf::Text::Bold | sf::Text::Italic);
  }
  else
  {
    this->_chatBoxes[message.getChannel().getName()]->addLine(message.getMessage(), sf::Color::White);
  }
}

void Client::ClientWindow::ChatDisplay::addChannel(Channel* channel)
{
  std::list<Channel*>::iterator ch;
  auto b = false;
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    if (c.getId() == "na")
    {
      b = true;
      ch = it;
    }
  }
  if (b)
  {
    auto& c = **ch;
    this->_channels.erase(ch);
    this->_chatBoxes.erase(this->_chatBoxes.find(c.getName()));
    this->_tabs->remove(c.getName());
  }

  this->_channels.push_back(channel);
  this->_chatBoxes[channel->getName()] = tgui::ChatBox::create();
  this->_chatBoxes[channel->getName()]->setRenderer(this->_theme.getRenderer("ChatBox"));
  this->_chatBoxes[channel->getName()]->setSize(CHATBOX_WIDTH, CHATBOX_HEIGHT);
  this->_chatBoxes[channel->getName()]->setTextSize(TEXT_SIZE);
  this->_chatBoxes[channel->getName()]->setPosition(this->_position.x, this->_position.y + TAB_HEIGHT);
  this->_chatBoxes[channel->getName()]->setVisible(false);
  if (channel->getId() == "na")
  {
    this->_tabs->add(channel->getName(), false);
    this->_tabs->setTabEnabled(this->_tabs->getTabsCount() - 1, false);
  }
  else
  {
    this->_tabs->add(channel->getName(), true);
    this->_chatBoxes[channel->getName()]->setVisible(true);
  }
}

bool operator==(const Channel c1, const Channel c2)
{
  return c1.getName() == c2.getName() && c1.getId() == c2.getId();
}

void Client::ClientWindow::ChatDisplay::removeChannel(Channel* channel)
{
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    if (c == *channel)
    {
      this->_channels.erase(it);
      this->_chatBoxes.erase(c.getName());
      this->_tabs->remove(c.getName());
    }
  }
}

void Client::ClientWindow::ChatDisplay::addUser(User* user)
{
  this->_users.push_back(user);
  this->_memberList->addItem(user->getUsername());
}

bool operator==(const User u1, const User u2)
{
  return u1.getUsername() == u2.getUsername() && u1.getId() == u2.getId();
}

void Client::ClientWindow::ChatDisplay::removeUser(User* user)
{
  auto b = false;
  std::list<User*>::iterator ue;
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = **it;
    std::cout << u.getId();
    if (u.getId() == user->getId())
    {
      b = true;
      ue = it;
    }
  }
  if (b)
  {
    auto& u = **ue;
    this->_users.erase(ue);
    this->_memberList->removeItem(u.getUsername());
  }
}

void Client::ClientWindow::ChatDisplay::switchChatBox()
{
  this->_focusedChat = this->_tabs->getSelectedIndex();
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    if (c.getName() == this->_tabs->getSelected() && c.getId() != "na")
    {
      this->_chatBoxes[c.getName()]->setVisible(true);
    }
    else
    {
      this->_chatBoxes[c.getName()]->setVisible(false);
    }
  }
}

void Client::ClientWindow::ChatDisplay::checkInput(sf::Event event)
{
  if (this->_typeBox->isFocused() && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !event.key.shift)
  {
    this->_typeBox->setText(this->_typeBox->getText().substring(0, this->_typeBox->getText().getSize() - 1));
    if (this->_typeBox->getText().getSize() >= 1)
    {
      sendToClient({ this->_client, this->_typeBox });
    }
  }
}

std::vector<tgui::Widget::Ptr> Client::ClientWindow::ChatDisplay::getWidgets() const
{
  std::vector<tgui::Widget::Ptr> v = { this->_tabs };
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    v.push_back(this->_chatBoxes.at(c.getName()));
  }
  v.push_back(_label);
  v.push_back(_memberList);
  v.push_back(_memberListLabel);
  v.push_back(_typeBox);
  v.push_back(_sendButton);
  return v;
}

bool Client::ClientWindow::ChatDisplay::isFocused()
{
  this->_focusedChat = this->_typeBox->isFocused();
  return this->_typeBox->isFocused();
}

void Client::ClientWindow::ChatDisplay::setFocus(bool b)
{
  this->_typeFocus = b;
  this->_typeBox->setFocused(b);
}

Channel Client::ClientWindow::ChatDisplay::getFocusedChannel() const
{
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = **it;
    if (this->_typeBox->isFocused() && this->_tabs->getSelected() == c.getName())
    {
      return c;
    }
  }
  return Channel();
}
