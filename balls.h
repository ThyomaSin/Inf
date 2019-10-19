#include <iostream>
#include <SFML/Graphics.hpp>
#include "uI.h"
#include "Vector2f.h"


const float dt = 1;

class Ball
{
  public::
  int r = 7;
  int red = 255;
  int green = 255;
  int blue = 0;
  Vector2f position = Vector2f(100, 100);
  Vector2f velocity = Vector2f(100, 100);
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
  (*ball).position = (*ball).position + (*ball).velocity;
}

void slowDown(Ball* ball, float acc, float Vmin)
{
  if (velocity(*ball) > Vmin)
    ((*ball).velocity) * (acc);
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
  return ((ball1.position + (ball2.position) * (-1)).len() < ball1.r + ball2.r);
}

void resolveCollision(Ball* ball1, Ball* ball2)
{
  float ro = 1;
  Vector2f r = (*ball1).position + (((*ball2).position) * (-1));
  Vector2f v = (*ball1).velocity + (((*ball2).velocity) * (-1));
  if ((r ^ v) > 0)
    return;

  r = r * (1/ r.len());

  Vector2f n = Vector2f(-r.y, r.x);

  float m1 = (4*3,14/3) * (*ball1).r * th_sqr((*ball1).r) * ro;
  float m2 = (4*3,14/3) * (*ball2).r * th_sqr((*ball2).r) * ro;

  Vector2f v1_n = n * ((*ball1).velocity ^ (n));
  Vector2f v2_n = n * ((*ball2).velocity ^ (n));

  float k = (m1  / m2);
  float v1 = (*ball1).velocity ^ (r);
  float v2 = (*ball2).velocity ^ (r);

  float a = 1 + k;
  float b = -2 * v2 - 2 * k * v1;
  float c = (k - 1) * th_sqr(v1) + 2 * v1 * v2;

  if (th_sqr(b) - 4*a*c < 0)
    return;

  float v1_ = (-b + sqrt(th_sqr(b) - 4*a*c)) / (2 * a);
  float v2_ = k * (v1 - v1_) + v2;

  (*ball1).velocity = v1_n + (r * (v1_));
  (*ball2).velocity = v2_n + (r * (v2_));
}

float velocity(Ball ball)
{
  return ball.velocity.len();
}
