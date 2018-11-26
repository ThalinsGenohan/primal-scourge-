#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Font.hpp>


class TextManager
{
public:
  const enum Language
  {
    LANG_EN_US,
    LANG_JA
  };

  TextManager();

  sf::Font getActiveFont() const { return this->_activeFont; }
  Language getActiveLanguage() const { return this->_activeLanguage; }
  std::wstring getText(std::string id) const { return this->_active.at(id); }
  std::map<std::string, std::wstring> getTextDump() const;

  void setLanguage(const Language language);
private:
  std::map<Language, sf::Font> _fonts;

  Language _activeLanguage;
  sf::Font _activeFont;
  std::map<std::string, std::wstring> _active;
};
typedef std::shared_ptr<TextManager> TextManagerRef;

#endif
