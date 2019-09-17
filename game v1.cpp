#include "TXLib.h"
#include "balls.h"
#include <iostream>
#include "uI.h"

int main()
{
  float dv = 0.3;

  txCreateWindow(1000,600);

  int level = 1;
  th_level();
  std::cin >> level;

  drawCircle(500,300,level);

  float n = th_ball();

  Ball b_features[50], player;
  Ball safe_b, safe_p;

  int r,red,green,blue = {0};
  th_ball_f();
  std::cin >> r >> red >> green >> blue;

  th_safe(r, red, green, blue, &safe_b);

  th_player();
  std::cin >> r >> red >> green >> blue;
  th_safe(r, red, green, blue, &safe_p);

  int again = 1;

  while (again)
  {
    th_paste_b(safe_b, b_features, n);
    th_paste_p(safe_p, &player);

    for (int i = 0; i < 30; i++)
      std::cout << std::endl;

    int state = 0;
    int caught = 0;
    bool ifstate = false;
    while (!state)
    {
      drawCircle(500,300,level);
      for (int i = 0; i < n; i++)
      {
        drawBall(b_features[i].x, b_features[i].y, b_features[i].r, b_features[i].red, b_features[i].green, b_features[i].blue);
        moveBall(&b_features[i].x, &b_features[i].y, &b_features[i].vx, &b_features[i].vy, dt);
        wallHit(&b_features[i].x, &b_features[i].y, &b_features[i].vx, &b_features[i].vy, b_features[i].r);
        slowDown(&b_features[i].vx, &b_features[i].vy);
      }
      drawBall(player.x, player.y, player.r, player.red, player.green, player.blue);
      moveBall(&player.x, &player.y, &player.vx, &player.vy, dt);
      slowDownPlayer(&player.vx, &player.vy);

      controlBall(&player.vx, &player.vy, dv);
      ifstate = ifstate or (player.x < player.r) or (player.x > 1000 - player.r);
      ifstate = ifstate or (player.y < player.r) or (player.y > 600 - player.r);
      ifstate = ifstate or sqrt(th_sqr(player.x - 500) + th_sqr(player.y - 300)) < player.r + level*20;
      if (ifstate)
        state = 1;

      for (int i = 1; i <= n; i++)
        if (sqrt(th_sqr(player.x - b_features[i].x) + th_sqr(player.y - b_features[i].y)) < player.r + b_features[i].r)
        {
          b_features[i].r = -player.r - 1;
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
    th_again();
    std::cin >> again;
  }
  return 0;
}
