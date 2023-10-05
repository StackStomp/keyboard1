#include "blinky.h"

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "logger.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

static const struct gpio_dt_spec leds[] = {
	GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios),
	GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios),
	GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios),
	GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios)
};

int blinky_init() {
	int ret;

	for (int i = 0; i < 4; ++i) {
		if (!gpio_is_ready_dt(&(leds[i]))) {
            LOGE("led does not ready, index %d", i);
			return 1;
		}
		if (i == 0) {
			ret = gpio_pin_configure_dt(&(leds[i]), GPIO_OUTPUT_ACTIVE);
		} else {
			ret = gpio_pin_configure_dt(&(leds[i]), GPIO_OUTPUT_INACTIVE);
		}
		if (ret < 0) {
            LOGE("Failed to set init status for led %d", i);
			return 1;
		}
	}
    LOGD("Init blinky OK");
    return 0;
}

int blinky_next_run(int *index) {
    int ret;
    ret = gpio_pin_toggle_dt(&(leds[*index]));
    if (ret < 0) {
        LOGE("Failed to toggle led %d", *index);
        return 1;
    }
    *index = (*index + 1) % 4;
    ret = gpio_pin_toggle_dt(&(leds[*index]));
    if (ret < 0) {
        LOGE("Failed to toggle led %d", *index);
        return 1;
    }
    return 0;
}
