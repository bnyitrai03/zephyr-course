#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "my_led.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    const struct device *led_sensor = DEVICE_DT_GET(DT_NODELABEL(my_led0));
    struct sensor_value val;

    if(!device_is_ready(led_sensor)){
        LOG_ERR("my_led sensor device not ready");
        return 0;
    }

    while(1){
        sensor_sample_fetch(led_sensor);
        LOG_INF("sample_fetch (LED on)");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        sensor_channel_get(led_sensor, SENSOR_CHAN_ALL, &val);
        LOG_INF("channel_get (LED off)");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        LOG_INF("dynamic data counter value: %d", increase_counter(led_sensor));
    }

    return 0;

}
