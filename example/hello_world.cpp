#include <iostream>
#include "pico/stdlib.h"

int main()
{
  stdio_init_all();

  auto const pin = 1;
  auto const delay = 2000;
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_OUT);

  for(uint32_t n = 0; true; ++n)
  {
    std::cout << "Hello, world #" << n << "!\n";

    gpio_put(pin, 1);
    sleep_ms(delay);
    gpio_put(pin, 0);
    sleep_ms(delay);
  }
}
