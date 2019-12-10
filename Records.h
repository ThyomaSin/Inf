#include <fstream>
#include <time.h>

class Records : public DrawableObj
{
  public:
  std::string text;
  sf::Text TEXT;
  sf::Font font;
  int time = 0;
  
  Records(sf::Font font, int characterSize, sf::Color color);
  void initTime(int t);
  void draw(sf::RenderWindow* window);
  void initText();
  void commitChanges();
};

Records::Records(sf::Font font, int characterSize, sf::Color color)
{
  this -> font = font;
  TEXT.setFont(this -> font);
  TEXT.setCharacterSize(characterSize);
  TEXT.setColor(color);
}

std::string getDate()
{
  const time_t timer = time(NULL);
  return timer + " ";
}


void Records::initTime(int t)
{
  time = t;
}

void Records::draw(sf::RenderWindow* window)  
{
  window -> draw(TEXT);
}

void Records::initText()
{
  TEXT.setString(text);
}

void Records::commitChanges()
{
  std::ifstream read;
  read.open("resources/Records.txt");
  
  std::getline(read, text, '\0');
  read.close();
  
  char T;
  std::sprintf(&T,"%d", time);
  std::string s = getDate() + T + '\n' + text;
  text = s;  

  std::ofstream write;
  write.open("resources/Records.txt");
  write << text << std::endl;
}














