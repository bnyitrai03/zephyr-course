#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include "my_led.h"

#define DT_DRV_COMPAT my_led
LOG_MODULE_REGISTER(my_led, LOG_LEVEL_INF);

struct my_led_sensor_config {
    struct gpio_dt_spec led;
};

struct my_led_sensor_data{
    int counter;
};

int increase_counter(const struct device *dev){
    struct my_led_sensor_data *data = dev->data;
    data->counter++;
    return data->counter;
}

// LED on
static int my_led_sensor_sample_fetch(const struct device *dev, enum sensor_channel chan){
    const struct my_led_sensor_config *cfg = dev->config;
    int ret;

    ret = gpio_pin_set_dt(&cfg->led, 1);
    return ret;
}

// LED off
static int my_led_sensor_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val){
    const struct my_led_sensor_config *cfg = dev->config;
    int ret;

    ret = gpio_pin_set_dt(&cfg->led, 0);
    return ret;
}

static int init(const struct device* dev){
    const struct my_led_sensor_config *cfg = dev->config;
    int ret;

    if(!gpio_is_ready_dt(&cfg->led)) {
        LOG_ERR("LED GPIO device not ready");
        return -1;
    }

    ret = gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED GPIO (%d)", ret);
        return ret;
    }

    LOG_INF("My LED Sensor is initialized!");
    return ret;
}

static DEVICE_API(sensor, api_iomico_lecture) = {
    .sample_fetch = my_led_sensor_sample_fetch,
    .channel_get = my_led_sensor_channel_get,
};

#define MY_LED_DEFINE(inst)                                                    \
    static const struct my_led_sensor_config my_led_cfg_##inst = {             \
        .led = GPIO_DT_SPEC_GET(DT_INST_PHANDLE(inst, led), gpios),            \
    };                                                                         \
    static struct my_led_sensor_data my_led_sensor_data_##inst = {             \
        .counter = 0                                                           \
    };                                                                         \
    DEVICE_DT_INST_DEFINE(inst, init, NULL, &my_led_sensor_data_##inst,        \
                          &my_led_cfg_##inst, POST_KERNEL,                     \
                          CONFIG_SENSOR_INIT_PRIORITY, &api_iomico_lecture);

DT_INST_FOREACH_STATUS_OKAY(MY_LED_DEFINE);
