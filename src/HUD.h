#pragma once

#include <SFML/Graphics.hpp>

#include "Character.h"

class Character::HUD : public Drawable
{
public:
  struct Label : Drawable
  {
    explicit Label(std::string text);

    sf::RectangleShape background;
    sf::Text text;

    std::string str;

    sf::Vector2f getSize() const { return this->background.getSize(); }

    void setPosition(sf::Vector2f pos);
    void setText(std::string text);

  protected:
    sf::Font _font;

    sf::Vector2f _position;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  };
  struct TypeLabel : Label
  {
    explicit TypeLabel(Type type);

    void setType(Type type);

  private:
    Type _type;
  };
  struct Bar : Drawable
  {
    Bar() : value(0), max(0) {}

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
  struct Portrait : Drawable
  {
    explicit Portrait(sf::Vector2f size, std::string filepath);

    sf::RectangleShape background;
    sf::RectangleShape image;

    void setPosition(sf::Vector2f pos);

  private:
    sf::Texture _texture;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  };

  HUD();
  HUD(std::string portraitFilepath, std::string name);

  void setPosition(sf::Vector2f pos);

  sf::Text getName() const { return this->_name; }
  Portrait getPortrait() const { return this->_portrait; }
  TypeLabel getType1() const { return this->_type1; }
  TypeLabel getType2() const { return this->_type2; }
  Bar getHpBar() const { return this->_hpBar; }
  Label getStrength() const { return this->_strength; }
  Label getDexterity() const { return this->_dexterity; }
  Label getSpecial() const { return this->_special; }
  Label getVitality() const { return this->_vitality; }
  std::array<sf::RectangleShape, 5> getPrimality() const { return this->_primality; }

private:
  sf::Font _font;

  sf::Vector2f _position;

  sf::Text _name;
  Portrait _portrait;
  TypeLabel _type1;
  TypeLabel _type2;
  Bar _hpBar;
  Label _strength;
  Label _dexterity;
  Label _special;
  Label _vitality;
  std::array<sf::RectangleShape, 5> _primality;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};