#include <iostream>
#include "TXLib.h"
#include "uI.h"

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

void drawBall(int x, int y, int r, int red, int green, int blue);

void moveBall(float* x, float* y, float* vx, float* vy, float dt);

void wallHit(float* x, float* y, float* vx, float* vy, float r);

void slowDown(float* vx, float* vy);

void slowDownPlayer(float* vx, float* vy);

void controlBall(float* vx, float* vy, float dv);

void drawCircle(int x, int y, int level);

float th_sqr(float x);

void th_paste_b(Ball safe, Ball b_features[], float n);

void th_download(string name ,Ball* safe);

void th_paste_p(Ball safe, Ball* player);

bool gameOver(Ball player, int level, int caught, int n);

void catchTheBall(Ball player, Ball b_features[], int* caught, int n);
