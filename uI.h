#include <iostream>

void th_level()
{
  std::cout << " Choose your level '1-10'"<< std::endl;
}

float th_ball()
{
  float n = 0;
  do
  {
    std::cout << "How many Balls? '1-50'" << std::endl;
    std::cin >> n;
  }
  while ((n <= 0) or (n > 50));
  return n;
}

void th_ball_f()
{
  std::cout << "r, red, green, blue of the balls" << std::endl;
}

void th_player()
{
  std::cout << "r, red, green, blue of the PLAYER" << std::endl;
}

void th_again()
{
  std::cout << " play again? '1 - 0'" << std::endl;
}
