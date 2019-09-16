#include <iostream>
#include "TXLib.h"
const float dt = 1;

void drawBall(int x, int y, int r, int red, int green, int blue)
{
  int i;
  for(i = r; i > 1; i--)
  {
    int red_i = red - red * i / r;
    int green_i = green - green * i / r;
    int blue_i = blue - blue * i / r;

    txSetColor(RGB(red_i,green_i,blue_i));
    txSetFillColor(RGB(red_i,green_i,blue_i));
    txCircle(x-(r-i)/2,y-(r-i)/2.3,i);
  }
  txSetColor(RGB(0,0,0));
  txSetFillColor(RGB(0,0,0));
}

void moveBall(float* x, float* y, float* vx, float* vy, float dt, float r)
{
  if ((*y > 600 - r) or (*y < r))
    *vy = -*vy;
  if ((*x > 1000 - r) or (*x < r))
    *vx = -*vx;

  *x += *vx * dt;
  *y += *vy * dt;

  if (*vx > 0.9)
    *vx *= 0.99;
  if (*vy > 0.9)
    *vy *= 0.99;

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
  *vy *= 0.98;
  *vx *= 0.98;
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
