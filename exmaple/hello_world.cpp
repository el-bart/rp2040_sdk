#include <iostream>
#include "pico/stdlib.h"

int main()
{
  stdio_init_all();
  for(uint32_t n = 0; true; ++n)
  {
    std::cout << "Hello, world #" << n << "!\n";
    sleep_ms(1000);
  }
}
