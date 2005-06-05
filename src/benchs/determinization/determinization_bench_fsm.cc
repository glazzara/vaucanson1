#include <iostream>
#include <cstdlib>

int main(int argc,  char** argv)
{
  unsigned n = atoi(argv[1]);

  for (unsigned i = 1; i < n; ++i)
    {
      std::cout << i - 1 << " " << i << " 1" << std::endl;
      std::cout << i << " " << i  << " 2" << std::endl;
      std::cout << i << " " << i  << " 3" << std::endl;
      std::cout << i << " " << 0  << " 2" << std::endl;
    }
  std::cout << n-1 << " " << 0 << " 1" << std::endl;
  std::cout << 0 << std::endl;
}
