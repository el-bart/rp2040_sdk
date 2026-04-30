#include <cinttypes>
#include <limits>
#include "hardware/pwm.h"
#include "hardware/gpio.h"

namespace rph
{

struct Servo final
{
  explicit Servo(int const pin):
    pin_{pin},
    slice_num_{ pwm_gpio_to_slice_num(pin_) },
    channel_{ (pin_%2)==0 ? PWM_CHAN_A : PWM_CHAN_B }
  {
    pwm_config cfg = pwm_get_default_config();

    // 125*10^6 / 2^16 / (38+2/16) ~= 50.03 Hz
    pwm_config_set_clkdiv_int_frac(&cfg, 38, 2); // div == 38 + 2/16

    pwm_config_set_output_polarity(&cfg, false, false); // invert both channels
    pwm_init(slice_num_, &cfg, false);
    gpio_set_function(pin_, GPIO_FUNC_PWM);

    Range constexpr r_;
    pwm_set_wrap(slice_num_, r_.max_);  // period

    pwm_set_enabled(slice_num_, true);

    pos(255/2);
  }

  ~Servo()
  {
    pwm_set_enabled(slice_num_, false);
  }

  Servo(Servo const&) = delete;
  Servo& operator=(Servo const&) = delete;
  Servo(Servo &&) = delete;
  Servo& operator=(Servo &&) = delete;

  void pos(uint8_t const p)
  {
    Range constexpr r_;
    auto const level = r_.servo_min_ + (r_.servo_range_ * p) / 256;
    pwm_set_chan_level(slice_num_, channel_, level);
  }

private:
  struct Range final
  {
    uint16_t const max_ = std::numeric_limits<uint16_t>::max();
    uint16_t const servo_min_ = max_ / 40u;
    uint16_t const servo_range_ = max_ / 20u + max_ / 30u;
    uint16_t const servo_max_ = servo_min_ + servo_range_;
    uint16_t const servo_center_ = (servo_min_ + servo_max_) / 2u;
  };

  int const pin_{};
  unsigned int const slice_num_{};
  unsigned int const channel_{};
};

}
