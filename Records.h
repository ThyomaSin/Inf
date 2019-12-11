#include <fstream>
#include <time.h>

class Records
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
  struct tm* u;
  u = localtime(&timer);
  
  char year[5];
  std::sprintf(year,"%04d", u -> tm_year + 1900);
  char month[3];
  std::sprintf(month,"%02d", u -> tm_mon + 1);
  char day[3];
  std::sprintf(day,"%02d", u -> tm_mday);
  char hour[3];
  std::sprintf(hour,"%02d", u -> tm_hour);
  char min[3];
  std::sprintf(min,"%02d", u -> tm_min);
  char sec[3];
  std::sprintf(sec,"%02d", u -> tm_sec);
  
  std::string s;
  s += year;
  s += "_";
  s += month;
  s += "_";
  s += day;
  s += "   ";
  s += hour; 
  s += ":";
  s += min; 
  s += ":";
  s += sec;
  s += "  ";
  return s;
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
  
  char T[7];
  std::sprintf(T,"%6d", time);
  std::string s = getDate();
  s += T;
  s += '\n';
  s += text;
  text = s;  

  std::ofstream write;
  write.open("resources/Records.txt");
  write << text << std::endl;
}














