#include <stdio.h>
#include <zephyr/kernel.h>

int main() {
  while (1) {
    k_msleep(1000);
  }

  return 0;
}