#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <TGUI/TGUI.hpp>

#include "TextManager.h"

class Client;

class ClientWindow
{
public:
  explicit ClientWindow(Client& client, TextManagerRef textManager);
  virtual ~ClientWindow() = default;

  virtual void run() = 0;

protected:
  Client& _client;
  TextManagerRef _textManager;

  sf::RenderWindow _window;

  tgui::Gui _gui;
  tgui::Theme _theme;
};

#endif
