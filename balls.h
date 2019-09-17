#include <iostream>
#include "TXLib.h"
const float dt = 1;

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

void th_paste_b(Ball safe, Ball b_features[], float n)
{
  for(int i = 0; i < n; i++)
  {
    b_features[i].r = safe.r;
    b_features[i].red = safe.red;
    b_features[i].green = safe.green;
    b_features[i].blue = safe.blue;
    b_features[i].x = 700;
    b_features[i].y = 400;
    b_features[i].vx = (n / 2 - i + 0.3) * 0.7 +0.3 ;
    b_features[i].vy = th_sqr(i - n / 2) * 0.1 + 10;
  }
}

void th_safe(float r, int red, int green, int blue, Ball* safe)
{
  (*safe).r = r;
  (*safe).red = red;
  (*safe).green = green;
  (*safe).blue = blue;
}

void th_paste_p(Ball safe, Ball* player)
{
  (*player).r = safe.r;
  (*player).red = safe.red;
  (*player).green = safe.green;
  (*player).blue = safe.blue;
  (*player).x = 200;
  (*player).y = 200;
  (*player).vx = 0;
  (*player).vy = 0;
}


