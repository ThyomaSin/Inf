#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class string
{
  public:
  int nmax;
  char* s;
  int currentPos = 0;

  void append(string* Text);
  void draw(sf::RenderWindow* window, sf::Text* TEXT);
  int countLines();
  void shiftAndShorten();
  string(int nmax);
  string();
  ~string();
};
  
string::string(int nmax)
{
  this -> s = new char[nmax];
}

string::string()
{
}

string::~string()
{
  delete[] s;
}

int getFileLen(std::ifstream* f)
{
  f -> seekg(0,f -> end);
  int len = f -> tellg();
  f -> seekg(0,f -> beg);
  return len;
}

void string::append(string* Text)
{
  this -> currentPos += 2;
  Text -> currentPos += 2;
  (this -> s)[this -> currentPos - 2] = (Text -> s)[Text -> currentPos - 2];
  (this -> s)[this -> currentPos - 1] = (Text -> s)[Text -> currentPos - 1];
  (this -> s)[this -> currentPos] = '\0';
}
  
void string::draw(sf::RenderWindow* window, sf::Text* TEXT)
{
  TEXT -> setString(this -> s);
  window -> draw((*TEXT));
  TEXT -> setString("");
}

int string::countLines()
{
  int num = 0;
  for(int i = 0; i < this -> currentPos; i++)
    if ((this -> s)[i] == '\n')
      num += 1;
  return num;
}

void string::shiftAndShorten()
{
  int k = 0;
  while ((this -> s[k] != '\n') and (this -> s[k] != '\0'))
    k++;
  k++;
  int i = k;
  while (this -> s[i] != '\0') 
  {
    this -> s[i - k] = this -> s[i];
    i++;
  }
  this -> currentPos -= k;
  this -> s[i - k] = '\0';
}

void keyPressed(int len, string* beDrawn, string* text, sf::RenderWindow* window, sf::Text* TEXT)
{
  if (text -> currentPos >= len - 2)
  {
    text -> currentPos = 0;
    beDrawn -> s[0] = '\0';
  }
  beDrawn -> append(text);
  if (beDrawn -> countLines() > 30)
    beDrawn -> shiftAndShorten();

  window -> clear();
  beDrawn -> draw(window, TEXT);
  window -> display();
}

int main()
{
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text TEXT;
  TEXT.setFont(font);
  TEXT.setCharacterSize(15);
  TEXT.setColor(sf::Color::Green);
  sf::RenderWindow window(sf::VideoMode(1000, 600), "hackerman");
  window.clear();
  

  std::ifstream f;
  f.open("hackertyper.txt");
  int len = getFileLen(&f);

  string text = string(len);
  f.read(text.s, len);
  f.close();
  
  string beDrawn = string(len);

  sf::Event event;
  
  while(window.isOpen())
  {
    while(window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
        return 0;
      }
      if (event.type == sf::Event::KeyPressed)
        keyPressed(len, &beDrawn, &text, &window, &TEXT);
    }
  }
  return 0;
}
    
