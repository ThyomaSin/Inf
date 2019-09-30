#include <iostream>

int th_level(void)
{
  int level = 1;
  std::cout << " Choose your level '1-10'"<< std::endl;
  std::cin >> level;
  return level;
}

int getNumber(void)
{
  int n = 0;
  std::cout << "How many Balls? " << std::endl;
  std::cin >> n;
  return n;
}
