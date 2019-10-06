#include <iostream>
#include <SFML/Graphics.hpp>
#include "uI.h"
#include "Vector2f.h"


const float dt = 1;

struct Ball
{
  int r = 10;
  int red = 255;
  int green = 255;
  int blue = 0;
  Vector2f position;
  Vector2f velocity;
};


float velocity(Ball ball);

void drawBall(Ball ball, sf::RenderWindow* window)
{
  sf::CircleShape circle(ball.r);
  circle.setPosition(ball.position.x - ball.r, ball.position.y - ball.r);
  
  for(int i = ball.r; i > 1; i--)
  {
    int red_i = ball.red - ball.red * i / ball.r;
    int green_i = ball.green - ball.green * i / ball.r;
    int blue_i = ball.blue - ball.blue * i / ball.r;
    
    circle.setFillColor(sf::Color(red_i, green_i, blue_i));
    (*window).draw(circle);
    circle.setRadius(i);
    
    float cx = ball.position.x - i + (ball.r - i) / 2;
    float cy = ball.position.y - i + (ball.r - i) / 2.3;
    circle.setPosition(cx, cy);   
  }
}

void wallHit(Ball* ball)
{
  if ((*ball).position.y > 600 - (*ball).r)
  {
    (*ball).position.y = 600 - (*ball).r;
    (*ball).velocity.y = -(*ball).velocity.y;
  }
  if ((*ball).position.y < (*ball).r)
  {
    (*ball).position.y = 0 + (*ball).r;
    (*ball).velocity.y = -(*ball).velocity.y;
  }
  if ((*ball).position.x > 1000 - (*ball).r)
  {
    (*ball).position.x = 1000 - (*ball).r;
    (*ball).velocity.x = -(*ball).velocity.x;
  }
  if ((*ball).position.x < (*ball).r)
  {
    (*ball).position.x = (*ball).r;
    (*ball).velocity.x = -(*ball).velocity.x;
  }

}

void moveBall(Ball* ball, float dt)
{
  (*ball).position = add((*ball).position, (*ball).velocity);
}

void slowDown(Ball* ball, float acc, float Vmin)
{
  if (velocity(*ball) > Vmin)
    (*ball).velocity = mul((*ball).velocity, acc);
}


/*void controlBall(Ball* ball, float dv)
{
  if (GetAsyncKeyState(VK_LEFT))
    (*ball).velocity.x -= dv;
  if (GetAsyncKeyState(VK_UP))
    (*ball).velocity.y -= dv;
  if (GetAsyncKeyState(VK_RIGHT))
    (*ball).velocity.x += dv;
  if (GetAsyncKeyState(VK_DOWN))
    (*ball).velocity.y += dv;
}
*/

bool checkCollision(Ball ball1, Ball ball2)
{
  return (len(add(ball1.position, mul(ball2.position, -1))) < ball1.r + ball2.r);
}

void resolveCollision(Ball* ball1, Ball* ball2)
{
  float ro = 1;
  Vector2f r = add((*ball1).position, mul((*ball2).position, -1));
  Vector2f v = add((*ball1).velocity, mul((*ball2).velocity, -1));
  if (scMul(r,v) > 0)
    return;

  r = mul(r, 1/ (len(r)));

  Vector2f n;
  n.x = - r.y;
  n.y = r.x;

  float m1 = (4*3,14/3) * (*ball1).r * th_sqr((*ball1).r) * ro;
  float m2 = (4*3,14/3) * (*ball2).r * th_sqr((*ball2).r) * ro;

  Vector2f v1_n = mul(n, scMul((*ball1).velocity, n));
  Vector2f v2_n = mul(n, scMul((*ball2).velocity, n));

  float k = (m1  / m2);
  float v1 = scMul((*ball1).velocity, r);
  float v2 = scMul((*ball2).velocity, r);

  float a = 1 + k;
  float b = -2 * v2 - 2 * k * v1;
  float c = (k - 1) * th_sqr(v1) + 2 * v1 * v2;

  if (th_sqr(b) - 4*a*c < 0)
    std::cout << "d < 0";

  float v1_ = (-b + sqrt(th_sqr(b) - 4*a*c)) / (2 * a);
  float v2_ = k * (v1 - v1_) + v2;

  (*ball1).velocity = add(v1_n, mul(r, v1_));
  (*ball2).velocity = add(v2_n, mul(r, v2_));
}

float velocity(Ball ball)
{
  return len(ball.velocity);
}
