#include <stdio.h>
#include <zephyr/kernel.h>

#include "zephyr/drivers/gpio.h"
#include "zephyr/drivers/pwm.h"

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0),
// gpios);
static const struct pwm_dt_spec led = PWM_DT_SPEC_GET(DT_ALIAS(led0));
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int main() {
  int ret;

  if (!pwm_is_ready_dt(&led) || !gpio_is_ready_dt(&button)) {
    return 0;
  }

  uint32_t pulse = 0;
  uint32_t period = led.period;
  int step = 200000;

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  if (ret < 0) return 0;

  while (1) {
    int val = gpio_pin_get_dt(&button);
    // gpio_pin_toggle_dt(&led);

    pwm_set_pulse_dt(&led, pulse);
    pulse += step;

    if (pulse >= period)
      pulse = period, step = -step;
    else if (pulse <= 0)
      pulse = 0, step = -step;

    k_msleep(10);

    printk("LED STATE: %d\n", val);
  }

  return 0;
}