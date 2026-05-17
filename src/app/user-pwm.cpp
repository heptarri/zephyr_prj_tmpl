#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

static const struct pwm_dt_spec led = PWM_DT_SPEC_GET(DT_ALIAS(led0));

void user_pwm_entry() {
  if (!pwm_is_ready_dt(&led)) return;

  uint32_t pulse = 0;
  uint32_t period = led.period;
  uint32_t step = 200000;

  while (1) {
    pwm_set_pulse_dt(&led, pulse);
    pulse += step;

    if (pulse >= period)
      pulse = period, step = -step;
    else if (pulse <= 0)
      pulse = 0, step = -step;

    k_sleep(K_MSEC(10));
  }
}

K_THREAD_DEFINE(tid_pwm, 1024, user_pwm_entry, NULL, NULL, NULL, 7, 0, 0);