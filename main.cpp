
#include "balls.h"
#include <iostream>


int main()
{
  float dv = 0.3;
  sf::RenderWindow window(sf::VideoMode(1000, 600), "Balls fly");
  window.clear();

  int n = getNumber();

  Ball player;
  Ball* b_features = new Ball[n];

  b_features[0].green = 0;

  for(int i = 0; i < n; i++)
  {
    b_features[i].velocity.x = th_sqr(n / 2 - (i % 40) + 0.5) * 0.002;
    b_features[i].velocity.y = th_sqr((i % 40) - n / 2)*0.002;
    b_features[i].position.x += 25 * (i % 20);
    b_features[i].position.y += 20 + 25 * (i / 20);
  }


  player.r = 30;
  player.green = 0;
  player.position.x = 800;
  player.position.y = 400;
  player.velocity.x = 0;
  player.velocity.y = 0;

  for (int i = 0; i < 30; i++)
    std::cout << std::endl;

  while (true)
  {
    for (int i = 0; i < n; i++)
    {
      drawBall(b_features[i], &window);
      moveBall(&b_features[i], dt);
      wallHit(&b_features[i]);
      slowDown(&b_features[i], 1, 2);
    }
    drawBall(player, &window);
    moveBall(&player, dt);
    wallHit(&player);
    slowDown(&player, 0.99, 0);
    window.display();

    //controlBall(&player, dv);

    for (int i = 0; i < n; i++)
      if (checkCollision(player, b_features[i]))
        resolveCollision(&player, &b_features[i]);

    for (int i = 0; i < n - 1; i++)
      for (int j = i + 1; j < n; j++)
        if (checkCollision(b_features[i], b_features[j]))
          resolveCollision(&b_features[i], &b_features[j]);

    //if (GetAsyncKeyState(VK_SPACE))
      //break;
    std::cout << player.red << std::endl;

    window.clear();
  }

  delete[] b_features;
  return 0;
}

