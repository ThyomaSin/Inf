#include "TXLib.h"
#include "balls.h"
#include <iostream>


struct Ball
{
  int r = 0;
  int red = 0;
  int green = 0;
  int blue = 0;
  float x = 0;
  float y = 0;
  float vx = 0;
  float vy = 0;
};

int main()
{
  float dv = 0.4;

  txCreateWindow(1000,600);

  int level = 1;
  userInt("level");
  std::cin >> level;

  drawCircle(500,300,level);

  float n = 0;
  do
  {
    userInt("balls");
    std::cin >> n;
  }
  while ((n <= 0) or (n > 50));

  Ball b_features[51];
  Ball safe[51];

  int r,red,green,blue = {0};
  userInt("ball_f");
  std::cin >> r >> red >> green >> blue;

  for(int i = 1; i <= n; i++)
  {
    b_features[i].r = r;
    b_features[i].red = red;
    b_features[i].green = green;
    b_features[i].blue = blue;
    b_features[i].x = 700;
    b_features[i].y = 400;
    b_features[i].vx = (n / 2 - i + 0.3) * 0.7 +0.3 ;
    b_features[i].vy = th_sqr(i - n / 2) * 0.1 + 10;
  }

  userInt("player");
  std::cin >> r >> red >> green >> blue;

  b_features[0].r = r;
  b_features[0].red = red;
  b_features[0].green = green;
  b_features[0].blue = blue;
  b_features[0].x = 200;
  b_features[0].y = 200;

  for (int i = 0; i <= n; i++)
  {
    safe[i].r = b_features[i].r;
    safe[i].red = b_features[i].red;
    safe[i].green = b_features[i].green;
    safe[i].blue = b_features[i].blue;
    safe[i].x = b_features[i].x;
    safe[i].y = b_features[i].y;
    safe[i].vx = b_features[i].vx;
    safe[i].vy = b_features[i].vy;
  }

  int again = 1;

  while (again)
  {
    for (int i = 0; i <= n; i++)
    {
      b_features[i].r = safe[i].r;
      b_features[i].red = safe[i].red;
      b_features[i].green = safe[i].green;
      b_features[i].blue = safe[i].blue;
      b_features[i].x = safe[i].x;
      b_features[i].y = safe[i].y;
      b_features[i].vx = safe[i].vx;
      b_features[i].vy = safe[i].vy;
    }

    for (int i = 0; i < 30; i++)
      std::cout << std::endl;

    int state = 0;
    int caught = 0;
    bool ifstate = false;
    while (!state)
    {
      drawCircle(500,300,level);
      for (int i = 0; i <= n; i++)
      {
        drawBall(b_features[i].x, b_features[i].y, b_features[i].r, b_features[i].red, b_features[i].green, b_features[i].blue);
        moveBall(&b_features[i].x, &b_features[i].y, &b_features[i].vx, &b_features[i].vy, dt);
        wallHit(&b_features[i].x, &b_features[i].y, &b_features[i].vx, &b_features[i].vy, b_features[i].r);
        slowDown(&b_features[i].vx, &b_features[i].vy);
      }
      slowDownPlayer(&b_features[0].vx, &b_features[0].vy);

      controlBall(&b_features[0].vx, &b_features[0].vy, dv);
      ifstate = ifstate or (b_features[0].x < b_features[0].r) or (b_features[0].x > 1000 - b_features[0].r);
      ifstate = ifstate or (b_features[0].y < b_features[0].r) or (b_features[0].y > 600 - b_features[0].r);
      ifstate = ifstate or sqrt(th_sqr(b_features[0].x - 500) + th_sqr(b_features[0].y - 300)) < b_features[0].r + level*20;
      if (ifstate)
        state = 1;

      for (int i = 1; i <= n; i++)
        if (sqrt(th_sqr(b_features[0].x - b_features[i].x) + th_sqr(b_features[0].y - b_features[i].y)) < b_features[0].r + b_features[i].r)
        {
          b_features[i].r = -b_features[0].r - 1;
          caught += 1;
        }

      if (caught == n)
        state = 2;

      txSleep(4);

      txClear();
    }
    if (state == 1)
      std::cout << "YOU LOOSE!";
    if (state == 2)
      std::cout << "YOU WON!";
    userInt("again");
    std::cin >> again;
  }
  return 0;
}
