#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

void drawText(char text[], char wroten[], int i, int j, sf::RenderWindow* window, sf::Text* TEXT)
{
  wroten[j] = text[i];
  wroten[j+1] = text[i+1];
  char* s = new char[j+2];
  for (int k = 0; k <= j+1; k++)
    s[k] = wroten[k]; 
  
  (*TEXT).setString(s);
  (*window).draw((*TEXT));
  (*TEXT).setString("");
  delete[] s;
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
  for (int i = 0; i < length; i++)
    if (txt[i] == '\n')
    {
      k = i + 1;
      break;
    }
  for (int i = k; i < length; i++)
    txt[i - k] = txt[i];
  length -= k;
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

  sf::RenderWindow window(sf::VideoMode(1000, 600), "hackerman");
  window.clear();
  
  char* text = new char[len];
  char* wroten = new char[len];
  f.read(text, len);
  f.close();
  
  int i = 0;
  int j = 0;
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
      {
        window.clear();
        drawText(text, wroten, i, j, &window, &TEXT);
        i += 2;
        j += 2;
        window.display();
      }
      if (countLines(wroten, j) > 30)
        j = shorten(wroten, j);
      if (i >= len - 1)
      {
        i = 0;
        j = 0;
      }
    }
  }
  delete[] text;
  delete[] wroten;
  return 0;
}
    
