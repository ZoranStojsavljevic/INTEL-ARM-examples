## BBB legacy GPIO handling
https://www.kernel.org/doc/Documentation/gpio/gpio-legacy.txt

### GPIO Interfaces

This provides an overview of GPIO access conventions on Linux. This document represents
description of the already deprecated global integer-based GPIO number space.

These calls use the gpio_* naming prefix. No other calls should use that prefix, or the
related __gpio_* prefix.

Simple wrappers manipulating legacy file descriptors:

	int gpio_open(int number, int out); /* returns handle (fd) */
	int gpio_close(int gpio);
	int gpio_set(int gpio, int up);
	int gpio_get(int gpio, int *up);
	int gpio_poll(int gpio, int rising_edge, int timeout);

In this directory, there are a Beagle Bone Black's (am33xx sitara TI silicon, armv7 A8 -
OMAP2) integer based GPIO interfaces (via sysfs/) presented.

### Working with GPIOs (C/C++)
https://www.unwireddevices.com/wiki/index.php/Working_with_GPIOs_(C/C%2B%2B)
