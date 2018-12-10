#include "pch.h"
#include "HUD.h"

#include "CONSTANTS.h"

Character::HUD::HUD() {}

Character::HUD::HUD(std::string portraitFilepath, std::string name)
{
  this->_portraitTexture.loadFromFile(portraitFilepath);
  this->_portrait.setSize({ 64.f, 64.f });
  this->_portrait.setTexture(new sf::Texture(this->_portraitTexture));
  this->_font.loadFromFile(FONT);
  this->_name.setFont(this->_font);
  this->_name.setString(name);
  this->_hpBar.background.setSize({ 100.f, 20.f });
  this->_hpBar.background.setOutlineThickness(1.f);
  this->_hpBar.background.setFillColor(sf::Color::Transparent);
  this->_hpBar.background.setOutlineColor(sf::Color::Black);
  this->_hpBar.bar.setSize({ 200.f, 20.f });
  this->_hpBar.bar.setFillColor(sf::Color::Red);
}

void Character::HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->_portrait, states);
  target.draw(this->_hpBar, states);
}

void Character::HUD::Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->background, states);
  target.draw(this->text, states);
}

void Character::HUD::Bar::setPosition(sf::Vector2f pos)
{
  this->_position = pos;
  this->bar.setPosition(pos);
  this->background.setPosition(pos);
}

void Character::HUD::Bar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->background, states);
  target.draw(this->bar, states);
  target.draw(this->valueText, states);
  target.draw(this->maxText, states);
}
