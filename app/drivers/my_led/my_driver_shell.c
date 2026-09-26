#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

static int sensor_sample_fetch_handler(const struct shell* sh, int argc, char** argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *my_led = shell_device_get_binding("my_led0");
    if (!my_led){
        shell_error(sh, "Couldn't find my_led0");
        return -EFAULT;
    }

    int ret = sensor_sample_fetch(my_led);
    if (ret != 0){
        shell_error(sh, "Sample fetch failed");
        return ret;
    }

    shell_info(sh, "LED on");
    return 0;
}

static int sensor_channel_get_handler(const struct shell* sh, int argc, char** argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *my_led = shell_device_get_binding("my_led0");
    if (!my_led){
        shell_error(sh, "Couldn't find my_led0");
        return -EFAULT;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(my_led, SENSOR_CHAN_ALL, &val);
    if (ret != 0){
        shell_error(sh, "Channel get failed");
        return ret;
    }

    shell_info(sh, "LED off");
    return 0;
}

static int sensor_info_handler(const struct shell* sh, int argc, char** argv){
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    const struct device *my_led = shell_device_get_binding("my_led0");
    if (!my_led){
        shell_error(sh, "Couldn't find my_led0");
        return -EFAULT;
    }

    shell_print(sh, "Device name: %s", my_led->name);
    shell_print(sh, "Device state: %d", device_is_ready(my_led));
    
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_cmds,
    [0] = SHELL_CMD_ARG(fetch, NULL, "Turn on LED", sensor_sample_fetch_handler, 1, 0),
    [1] = SHELL_CMD_ARG(read, NULL, "Turn off LED", sensor_channel_get_handler, 1, 0),
    [2] = SHELL_CMD_ARG(info, NULL, "Get sensor info", sensor_info_handler, 1, 0),
    [3] = SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &sensor_cmds, "Sensor commands", NULL);