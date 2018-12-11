#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "CONSTANTS.h"

class Pokemon
{
public:
  Pokemon();
  Pokemon(int dexNum, std::string speciesName, Type type, std::array<int, 5> baseStats, int baseDef = 0);
  Pokemon(int dexNum, std::string speciesName, Type type1, Type type2, std::array<int, 5> baseStats, int baseDef = 0);

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

#define NO_POKEMON  Pokemon(0,   "N/A",               Type::NO_TYPE, Type::NO_TYPE, { 0,  0, 0, 0, 0 }, 0)
#define BULBASAUR   Pokemon(1,   "Bulbasaur",         Type::GRASS, Type::POISON,    { 6,  2, 1, 2, 2 }   )
#define IVYSAUR     Pokemon(2,   "Ivysaur",           Type::GRASS, Type::POISON,    { 8,  2, 2, 3, 2 }   )
#define VENUSAUR    Pokemon(3,   "Venusaur",          Type::GRASS, Type::POISON,    { 10, 3, 3, 3, 3 }, 1)
#define MVENUSAUR   Pokemon(3,   "Mega Venusaur",     Type::GRASS, Type::POISON,    { 10, 3, 3, 4, 3 }, 1)
#define CHARMANDER  Pokemon(4,   "Charmander",        Type::FIRE,                   { 5,  1, 2, 2, 1 }   )
#define CHARMELEON  Pokemon(5,   "Charmeleon",        Type::FIRE,                   { 7,  2, 3, 2, 2 }   )
#define CHARIZARD   Pokemon(6,   "Charizard",         Type::FIRE, Type::FLYING,     { 10, 3, 3, 3, 3 }, 1)
#define MCHARIZARDX Pokemon(6,   "Mega Charizard X",  Type::FIRE, Type::DRAGON,     { 10, 4, 3, 3, 3 }, 1)
#define MCHARIZARDY Pokemon(6,   "Mega Charizard Y",  Type::FIRE, Type::FLYING,     { 10, 3, 3, 4, 3 }, 1)
#define SQUIRTLE    Pokemon(7,   "Squirtle",          Type::WATER,                  { 6,  2, 1, 2, 2 }   )
#define WARTORTLE   Pokemon(8,   "Wartortle",         Type::WATER,                  { 7,  2, 2, 2, 2 }, 1)
#define BLASTOISE   Pokemon(9,   "Blastoise",         Type::WATER,                  { 10, 3, 2, 3, 3 }, 1)
#define MBLASTOISE  Pokemon(9,   "Mega Blastoise",    Type::WATER,                  { 10, 3, 2, 4, 3 }, 1)

#define VULPIX      Pokemon(37,  "Vulpix",            Type::FIRE,                   { 5,  1, 2, 2, 1 }   )
#define AVULPIX     Pokemon(37,  "Alolan Vulpix",     Type::ICE,                    { 5,  1, 2, 2, 1 }   )
#define NINETALES   Pokemon(38,  "Ninetales",         Type::FIRE,                   { 9,  2, 3, 3, 3 }, 1)
#define ANINETALES  Pokemon(39,  "Alolan Ninetales",  Type::ICE, Type::FAIRY,       { 9,  2, 3, 3, 3 }, 1)

#define EEVEE       Pokemon(133, "Eevee",             Type::NORMAL,                 { 7,  2, 2, 2, 2 }   )
#define VAPOREON    Pokemon(134, "Vaporeon",          Type::WATER,                  { 16, 2, 2, 3, 3 }   )
#define JOLTEON     Pokemon(135, "Jolteon",           Type::ELECTRIC,               { 8,  2, 4, 3, 2 }   )
#define FLAREON     Pokemon(136, "Flareon",           Type::FIRE,                   { 8,  3, 2, 3, 2 }, 1)

#define ARCTICUNO   Pokemon(144, "Arcticuno",         Type::ICE, Type::FLYING,      { 11, 3, 3, 3, 3 }, 1)
#define ZAPDOS      Pokemon(145, "Zapdos",            Type::ELECTRIC, Type::FLYING, { 11, 3, 3, 3, 3 }, 1)
#define MOLTRES     Pokemon(146, "Moltres",           Type::FIRE, Type::FLYING,     { 11, 3, 3, 3, 3 }, 1)

#define MEWTWO      Pokemon(150, "Mewtwo",            Type::PSYCHIC,                { 13, 3, 4, 4, 3 }, 1)
#define MEW         Pokemon(151, "Mew",               Type::PSYCHIC,                { 13, 3, 3, 3, 3 }, 1)
