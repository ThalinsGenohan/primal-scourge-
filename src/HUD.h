#pragma once

#include <SFML/Graphics.hpp>

#include "Character.h"

class Character::HUD : public Drawable
{
public:
  struct Label : Drawable
  {
    sf::RectangleShape background;
    sf::Text text;

    std::string str;

    void setPosition(sf::Vector2f pos);

  private:
    sf::Font _font;

    sf::Vector2f _position;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  };
  struct Bar : Drawable
  {
    sf::RectangleShape background;
    sf::RectangleShape bar;
    sf::Text valueText;
    sf::Text maxText;

    int value;
    int max;

    void setPosition(sf::Vector2f pos);

  private:
    sf::Font _font;

    sf::Vector2f _position;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  };

  HUD();
  HUD(std::string portraitFilepath, std::string name);

  void setPosition(sf::Vector2f pos);

  sf::Text getName() const { return this->_name; }
  sf::Sprite getPortrait() const { return this->_portrait; }
  Label getType1() const { return this->_type1; }
  Label getType2() const { return this->_type2; }
  Bar getHpBar() const { return this->_hpBar; }
  Label getStrength() const { return this->_strength; }
  Label getDexterity() const { return this->_dexterity; }
  Label getSpecial() const { return this->_special; }
  Label getVitality() const { return this->_vitality; }
  std::array<sf::RectangleShape, 5> getPrimality() const { return this->_primality; }

private:
  sf::Font _font;
  sf::Texture _portraitTexture;

  sf::Vector2f _position;

  sf::Text _name;
  sf::Sprite _portrait;
  Label _type1;
  Label _type2;
  Bar _hpBar;
  Label _strength;
  Label _dexterity;
  Label _special;
  Label _vitality;
  std::array<sf::RectangleShape, 5> _primality;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};