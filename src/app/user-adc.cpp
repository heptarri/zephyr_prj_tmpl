#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>

static const struct adc_dt_spec channel =
    ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0);

void user_adc_entry() {
  int ret;
  int16_t buf;
  int32_t val_mv;

  if (!adc_is_ready_dt(&channel)) return;

  ret = adc_channel_setup_dt(&channel);
  if (ret < 0) return;

  struct adc_sequence sequence = {
      .buffer = &buf,
      .buffer_size = sizeof(buf),
  };

  ret = adc_sequence_init_dt(&channel, &sequence);
  if (ret < 0) return;

  while (1) {
    adc_read_dt(&channel, &sequence);
    val_mv = buf;

    adc_raw_to_millivolts_dt(&channel, &val_mv);

    printk("ADC Raw val: %d; Voltage: %d mV.\n", buf, val_mv);

    k_sleep(K_SECONDS(1));
  }
}

K_THREAD_DEFINE(tid_adc, 1024, user_adc_entry, NULL, NULL, NULL, 7, 0, 0);