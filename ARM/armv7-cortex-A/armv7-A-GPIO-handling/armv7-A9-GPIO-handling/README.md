## i.MX6 legacy GPIO handling
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

In this directory, there are a i.MX6 (armv7 A9) integer based GPIO interfaces (via
sysfs/) presented.

## Definitive (i.MX6 ==>> armv7 A9) GPIO guide
https://www.kosagi.com/w/index.php?title=Definitive_GPIO_guide

### Linux Userspace Naming Convention

Almost every pad has, as one of its 8 possible functions, a GPIO role.Linux uses a single integer
to enumerate all pads,  therefore Freescale's bank/bit notation for GPIOs must be mapped.

The bank/bit to Linux userspace formula is:

	linux gpio number = (gpio_bank - 1) * 32 + gpio_bit

So, GPIO1_IO17 maps to (1 - 1) * 32 + 17 = 17.

A more complex example is DISP0_DAT13. It maps to GPIO5_IO07, so its userspace number is
(5 - 1) * 32 + 7 = 135.

Thus, the algorithm to go from a schematic pin to a Linux userspace number is as follows:

Find the function on the schematic (e.g. PCIE_PWRON)

Trace it to the pad on a CPU. Note the canonical name (e.g. GPIO_17)
Look the canonical name up in table 28-4 of the reference manual to resolve the GPIO bit/bank
notation (e.g., GPIO_17 = GPIO7_IO12), or search for the pad name in the table on this page
(derived from the i.MX6Q Reference Manual Rev 1 4/2013).
Apply the translation formula: (7 - 1) * 32 + 12 = linux userspace gpio204

Note in the above example, the "pad name" GPIO_17 had *nothing* to do with the actual GPIO
bit/bank notation. So don't let the names fool you. Think of pad names as unique strings with
no inherent meaning, and your life will be easier.

### Linux Device Tree Naming Convention

There's another place where you might want to call out a GPIO: the device tree.

Novena's device tree entry would be found in arch/arm/boot/dts/imx6q-novena.dts.

When referring to a GPIO in a device tree node, you use the bit/bank mapping scheme. For example,
AUD_PWRON (schematic net name) maps to DISP0_DAT23 (i.MX6Q pad name). This maps to GPIO5_IO17 (per
lookup in table below), and therefore the device tree entry for this is:

	power-gpio = <&gpio5 17 0>

The third field is for gpio polarity (0 = active high, 1 = active low). In the context of an interrupt,
the third field specifies the polarity of the edge trigger, see: Documentation/devicetree/bindings/gpio/fsl-imx-gpio.txt

Sometimes you have to "hog" a pin in the device tree. To do that, look for the node iomuxc, in the
pinctrl_hog:hoggrp. Here, you have to use a series of names and numbers that you look up in the pin
control file.

Easiest way I've found is to start by searching the bank/bit name in the file "imx6q-pinfuc.h". Note
the format for the name is "GPIOn_IOmm" (I always forget the IO before the bit name).

Searching the canonical pad name is confusing because the pad name is re-used up to 8 times, and it
doesn't sufficiently disambiguate the function.

	MX6QDL_PAD_DISP0_DAT23__GPIO5_IO17 0x80000000

According to Documentation/devicetree/bindings/pinctrl/fsl,imx6q-pinctrl.txt that number to the right
of the hog spec can be used to set up things like pull-ups, pull-downs, keepers, drive strength, etc.
The value 0x80000000 is special and means "I don't know and don't change from the default". Otherwise,
it's set according to the following chart (basically the bitfields of the IOMUXC lower 17 bits):

	PAD_CTL_HYS		(1 << 16)
	PAD_CTL_PUS_100K_DOWN	(0 << 14)
	PAD_CTL_PUS_47K_UP	(1 << 14)
	PAD_CTL_PUS_100K_UP	(2 << 14)
	PAD_CTL_PUS_22K_UP	(3 << 14)
	PAD_CTL_PUE		(1 << 13)
	PAD_CTL_PKE		(1 << 12)
	PAD_CTL_ODE		(1 << 11)
	PAD_CTL_SPEED_LOW	(1 << 6)
	PAD_CTL_SPEED_MED	(2 << 6)
	PAD_CTL_SPEED_HIGH	(3 << 6)
	PAD_CTL_DSE_DISABLE	(0 << 3)
	PAD_CTL_DSE_240ohm	(1 << 3)
	PAD_CTL_DSE_120ohm	(2 << 3)
	PAD_CTL_DSE_80ohm	(3 << 3)
	PAD_CTL_DSE_60ohm	(4 << 3)
	PAD_CTL_DSE_48ohm	(5 << 3)
	PAD_CTL_DSE_40ohm	(6 << 3)
	PAD_CTL_DSE_34ohm	(7 << 3)
	PAD_CTL_SRE_FAST	(1 << 0)
	PAD_CTL_SRE_SLOW	(0 << 0)

Pro tip: don't use a value of 0, it doesn't work.

### Using Sysfsgpio on Linux

As an example, we'll use the controllable 5V power source.

The Device Tree lists it as gpio3,19:

	gpios = <&gpio3 19 GPIO_ACTIVE_HIGH>

To get the Linux GPIO number, use the formula above: (bank - 1 * 32) + pin:

	(3-1 * 32) + 19 = 83

Therefore, the 5v (fan)source is GPIO 83.

Expose the GPIO to userspace:

	echo 83 > /sys/class/gpio/export

Make it an output:

	echo out > /sys/class/gpio/gpio83/direction

And set it high:

	echo 1 > /sys/class/gpio/gpio83/value
