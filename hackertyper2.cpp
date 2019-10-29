#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

/*int getFileLen(std::fstream f)
{
  
  return len;
}*/

void addLetters(char beDrawn[], char Text[], int pos, int currentPos)
{
  beDrawn[currentPos] = Text[pos];
  beDrawn[currentPos + 1] = Text[pos + 1];
  beDrawn[currentPos + 2] = '\0';
}
  
void drawText(char beDrawn[], sf::RenderWindow* window, sf::Text* TEXT)
{
  TEXT -> setString(beDrawn);
  window -> draw((*TEXT));
  TEXT -> setString("");
}

int countLines(char txt[], int length)
{
  int num = 0;
  for (int i = 0; i < length; i++)
    if (txt[i] == '\n')
      num += 1;
  return num;
}

int shorten(char txt[], int length)
{
  int k = 0;
  while ((txt[k] != '\n') and (txt[k] != '\0'))
    k++;
  int i = k + 1;
  while (txt[i] != '\0') 
  {
    txt[i - k] = txt[i];
    i++;
  }
  length -= k;
  txt[i - k] = '\0';
  return length;
}


int main()
{
  sf::Font font;
  font.loadFromFile("arial.ttf");
  sf::Text TEXT;
  TEXT.setFont(font);
  TEXT.setCharacterSize(15);
  TEXT.setColor(sf::Color::Green);

  std::fstream f;
  f.open("hackertyper.txt");
  f.seekg(0,f.end);
  int len = f.tellg();
  f.seekg(0,f.beg); 
  char* text = new char[len];
  f.read(text, len);
  f.close();
  
  char* beDrawn = new char[len];

  sf::RenderWindow window(sf::VideoMode(1000, 600), "hackerman");
  window.clear();
  
  int pos = 0;
  int currentPos = 0;
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
      if (pos >= len - 2)
      {
        pos = 0;
        beDrawn[0] = '\0';
      }
      if (event.type == sf::Event::KeyPressed)
      {
        window.clear();
        addLetters(beDrawn, text, pos, currentPos);
        drawText(beDrawn, &window, &TEXT);
        pos += 2;
        currentPos += 2;
        window.display();
      }
      if (countLines(beDrawn, currentPos) > 30)
        currentPos = shorten(beDrawn, currentPos);
    }
  }
  delete[] text;
  delete[] beDrawn;
  return 0;
}
    
