#ifndef CHARACTER_H
#define CHARACTER_H

#include <array>
#include <map>
#include <string>

#include "CONSTANTS.h"

class Character : public sf::Drawable
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
  class HUD;

  Character();

  std::string getName() const { return this->_name; }
  Species getSpecies() const { return this->_species; }
  int getHp() const { return this->_hp; }
  int getMaxHp() const { return this->_maxHp; }
  Type getType1() const { return this->_type1; }
  Type getType2() const { return this->_type2; }
  Stat getStrength() const { return this->_strength; }
  Stat getDexterity() const { return this->_dexterity; }
  Stat getSpecial() const { return this->_special; }
  Stat getVitality() const { return this->_vitality; }
  int getPrimality() const { return this->_primality; }
  bool isAsleep() const { return this->_statuses.at(SLEEP); }
  bool isBleeding() const { return this->_statuses.at(BLEED); }
  bool isBurned() const { return this->_statuses.at(BURN); }
  bool isConfused() const { return this->_statuses.at(CONFUSE); }
  bool isEntangled() const { return this->_statuses.at(ENTANGLE); }
  bool isFlinching() const { return this->_statuses.at(FLINCH); }
  bool isFrozen() const { return this->_statuses.at(FREEZE); }
  bool isParalyzed() const { return this->_statuses.at(PARALYZE); }
  bool isPoisoned() const { return this->_statuses.at(POISON_STATUS); }
  bool isBadlyPoisoned() const { return this->_statuses.at(BAD_POISON); }
  bool isScared() const { return this->_statuses.at(SCARE); }
  bool isTerrified() const { return this->_statuses.at(TERRIFY); }
  bool isStaggered() const { return this->_statuses.at(STAGGER); }
  bool isFainted() const { return this->_statuses.at(FAINT); }
  int getExp() const { return this->_exp; }

  void setPosition(sf::Vector2f pos);

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

  HUD* _hud;
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
