#include <cinttypes>
#include <limits>
#include "hardware/adc.h"

namespace rph
{

struct ADC final
{
  enum class Port: int
  {
    ADC0,
    ADC1,
    ADC2,
    ADC3,
  };

  explicit ADC(Port const port):
    port_{port}
  {
    adc_init();
    adc_gpio_init( pinNo() );
  }

  ~ADC() = default;

  ADC(ADC const&) = delete;
  ADC& operator=(ADC const&) = delete;
  ADC(ADC &&) = delete;
  ADC& operator=(ADC &&) = delete;

  float read() const
  {
    adc_select_input( adcNo() );
    auto constexpr conv_fact = 3.3f / 4095.0f;  // 12-bit readouts
    auto const r = adc_read();
    auto const v = r * conv_fact;
    return v;
  }

private:
  int pinNo() const
  {
    switch(port_)
    {
      case Port::ADC0: return 26;
      case Port::ADC1: return 27;
      case Port::ADC2: return 28;
      case Port::ADC3: return 29;
    }
    assert(false);
    return 0;
  }

  int adcNo() const
  {
    switch(port_)
    {
      case Port::ADC0: return 0;
      case Port::ADC1: return 1;
      case Port::ADC2: return 2;
      case Port::ADC3: return 3;
    }
    assert(false);
    return 999;
  }

  Port const port_{Port::ADC0};
};

}
