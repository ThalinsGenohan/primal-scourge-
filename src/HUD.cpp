#include "pch.h"
#include "HUD.h"

#include "CONSTANTS.h"

Character::HUD::HUD() : _portrait({0.f, 0.f}, ""), _type1(NO_TYPE), _type2(NO_TYPE), _strength("0"), _dexterity("0"), _special("0"), _vitality("0")
{
}

Character::HUD::HUD(std::string portraitFilepath, std::string name): _portrait({80.f, 80.f}, portraitFilepath), _type1(NO_TYPE), _type2(NO_TYPE), _strength("0"), _dexterity("0"), _special("0"), _vitality("0")
{
  this->_font.loadFromFile(FONT);
  this->_name.setFont(this->_font);
  this->_name.setString(name);
  this->_name.setCharacterSize(TEXT_SIZE);
  this->_hpBar.background.setSize({100.f, 20.f});
  this->_hpBar.background.setOutlineThickness(1.f);
  this->_hpBar.background.setFillColor(sf::Color::Transparent);
  this->_hpBar.background.setOutlineColor(sf::Color::Black);
  this->_hpBar.bar.setSize({200.f, 20.f});
  this->_hpBar.bar.setFillColor(sf::Color::Red);
  this->_type1.background.setSize({
    this->_portrait.background.getSize().x / 2.f, this->_portrait.background.getSize().y / 4.f
  });
  this->_type1.background.setFillColor(sf::Color::White);
  this->_type2.background.setSize({
    this->_portrait.background.getSize().x / 2.f, this->_portrait.background.getSize().y / 4.f
    });
  this->_type2.background.setFillColor(sf::Color::White);

  this->_type1.setType(FIGHTING);
  this->_type2.setType(STEEL);
}

void Character::HUD::setPosition(sf::Vector2f pos)
{
  this->_position = pos;
  const auto x = pos.x, y = pos.y;
  this->_name.setPosition(x, y - TEXT_SIZE - 3);
  this->_portrait.setPosition(pos);
  this->_hpBar.setPosition({ x + this->_portrait.background.getGlobalBounds().width, y });
  this->_type1.setPosition({ x, y + this->_portrait.background.getSize().y });
  this->_type2.setPosition({ x + this->_type1.getSize().x, y + this->_portrait.background.getSize().y });
}

void Character::HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->_name, states);
  target.draw(this->_portrait, states);
  target.draw(this->_type1, states);
  target.draw(this->_type2, states);
  target.draw(this->_hpBar, states);
  target.draw(this->_strength, states);
  target.draw(this->_dexterity, states);
  target.draw(this->_special, states);
  target.draw(this->_vitality, states);
  for (auto i = 0; i < int(this->_primality.size()); i++)
  {
    target.draw(this->_primality[i], states);
  }
}

Character::HUD::TypeLabel::TypeLabel(Type type): Label(""), _type(type)
{
  this->_font.loadFromFile(FONT);
  this->text.setFont(this->_font);
  this->text.setCharacterSize(TEXT_SIZE);
  this->text.setFillColor(sf::Color(255, 255, 255));
  this->setType(type);
}

void Character::HUD::TypeLabel::setType(Type type)
{
  switch (type)
  {
  case NORMAL:
    this->setText("Normal");
    this->background.setFillColor(NORMAL_COLOR);
    break;
  case FIRE:
    this->setText("Fire");
    this->background.setFillColor(FIRE_COLOR);
    break;
  case WATER:
    this->setText("Water");
    this->background.setFillColor(WATER_COLOR);
    break;
  case ELECTRIC:
    this->setText("Electric");
    this->background.setFillColor(ELECTRIC_COLOR);
    break;
  case GRASS:
    this->setText("Grass");
    this->background.setFillColor(GRASS_COLOR);
    break;
  case ICE:
    this->setText("Ice");
    this->background.setFillColor(ICE_COLOR);
    break;
  case FIGHTING:
    this->setText("Fight");
    this->background.setFillColor(FIGHTING_COLOR);
    break;
  case POISON:
    this->setText("Poison");
    this->background.setFillColor(POISON_COLOR);
    break;
  case GROUND:
    this->setText("Ground");
    this->background.setFillColor(GROUND_COLOR);
    break;
  case FLYING:
    this->setText("Flying");
    this->background.setFillColor(FLYING_COLOR);
    break;
  case PSYCHIC:
    this->setText("Psychic");
    this->background.setFillColor(PSYCHIC_COLOR);
    break;
  case BUG:
    this->setText("Bug");
    this->background.setFillColor(BUG_COLOR);
    break;
  case ROCK:
    this->setText("Rock");
    this->background.setFillColor(ROCK_COLOR);
    break;
  case GHOST:
    this->setText("Ghost");
    this->background.setFillColor(GHOST_COLOR);
    break;
  case DRAGON:
    this->setText("Dragon");
    this->background.setFillColor(DRAGON_COLOR);
    break;
  case DARK:
    this->setText("Dark");
    this->background.setFillColor(DARK_COLOR);
    break;
  case STEEL:
    this->setText("Steel");
    this->background.setFillColor(STEEL_COLOR);
    break;
  case FAIRY:
    this->setText("Fairy");
    this->background.setFillColor(FAIRY_COLOR);
    break;
  default:;
  }
}

Character::HUD::Label::Label(std::string text)
{
  this->_font.loadFromFile(FONT);
  this->text.setFont(this->_font);
  this->text.setCharacterSize(TEXT_SIZE);
  this->setText(text);
}

void Character::HUD::Label::setPosition(sf::Vector2f pos)
{
  this->_position = pos;
  this->background.setPosition(pos);
  this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
  this->text.setPosition(pos.x + this->background.getGlobalBounds().width / 2.f, pos.y + TEXT_SIZE - 6.f);
}

void Character::HUD::Label::setText(std::string text)
{
  this->str = text;
  this->text.setString(text);
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

Character::HUD::Portrait::Portrait(sf::Vector2f size, std::string filepath)
{
  this->_texture.loadFromFile(filepath);
  this->background.setSize(size);
  this->background.setFillColor(sf::Color(0x7F, 0x7F, 0x7F));
  this->background.setOutlineColor(sf::Color::Black);
  this->background.setOutlineThickness(1.f);
  this->image.setSize(size);
  this->image.setTexture(new sf::Texture(this->_texture));
}

void Character::HUD::Portrait::setPosition(sf::Vector2f pos)
{
  this->background.setPosition(pos);
  this->image.setPosition(pos);
}

void Character::HUD::Portrait::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->background, states);
  target.draw(this->image, states);
}
