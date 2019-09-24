#include <iostream>
#include "TXLib.h"
#include "uI.h"


const float dt = 1;

struct Ball
{
  int r = 10;
  int red = 200;
  int green = 200;
  int blue = 200;
  float x = 800;
  float y = 400;
  float vx = 0;
  float vy = 0;
};

void drawBall(Ball ball);

void moveBall(Ball* ball, float dt);

void wallHit(Ball* ball);

void slowDown(Ball* ball, float acc);

void controlBall(float* vx, float* vy, float dv);

void drawCircle(int x, int y, int level);

float th_sqr(float x);

bool gameOver(Ball player, int level, int caught, int n);

bool checkCollision(Ball ball1, Ball ball2);

void resolveCollision(Ball player, Ball* ball, int* caught);

float velocity(Ball ball);



void drawBall(Ball ball)
{
  COLORREF color = txGetFillColor();
  for(int i = ball.r; i > 1; i--)
  {
    int red_i = ball.red - ball.red * i / ball.r;
    int green_i = ball.green - ball.green * i / ball.r;
    int blue_i = ball.blue - ball.blue * i / ball.r;

    txSetColor(RGB(red_i,green_i,blue_i));
    txSetFillColor(RGB(red_i,green_i,blue_i));
    txCircle(ball.x - (ball.r - i) / 2, ball.y - (ball.r - i) / 2.3, i);
  }
  txSetColor(color);
  txSetFillColor(color);
}

void wallHit(Ball* ball)
{
  if (((*ball).y > 600 - (*ball).r) or ((*ball).y < (*ball).r))
    (*ball).vy = -(*ball).vy;
  if (((*ball).x > 1000 - (*ball).r) or ((*ball).x < (*ball).r))
    (*ball).vx = -(*ball).vx;
}

void moveBall(Ball* ball, float dt)
{
  (*ball).x += (*ball).vx * dt;
  (*ball).y += (*ball).vy * dt;
}

void slowDown(Ball* ball, float acc)
{
  (*ball).vx *= acc;
  (*ball).vy *= acc;
}

void controlBall(Ball* ball, float dv)
{
  if (GetAsyncKeyState(VK_LEFT))
    (*ball).vx -= dv;
  if (GetAsyncKeyState(VK_UP))
    (*ball).vy -= dv;
  if (GetAsyncKeyState(VK_RIGHT))
    (*ball).vx += dv;
  if (GetAsyncKeyState(VK_DOWN))
    (*ball).vy += dv;
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

bool checkCollision(Ball ball1, Ball ball2)
{
  return (sqrt(th_sqr(ball1.x - ball2.x) + th_sqr(ball1.y - ball2.y)) < ball1.r + ball2.r);
}

void resolveCollision(Ball player, Ball* ball, int* caught)
{
  *caught += 1;
  (*ball).r = - player.r - 1;
}

float velocity(Ball ball)
{
  return sqrt(th_sqr(ball.vx) + th_sqr(ball.vy));
}
