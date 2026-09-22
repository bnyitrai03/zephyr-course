if(CONFIG_MY_LED)
    target_sources(app PRIVATE my_led.c)
    zephyr_include_directories(../include)
endif()