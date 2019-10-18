#include <math.h>

struct Vector2f
{
  float x = 100;
  float y = 100;

  Vector2f operator* (float Const);
  
  Vector2f(float x, float y);

  Vector2f operator+ (Vector2f v1);

  float len();

  float operator^ (Vector2f v1);
  
};

Vector2f::Vector2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vector2f Vector2f::operator* (float Const)
{
  return Vector2f(this->x * Const, this->y * Const);
}

float th_sqr(float x)
{
  return x * x;
}

Vector2f Vector2f::operator+ (Vector2f v1)
{
  return Vector2f(this->x + v1.x, this->y + v1.y);
}



float Vector2f::len()
{
  return (sqrt(th_sqr(this->x) + th_sqr(this->y)));
}

float Vector2f::operator^ (Vector2f v1)
{
  return v1.x * this->x + v1.y * this->y;
}
