#include "Character.h"

Character::Character(): _species(), _hp(0), _maxHp(0), _type1(), _type2(), _primality(0), _exp(0)
{
  for (auto i = 0; i < STATUS_COUNT; i++)
  {
    this->_statuses[Status(i)] = false;
  }
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->_hud, states);
}

Character::HUD::HUD()
{
}

void Character::HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->_portrait, states);
}

void Character::HUD::Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->background, states);
  target.draw(this->text, states);
}

void Character::HUD::Bar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(this->background, states);
  target.draw(this->bar, states);
  target.draw(this->valueText, states);
  target.draw(this->maxText, states);
}
