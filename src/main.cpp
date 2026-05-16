#include <stdio.h>
#include <zephyr/kernel.h>

#include "zephyr/drivers/gpio.h"

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

void thread1_dummy(void* dummy) {
  ARG_UNUSED(dummy);

  while (1) {
    k_msleep(1);
  }
}

K_THREAD_DEFINE(tid, 256, thread1_dummy, NULL, NULL, NULL, 5, 0, 0);

int main() {
  int ret;

  if (!gpio_is_ready_dt(&led) || !gpio_is_ready_dt(&button)) {
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0) return 0;

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  if (ret < 0) return 0;

  while (1) {
    int val = gpio_pin_get_dt(&button);

    if (val > 0) {
      gpio_pin_toggle_dt(&led);
      k_sleep(K_MSEC(100));
    } else {
      gpio_pin_toggle_dt(&led);
      k_sleep(K_MSEC(1000));
    }

    printk("LED STATE: %d\n", val);
  }

  return 0;
}