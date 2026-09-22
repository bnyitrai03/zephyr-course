#ifndef MY_LED_HPP
#define MY_LED_HPP

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int increase_counter(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif