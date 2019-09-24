#include <iostream>

int th_level(void)
{
  int level = 1;
  std::cout << " Choose your level '1-10'"<< std::endl;
  std::cin >> level;
  return level;
}

float getNumber(void)
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
