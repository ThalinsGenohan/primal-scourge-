#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "src/CONSTANTS.h"
#include <map>
#include <TGUI/TGUI.hpp>

class Character
{
public:
  struct Stat
  {
    int base;
    int boost;
    int bonus;
    int buff;

    int cost;
  };

  Character();

  std::string getName() const;
  Species getSpecies() const;
  int getHp() const;
  int getMaxHp() const;
  Type getType1() const;
  Type getType2() const;
  Stat getStrength() const;
  Stat getDexterity() const;
  Stat getSpecial() const;
  Stat getVitality() const;
  int getPrimality() const;
  bool isAsleep() const;
  bool isBurned() const;
  bool isConfused() const;
  bool isEntangled() const;
  bool isFlinching() const;
  bool isFrozen() const;
  bool isParalyzed() const;
  bool isPoisoned() const;
  bool isBadlyPoisoned() const;
  bool isScared() const;
  bool isTerrified() const;
  bool isStaggered() const;
  bool isFainted() const;
  int getExp() const;

private:
  std::string _name;
  Species _species;
  int _hp;
  int _maxHp;
  Type _type1;
  Type _type2;
  Stat _strength;
  Stat _dexterity;
  Stat _special;
  Stat _vitality;
  int _primality;
  std::map<Status, bool> _statuses;
  int _exp;

  sf::Font _font;
  sf::Text _nameLabel;
  sf::RectangleShape _portraitOutline;
  sf::Texture _portraitTexture;
  sf::Sprite _portrait;
  sf::RectangleShape _type1LabelBg;
  sf::Text _type1Label;
  sf::RectangleShape _type2LabelBg;
  sf::Text _type2Label;
  sf::RectangleShape _hpBarOutline;
  sf::RectangleShape _hpBar;
  sf::RectangleShape _strLabelBg;
  sf::Text _strLabel;
  sf::RectangleShape _dexLabelBg;
  sf::Text _dexLabel;
  sf::RectangleShape _speLabelBg;
  sf::Text _speLabel;
  sf::RectangleShape _vitLabelBg;
  sf::Text _vitLabel;
  std::vector<sf::RectangleShape> _primalityMeter;
  
};

#endif
