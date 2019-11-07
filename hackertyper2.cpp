#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

int getFileLen(std::ifstream* f)
{
  f ->seekg(0,f -> end);
  int len = f ->tellg();
  f -> seekg(0,f -> beg);
  return len;
}

void addLetters(char beDrawn[], char Text[], int pos, int currentPos)
{
  beDrawn[currentPos - 2] = Text[pos - 2];
  beDrawn[currentPos - 1] = Text[pos - 1];
  beDrawn[currentPos] = '\0';
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

int shiftAndShorten(char txt[], int length)
{
  int k = 0;
  while ((txt[k] != '\n') and (txt[k] != '\0'))
    k++;
  k++;
  int i = k;
  while (txt[i] != '\0') 
  {
    txt[i - k] = txt[i];
    i++;
  }
  length -= k;
  txt[i - k] = '\0';
  return length;
}

void keyPressed(int* pos, int* currentPos, int len, char beDrawn[], char text[], sf::RenderWindow* window, sf::Text* TEXT)
{
  (*pos) += 2;
  (*currentPos) += 2;
  if ((*pos) >= len - 2)
  {
    *pos = 0;
    beDrawn[0] = '\0';
  }
  addLetters(beDrawn, text, *pos, *currentPos);
  drawText(beDrawn, window, TEXT);
  if (countLines(beDrawn, *currentPos) > 30)
    *currentPos = shiftAndShorten(beDrawn, *currentPos);

  window -> clear();
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

  char* text = new char[len];
  f.read(text, len);
  f.close();
  
  char* beDrawn = new char[len];

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
      if (event.type == sf::Event::KeyPressed)
        keyPressed(&pos, &currentPos, len, beDrawn, text, &window, &TEXT);
    }
  }
  delete[] text;
  delete[] beDrawn;
  return 0;
}
    
