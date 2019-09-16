#include "TXLib.h"
#include "balls.h"
#include <iostream>


int main()
{
  int i,j,r,red,green,blue,level,state;
  state = 0;
  float dv = 0.2;
  int caught = 0;
  bool ifstate = false;
  int again = 1;
  float n;

  txCreateWindow(1000,600);
  std::cout << " Choose your level '1-10'"<< std::endl;
  std::cin >> level;

  drawCircle(500,300,level);

  std::cout << "How many Balls? '1-20'" << std::endl;
  std::cin >> n;

  float b_features[21][8] = {0};
  float safe[21][8];

  std::cout << "r, red, green, blue of the balls" << std::endl;
  std::cin >> r >> red >> green >> blue;

  for(i = 1; i <= n; i++)
  {
    b_features[i][0] = r;
    b_features[i][1] = red;
    b_features[i][2] = green;
    b_features[i][3] = blue;
    b_features[i][4] = 700;
    b_features[i][5] = 400;
    b_features[i][6] = (n / 2 - i) * 0.7 + 4.5;
    b_features[i][7] = th_sqr(i - n / 2) * 0.1 + 10;
  }

  std::cout << "r, red, green, blue of the PLAYER" << std::endl;
  std::cin >> r >> red >> green >> blue;

  b_features[0][0] = r;
  b_features[0][1] = red;
  b_features[0][2] = green;
  b_features[0][3] = blue;
  b_features[0][4] = 200;
  b_features[0][5] = 200;

  for (i = 0; i <= n; i++)
    for (j = 0; j <= 7; j++)
      safe[i][j] = b_features[i][j];

  while (again == 1)
  {
    for (i = 0; i <= n; i++)
      for (j = 0; j <= 7; j++)
        b_features[i][j] = safe[i][j];

    for (i = 0; i < 30; i++)
      std::cout << std::endl;
    while (state == 0)
    {
      for (i = 0; i <= n; i++)
        drawBall(b_features[i][4], b_features[i][5], b_features[i][0], b_features[i][1], b_features[i][2], b_features[i][3]);
      drawCircle(500,300,level);

      txSleep(4);
      for (i = 0; i <= n; i++)
        moveBall(&b_features[i][4],&b_features[i][5], &b_features[i][6], &b_features[i][7], dt, b_features[i][0]);

      controlBall(&b_features[0][6], &b_features[0][7], dv);
      ifstate = ifstate or (b_features[0][4] < b_features[0][0]) or (b_features[0][4] > 1000 - b_features[0][0]);
      ifstate = ifstate or (b_features[0][5] < b_features[0][0]) or (b_features[0][5] > 600 - b_features[0][0]);
      ifstate = ifstate or sqrt(th_sqr(b_features[0][4] - 500) + th_sqr(b_features[0][5] - 300)) < b_features[0][0] + level*20;
      if (ifstate)
        state = 1;

      for (i = 1; i <= n; i++)
        if (sqrt(th_sqr(b_features[0][4] - b_features[i][4]) + th_sqr(b_features[0][5] - b_features[i][5])) < b_features[0][0] + b_features[i][0])
        {
          b_features[i][0] = -b_features[0][0] - 1;
          caught += 1;
        }

      if (caught == n)
        state = 2;

      txClear();
    }
    if (state == 1)
      std::cout << "YOU LOOSE!";
    if (state == 2)
      std::cout << "YOU WON!";
    std::cout << " play again? '1 - 0'" << std::endl;
    std::cin >> again;
    state = 0;
    caught = 0;
    ifstate = false;
  }
  return 0;
}
