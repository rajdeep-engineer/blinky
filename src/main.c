/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT | GPIO_OPEN_DRAIN | GPIO_PULL_UP);
	if (ret < 0) {
		return;
	}
	
	gpio_pin_set_dt(&led, 1);	//led on
	k_msleep(SLEEP_TIME_MS);
	k_msleep(SLEEP_TIME_MS);
	k_msleep(SLEEP_TIME_MS);
	gpio_pin_set_dt(&led, 0);	//led off
	k_sleep(K_FOREVER);

	while (1) {
		//gpio_pin_toggle_dt(&led);
		k_msleep(SLEEP_TIME_MS);
	}
}
