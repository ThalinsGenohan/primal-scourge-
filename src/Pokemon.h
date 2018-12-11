#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "CONSTANTS.h"

class Pokemon
{
public:
  Pokemon();
  Pokemon(int dexNum, std::string speciesName, std::array<Type, 2> types, std::array<int, 6> baseStats);

private:
  Species _species;
  std::string _speciesName;

  int _baseHealth;
  int _baseStrength;
  int _baseDexterity;
  int _baseSpecial;
  int _baseVitality;
  int _baseDefense;
};

#define NO_POKEMON  Pokemon(0, "N/A", { Type::NO_TYPE, Type::NO_TYPE }, { 0, 0, 0, 0, 0, 0 })
#define BULBASAUR   Pokemon(1, "Bulbasaur", { Type::GRASS, Type::POISON }, { 6, 2, 1, 2, 2, 0 })
#define IVYSAUR     Pokemon(2, "Ivysaur", { Type::GRASS, Type::POISON }, { 8, 2, 2, 3, 2, 0 })
#define VENUSAUR    Pokemon(3, "Venusaur", { Type::GRASS, Type::POISON }, { 10, 3, 3, 3, 3, 1})
#define CHARMANDER  Pokemon(4, "Charmander")
