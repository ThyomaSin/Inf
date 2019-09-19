#include "TXLib.h"
#include "uI.h"
#include "balls.h"
#include <iostream>

int th_level()
{
  int level = 1;
  std::cout << " Choose your level '1-10'"<< std::endl;
  std::cin >> level;
  return level;
}

float getNumber()
{
  float n = 0;
  do
  {
    std::cout << "How many Balls? '1-50'" << std::endl;
    std::cin >> n;
  }
  while ((n <= 0) or (n > 50));
  return n;
}

void th_ball_f()
{
  std::cout << "r, red, green, blue of the balls" << std::endl;
}

void th_player()
{
  std::cout << "r, red, green, blue of the PLAYER" << std::endl;
}

int th_again()
{
  int again = 1;
  std::cout << " play again? '1 - 0'" << std::endl;
  std::cin >> again;
  return again;
}

void drawBall(int x, int y, int r, int red, int green, int blue)
{
  COLORREF color = txGetFillColor();
  for(int i = r; i > 1; i--)
  {
    int red_i = red - red * i / r;
    int green_i = green - green * i / r;
    int blue_i = blue - blue * i / r;

    txSetColor(RGB(red_i,green_i,blue_i));
    txSetFillColor(RGB(red_i,green_i,blue_i));
    txCircle(x-(r-i)/2,y-(r-i)/2.3,i);
  }
  txSetColor(color);
  txSetFillColor(color);
}

void wallHit(float* x, float* y, float* vx, float* vy, float r)
{
  if ((*y > 600 - r) or (*y < r))
    *vy = -*vy;
  if ((*x > 1000 - r) or (*x < r))
    *vx = -*vx;
}

void moveBall(float* x, float* y, float* vx, float* vy, float dt)
{
  *x += *vx * dt;
  *y += *vy * dt;
}

void slowDown(float* vx, float* vy)
{
  if (*vx > 0.9)
    *vx *= 0.97;
  if (*vy > 0.9)
    *vy *= 0.97;
}

void slowDownPlayer(float* vx, float* vy)
{
  *vy *= 0.96;
  *vx *= 0.96;
}

void controlBall(float* vx, float* vy, float dv)
{
  if (GetAsyncKeyState(VK_LEFT))
    *vx -= dv;
  if (GetAsyncKeyState(VK_UP))
    *vy -= dv;
  if (GetAsyncKeyState(VK_RIGHT))
    *vx += dv;
  if (GetAsyncKeyState(VK_DOWN))
    *vy += dv;
}

void drawCircle(int x, int y, int level)
{
  txSetColor(RGB(255,0,0));
  txSetFillColor(RGB(255,0,0));
  txCircle(x,y,level*20);
  txSetColor(RGB(0,0,0));
  txSetFillColor(RGB(0,0,0));
  txCircle(x,y,level*20 - 5);
}

float th_sqr(float x)
{
  return x * x;
}

void th_download(string name ,Ball* safe)
{
  int r, red, green, blue = {1};
  if (name == "player")
  {
    th_player();
    std::cin >> r >> red >> green >> blue;
  }

  else
  {
    th_ball_f();
    std::cin >> r >> red >> green >> blue;
  }

  (*safe).r = r;
  (*safe).red = red;
  (*safe).green = green;
  (*safe).blue = blue;
}

void th_paste(Ball safe, Ball* player, string name, float n, int i)
{
  (*player).r = safe.r;
  (*player).red = safe.red;
  (*player).green = safe.green;
  (*player).blue = safe.blue;
  if (name == "ball")
  {
    (*player).x = 700;
    (*player).y = 400;
    (*player).vx = (n / 2 - i + 0.3) * 0.7 +0.3 ;
    (*player).vy = th_sqr(i - n / 2) * 0.1 + 10;
  }
  else
  {
    (*player).x = 200;
    (*player).y = 200;
    (*player).vx = 0;
    (*player).vy = 0;
  }
}

bool gameOver(Ball player, int level, int caught, int n)
{
  if ((player.x < player.r) or (player.x > 1000 - player.r))
    return true;
  if ((player.y < player.r) or (player.y > 600 - player.r))
    return true;
  if (sqrt(th_sqr(player.x - 500) + th_sqr(player.y - 300)) < player.r + level*20)
    return true;
  if (caught == n)
    return true;
  return false;
}

void catchTheBall(Ball player, Ball b_features[], int* caught, int n)
{
  for (int i = 0; i < n; i++)
    if (sqrt(th_sqr(player.x - b_features[i].x) + th_sqr(player.y - b_features[i].y)) < player.r + b_features[i].r)
      {
        b_features[i].r = -player.r - 1;
        *caught += 1;
      }
}


int main()
{
  float dv = 0.3;

  txCreateWindow(1000,600);

  int level = 1;
  level = th_level();

  drawCircle(500,300,level);

  float n = getNumber();

  Ball b_features[50], player;
  Ball safe_b, safe_p;

  th_download("balls", &safe_b);
  th_download("player", &safe_p);

  int again = 1;

  while (again)
  {
    for(int i = 0; i < n; i++)
      th_paste(safe_b, &b_features[i], "ball", n, i);
    th_paste(safe_p, &player, "player", n, 1);

    for (int i = 0; i < 30; i++)
      std::cout << std::endl;

    int caught = 0;
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

      catchTheBall(player, b_features, &caught, n);

      if (gameOver(player,level, caught, n))
        break;

      txSleep(4);

      txClear();
    }
    if (caught != n)
      std::cout << "YOU LOOSE!";
    else
      std::cout << "YOU WON!";
    again = th_again();
  }
  return 0;
}
