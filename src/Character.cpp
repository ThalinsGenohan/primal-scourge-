#include "pch.h"
#include "Character.h"

#include "HUD.h"

Character::Character() : _species(), _hp(0), _maxHp(0), _type1(), _type2(), _strength(), _dexterity(), _special(), _vitality(), _primality(0), _exp(0), _hud(new HUD("assets/portraits/sprite_0.png", "Thalins"))
{
  for (auto i = 0; i < STATUS_COUNT; i++)
  {
    this->_statuses[Status(i)] = false;
  }
  this->_hud->setPosition({ MARGIN, MARGIN });

}

void Character::setPosition(sf::Vector2f pos) const
{
  this->_hud->setPosition(pos);
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(*this->_hud, states);
}

