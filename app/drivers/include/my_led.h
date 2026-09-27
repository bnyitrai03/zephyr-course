#ifndef MY_LED_HPP
#define MY_LED_HPP

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int set_counter(const struct device *dev, int val);

#ifdef __cplusplus
}
#endif

#endif