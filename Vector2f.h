struct Vector2f
{
  float x = 100;
  float y = 100;
};

float th_sqr(float x)
{
  return x * x;
}

Vector2f add(Vector2f v1, Vector2f v2)
{
  Vector2f v;
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
  return v;
}

Vector2f mul(Vector2f v1, float Const)
{
  Vector2f v;
  v.x = v1.x * Const;
  v.y = v1.y * Const;
  return v;
}

float len(Vector2f v)
{
  return (sqrt(th_sqr(v.x) + th_sqr(v.y)));
}

float scMul(Vector2f v1, Vector2f v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
