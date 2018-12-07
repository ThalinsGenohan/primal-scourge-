#include "pch.h"

#include "TextManager.h"
#include "lang/lang.h"

TextManager::TextManager()
{
  this->_fonts[LANG_EN_US].loadFromFile("assets/fonts/Lucida Sans.ttf");
  this->_fonts[LANG_JA].loadFromFile("assets/fonts/KozGoPro-Regular.otf");
  this->setLanguage(LANG_EN_US);
}

std::map<std::string, std::wstring> TextManager::getTextDump() const
{
  return this->_active;
}

void TextManager::setLanguage(const Language language)
{
  this->_activeLanguage = language;
  this->_activeFont = this->_fonts[language];
  switch (language)
  {
  case LANG_JA:
    this->_active = lang::ja;
    break;
  default:
    this->_active = lang::en_us;
  }
}
