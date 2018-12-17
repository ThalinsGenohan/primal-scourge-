#include "pch.h"
#include "CONSTANTS.h"
#include "TextManager.h"

#include <discord_rpc.h>
#include "discord.h"
#include "Client.h"
#include "Server.h"
#include <thread>

#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#endif

bool pushButton(tgui::EditBox::Ptr eb)
{
  auto str = eb->getText();

  return false;
}

sf::IpAddress connect(TextManagerRef textManager)
{
  sf::RenderWindow window(sf::VideoMode(250, 100), textManager->getText("CONNECTION_WINDOW"));
  tgui::Gui gui(window);
  auto textbox = tgui::EditBox::create();
  auto button = tgui::Button::create();
  textbox->setRenderer(tgui::Theme("assets/themes/Black.txt").getRenderer("EditBox"));
  textbox->setTextSize(int(TEXT_SIZE * 1.5f));
  textbox->setAlignment(tgui::EditBox::Alignment::Center);
  textbox->setSize(180, 25);
  textbox->setPosition((250.f - textbox->getSize().x) / 2.f, 25);
  textbox->setInputValidator("\\d{1,3}(\\.\\d{1,3}|\\.$){0,3}");
  button->setRenderer(tgui::Theme("assets/themes/Black.txt").getRenderer("Button"));
  button->setSize(100, 25);
  button->setPosition(75, 50);
  button->setTextSize(int(TEXT_SIZE * 1.5f));
  button->setText("Connect");
  button->setPosition((250.f - button->getSize().x) / 2.f, 50);

  gui.add(textbox);
  gui.add(button);

  while (window.isOpen())
  {
    sf::Event e;
    while (window.pollEvent(e))
    {
      if (e.type == sf::Event::Closed)
      {
        window.close();
      }
      gui.handleEvent(e);
    }

    window.clear(sf::Color::Black);
    gui.draw();
    window.display();
  }
  return sf::IpAddress("0.0.0.0");
}

sf::IpAddress searchLan()
{
  sf::UdpSocket udp;
  udp.bind(PORT);
  sf::Packet packet;
  packet << std::string("ping");
  std::cout << "Searching LAN for connection..." << std::endl;
  udp.send(packet, sf::IpAddress::Broadcast, PORT);
  packet.clear();
  sf::IpAddress ip;
  unsigned short port;
  if(udp.receive(packet, ip, port) != sf::Socket::Done)
  {
    std::cout << "No LAN connection detected." << std::endl;
    ip = "0.0.0.0";
    return ip;
  }
  std::string str = "";
  if (!(packet >> str) || str != "pong")
  {
    std::cout << "No LAN connection detected." << std::endl;
    ip = "0.0.0.0";
  }
  return ip;
}

void runServer(Server& server)
{
  server.run();
}

int main(int /*argc*/, char** /*argv*/)
{
  srand(unsigned(time(nullptr)));

  std::cout << "Starting Client..." << std::endl;
  const auto textManager = std::make_shared<TextManager>();
  discord::initDiscord();

  auto ip = searchLan();
#ifdef _WIN32
#ifdef NDEBUG
  ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#endif
  if (ip.toInteger() == 0)
  {
    //ip = connect(textManager);
    Server server;
    std::thread thread([&]()
    {
      server.run();
    });
    Client client(sf::IpAddress::LocalHost, textManager);
    client.disconnect();
    server.stop();
    thread.join();
  }
  if (ip.toInteger() != 0)
  {
    Client client(ip, textManager);
    client.disconnect();
  }
  Discord_Shutdown();

  std::cout << "End. Closing program..." << std::endl;
  return 0;
}
