/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

#include "blinky.h"
#include "logger.h"

#define SLEEP_TIME_MS   500

int main(void)
{
	if (blinky_init() != 0) {
		return 0;
	}

	int index = 0;
	while (1) {
		if (blinky_next_run(&index) != 0) {
			return 0;
		}
		LOGD("This turn %d\n", index);
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}
