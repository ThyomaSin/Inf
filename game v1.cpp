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

    int caught = 0;
    bool ifstate = false;
    while (true)
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

      ifstate = gameOver(player, level);

      checkCollision(player, b_features, &caught, n);

      if (gameContinue(ifstate, caught, n))
        break;

      txSleep(4);

      txClear();
    }
    if (ifstate)
      std::cout << "YOU LOOSE!";
    if (caught == n)
      std::cout << "YOU WON!";
    th_again();
    std::cin >> again;
  }
  return 0;
}
