#include <iostream>
#include <SFML/Graphics.hpp>
#include "uI.h"
#include "Vector2f.h"


const float dt = 1;

struct Ball
{
  int r = 7;
  int red = 255;
  int green = 255;
  int blue = 0;
  Vector2f position = Vector2f(100, 100);
  Vector2f velocity = Vector2f(100, 100);

  Ball(Vector2f position, Vector2f velocity, int r, int red, int green, int blue);
  Ball();
  void draw(sf::RenderWindow* window);
  void wallHit();
  void move(float dt);
  void slowDown(float acc, float Vmin);
  bool checkCollision(Ball ball);
  void resolveCollision(Ball* ball);
  float Velocity();
};

Ball::Ball(Vector2f position, Vector2f velocity, int r, int red, int green, int blue)
{
  this -> position = position;
  this -> velocity = velocity;
  this -> r = r;
  this -> green = green;
  this -> red = red;
  this -> blue = blue;
}

Ball::Ball()
{
}
  
void Ball::draw(sf::RenderWindow* window)
{
  sf::CircleShape circle(this -> r);
  circle.setPosition(this -> position.x - this -> r, this -> position.y - this -> r);
  
  for(int i = this -> r; i > 1; i--)
  {
    int red_i = this -> red - this -> red * i / this -> r;
    int green_i = this -> green - this -> green * i / this -> r;
    int blue_i = this -> blue - this -> blue * i / this -> r;
    
    circle.setFillColor(sf::Color(red_i, green_i, blue_i));
    (*window).draw(circle);
    circle.setRadius(i);
    
    float cx = this -> position.x - i + (this -> r - i) / 2;
    float cy = this -> position.y - i + (this -> r - i) / 2.3;
    circle.setPosition(cx, cy);   
  }
}

void Ball::wallHit()
{
  if (this -> position.y > 600 - this -> r)
  {
    this -> position.y = 600 - this -> r;
    this -> velocity.y = -(this -> velocity.y);
  }
  if (this -> position.y < this -> r)
  {
    this -> position.y = this -> r;
    this -> velocity.y = -(this -> velocity.y);
  }
  if (this -> position.x > 1000 - this -> r)
  {
    this -> position.x = 1000 - this -> r;
    this -> velocity.x = -this -> velocity.x;
  }
  if (this -> position.x < this -> r)
  {
    this -> position.x = this -> r;
    this -> velocity.x = -this -> velocity.x;
  }

}

void Ball::move(float dt)
{
  this -> position = this -> position + this -> velocity;
}

void Ball::slowDown(float acc, float Vmin)
{
  if (this -> Velocity() > Vmin)
    this -> velocity = (this -> velocity) * (acc);
}


void controlBall(Ball* ball, float dv)
{
  

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    (*ball).velocity.x -= dv;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    (*ball).velocity.y -= dv;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    (*ball).velocity.x += dv;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    (*ball).velocity.y += dv;
}


bool Ball::checkCollision(Ball ball)
{
  return ((this -> position + (ball.position) * (-1)).len() < this -> r + ball.r);
}

void Ball::resolveCollision(Ball* ball)
{
  float ro = 1;
  Vector2f r = this -> position + (((*ball).position) * (-1));
  Vector2f v = this -> velocity + (((*ball).velocity) * (-1));
  if ((r ^ v) > 0)
    return;

  r = r * (1/ r.len());

  Vector2f n = Vector2f(-r.y, r.x);

  float m1 = (4*3,14/3) * (this -> r) * th_sqr(this -> r) * ro;
  float m2 = (4*3,14/3) * (*ball).r * th_sqr((*ball).r) * ro;

  Vector2f v1_n = n * ((this -> velocity) ^ (n));
  Vector2f v2_n = n * ((*ball).velocity ^ (n));

  float k = (m1  / m2);
  float v1 = (this -> velocity) ^ (r);
  float v2 = (*ball).velocity ^ (r);

  float a = 1 + k;
  float b = -2 * v2 - 2 * k * v1;
  float c = (k - 1) * th_sqr(v1) + 2 * v1 * v2;

  if (th_sqr(b) - 4*a*c < 0)
    return;

  float v1_ = (-b + sqrt(th_sqr(b) - 4*a*c)) / (2 * a);
  float v2_ = k * (v1 - v1_) + v2;

  this -> velocity = v1_n + (r * (v1_));
  (*ball).velocity = v2_n + (r * (v2_));
}

float Ball::Velocity()
{
  return (this -> velocity.len());
}
