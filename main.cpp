//========================================================================
//! @file       Main.cpp
//{=======================================================================
//!
//! @brief      <Заголовок>\n
//! @brief      <Подзаголовок>
//!
//! @version    [Version 0.01 alpha, build 1]
//! @author     Copyright (C) <Автор>, <Год> (<Имя> <Почта>)
//! @date       <Дата>
//!
//! @par        Протестировано
//!           - (TODO: список платформ)
//!
//! @todo     - (TODO: список ближайших планов по этому файлу)
//!
//! @bug      - (TODO: список найденных ошибок в этом файле)
//!
//! @par        История изменений файла
//!           - Версия 0.01 Alpha
//!             - Только что созданный файл
//!
//}=======================================================================

#include "balls.h"
#include <iostream>

int main()
{
  float dv = 0.3;

  txCreateWindow(1000,600);

  int level = 1;
  level = th_level();

  drawCircle(500,300,level);

  float n = getNumber();

  Ball b_features[50], player;

  for(int i = 0; i < n; i++)
  {
    b_features[i].vx = (n / 2 - i + 0.3) * 0.7 +0.3;
    b_features[i].vy = th_sqr(i - n / 2) * 0.1 + 10;
  }

  player.r = 20;
  player.green = 0;
  player.x = 200;
  player.y = 200;

  for (int i = 0; i < 30; i++)
    std::cout << std::endl;

  int caught = 0;
  while (true)
  {
    drawCircle(500,300,level);
    for (int i = 0; i < n; i++)
    {
      drawBall(b_features[i]);
      moveBall(&b_features[i], dt);
      wallHit(&b_features[i]);
      slowDown(&b_features[i]);
    }
    drawBall(player);
    moveBall(&player, dt);
    absoluteSlowDown(&player);

    controlBall(&player, dv);

    for (int i = 0; i < n; i++)
      if (checkCollision(player, b_features[i]))
        resolveCollision(player, &b_features[i], &caught);

    if (gameOver(player, level, caught, n))
      break;

    txSleep(4);

    txClear();
  }
  if (caught != n)
    std::cout << "YOU LOOSE!";
  else
    std::cout << "YOU WON!";

  return 0;
}

