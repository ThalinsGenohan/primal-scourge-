#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "CONSTANTS.h"

class ClientWindow
{
public:
  ClientWindow();

  void run();

private:
  sf::RenderWindow _window;

  tgui::Gui _gui;
  tgui::Theme _theme;
  tgui::Tabs::Ptr _lTabs;
  std::map<std::string, tgui::ChatBox::Ptr> _lChatBox;
  tgui::Tabs::Ptr _rTabs;
  std::map<std::string, tgui::ChatBox::Ptr> _rChatBox;
  tgui::ListBox::Ptr _memberList;
  tgui::TextBox::Ptr _typeBox;
  tgui::Button::Ptr _sendButton;

  std::vector<std::string> _lChannels;
  std::vector<std::string> _rChannels;
};

#endif
