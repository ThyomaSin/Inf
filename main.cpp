
#include "balls.h"
#include <iostream>


int main()
{
  float dv = 0.3;
  sf::RenderWindow window(sf::VideoMode(1000, 600), "Balls fly");
  GrManager objects;

  int n = getNumber();
  Ball player = Ball(Vector2f(800, 400), Vector2f(0, 0), 30, 255, 0, 255);
  Ball* b_features = new Ball[n];

  objects.registrate(&player);
  
  b_features[0].green = 0;

  for(int i = 0; i < n; i++)
  {
    objects.registrate(&(b_features[i]));
    int vx = (i + 1) % 8;
    int vy = (n - i + 1) % 8;
    b_features[i].velocity.x = vx;
    b_features[i].velocity.y = vy;
    b_features[i].position.x += 20 + 25 * (i % 30);
    b_features[i].position.y += 20 + 25 * (i / 30);
  }

  sf::Event event;
  void* pointer = &window;
  while (window.isOpen())
  {
    objects.drawAll(pointer);                      //draw

    for (int i = 0; i < n; i++)  //physics
    {
      b_features[i].move(dt);
      b_features[i].wallHit();
      b_features[i].slowDown(1, 2);
    }
    player.move(dt);
    player.wallHit();
    player.slowDown(0.99, 0);

    for (int i = 0; i < n; i++)
      if (player.checkCollision(b_features[i]))
        player.resolveCollision(&b_features[i]);

    for (int i = 0; i < n - 1; i++)
      for (int j = i + 1; j < n; j++)
        if (b_features[i].checkCollision(b_features[j]))
          b_features[i].resolveCollision(&b_features[j]);
   
    while(window.pollEvent(event))  //events
    {
      if (event.type == sf::Event::Closed)
      { 
        window.close();
        break;
      }
      if (event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Space)
        { 
          window.close();
          break;
        }
    }

    controlBall(&player, dv);  //controlling&feedback
  }

  delete[] b_features;
  return 0;
}

