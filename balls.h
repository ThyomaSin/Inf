#include <iostream>
#include "TXLib.h"
const float dt = 1;

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
  *vy *= 0.98;
  *vx *= 0.98;
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

void userInt(string s)
{
  if (s == "level")
    std::cout << " Choose your level '1-10'"<< std::endl;
  if (s =="balls")
    std::cout << "How many Balls? '1-50'" << std::endl;
  if (s == "ball_f")
    std::cout << "r, red, green, blue of the balls" << std::endl;
  if (s == "player")
    std::cout << "r, red, green, blue of the PLAYER" << std::endl;
  if (s == "again")
    std::cout << " play again? '1 - 0'" << std::endl;
}
