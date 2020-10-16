### Open Source general aproach how to access common GPIOs - libgpiod
https://www.kernel.org/doc/Documentation/gpio/consumer.txt

GPIO Descriptor Consumer Interface

This document describes the consumer interface of the GPIO framework. Note that it describes
the new descriptor-based interface. For a description of the deprecated integer-based GPIO
interface please refer to gpio-legacy.txt.

These calls use the gpiod_* naming prefix. No other calls should use that prefix, or the
related __gpiod_* prefix.

Please, also read the following document:
https://embeddedbits.org/new-linux-kernel-gpio-user-space-interface/

From kernel 4.8 the libgpiod driver and library are included in the kernel.

Current GPIO devchar version is v1.

#### Where to find libgpiod package and git - index : libgpiod/libgpiod.git
https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git/

Here are the net pointers from which to clone libgpiod repositories:

	git://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
	https://git.kernel.org/pub/scm/libs/libgpiod/libgpiod.git
	https://kernel.googlesource.com/pub/scm/libs/libgpiod/libgpiod.git

#### Debian apt get method (real Beagle Bone Black used with Debian Buster on it)

	debian@arm:~/libgpiod$ sudo apt install libgpiod-dev
	Reading package lists... Done
	Building dependency tree
	Reading state information... Done
	libgpiod-dev is already the newest version (1.4.1-2rcnee3~buster+20190906).
	0 upgraded, 0 newly installed, 0 to remove and 1 not upgraded.

	debian@arm:~/libgpiod$ sudo apt install libgpiod-doc
	Reading package lists... Done
	Building dependency tree
	Reading state information... Done
	libgpiod-doc is already the newest version (1.4.1-2rcnee3~buster+20190906).
	0 upgraded, 0 newly installed, 0 to remove and 1 not upgraded.

#### Examples (need to be adopted for the actual platform GPIO configuration)

The following examples are applicable for Beagle Bone Black (BBB):

	libgpio-state.c
	libgpio-event.c
	libgpio-lsgpio.c (with appropriate local libgpio-lsgpio.h)

#### Compilation/Linkage (on target platform - BBB with Debian Buster installed)

	$ gcc -lgpiod libgpio-state.c  -o libgpio-state
	$ gcc -lgpiod libgpio-event.c  -o libgpio-event
	$ gcc -lgpiod libgpio-lsgpio.c -o libgpio-lsgpio

#### Useful CLI libgpiod commands

If one wants to manage and interact with GPIO lines from a terminal, one can use the command-line
tools provided by libgpiod.

##### gpiodetect

The gpiodetect command will list all GPIO chips, their labels and the number of GPIO lines:

	debian@arm:~/libgpiod$ gpiodetect
	gpiochip0 [gpio-0-31] (32 lines)
	gpiochip1 [gpio-32-63] (32 lines)
	gpiochip2 [gpio-64-95] (32 lines)
	gpiochip3 [gpio-96-127] (32 lines)

##### gpioinfo <chip #>

The gpioinfo command will print information about GPIO lines of a specific GPIO controller (or all
GPIO controllers if none are specified):

	debian@arm:~/libgpiod$ gpioinfo 0
	gpiochip0 - 32 lines:
		line   0:  "MDIO_DATA"       unused   input  active-high
		line   1:   "MDIO_CLK"       unused   input  active-high
		line   2:  "SPI0_SCLK"      "P9_22"   input  active-high [used]
		line   3:    "SPI0_D0"      "P9_21"   input  active-high [used]
		line   4:    "SPI0_D1"      "P9_18"   input  active-high [used]
		line   5:   "SPI0_CS0"      "P9_17"   input  active-high [used]
		line   6:   "SPI0_CS1"         "cd"   input  active-low  [used]
		line   7: "ECAP0_IN_PWM0_OUT" "P9_42" input  active-high [used]
		line   8: "LCD_DATA12"      "P8_35"   input  active-high [used]
		line   9: "LCD_DATA13"      "P8_33"   input  active-high [used]
		line  10: "LCD_DATA14"      "P8_31"   input  active-high [used]
		line  11: "LCD_DATA15"      "P8_32"   input  active-high [used]
		line  12: "UART1_CTSN"      "P9_20"   input  active-high [used]
		line  13: "UART1_RTSN"      "P9_19"   input  active-high [used]
		line  14:  "UART1_RXD"      "P9_26"   input  active-high [used]
		line  15:  "UART1_TXD"      "P9_24"   input  active-high [used]
		line  16: "GMII1_TXD3"       unused   input  active-high
		line  17: "GMII1_TXD2"       unused   input  active-high
		line  18: "USB0_DRVVBUS"     unused   input  active-high
		line  19: "XDMA_EVENT_INTR0" "A15"    input  active-high [used]
		line  20: "XDMA_EVENT_INTR1" "P9_41"  input  active-high [used]
		line  21: "GMII1_TXD1"       unused   input  active-high
		line  22:   "GPMC_AD8"      "P8_19"   input  active-high [used]
		line  23:   "GPMC_AD9"      "P8_13"   input  active-high [used]
		line  24:         "NC"       unused   input  active-high
		line  25:         "NC"       unused   input  active-high
		line  26:  "GPMC_AD10"      "P8_14"   input  active-high [used]
		line  27:  "GPMC_AD11"      "P8_17"   input  active-high [used]
		line  28: "GMII1_TXD0"       unused   input  active-high
		line  29: "RMII1_REFCLK"     unused   input  active-high
		line  30: "GPMC_WAIT0"      "P9_11"   input  active-high [used]
		line  31:   "GPMC_WPN"      "P9_13"   input  active-high [used]

	debian@arm:~/libgpiod$ gpioinfo 1
	gpiochip1 - 32 lines:
		line   0:   "GPMC_AD0"      "P8_25"   input  active-high [used]
		line   1:   "GPMC_AD1"      "P8_24"   input  active-high [used]
		line   2:   "GPMC_AD2"      "P8_05"   input  active-high [used]
		line   3:   "GPMC_AD3"      "P8_06"   input  active-high [used]
		line   4:   "GPMC_AD4"      "P8_23"   input  active-high [used]
		line   5:   "GPMC_AD5"      "P8_22"   input  active-high [used]
		line   6:   "GPMC_AD6"      "P8_03"   input  active-high [used]
		line   7:   "GPMC_AD7"      "P8_04"   input  active-high [used]
		line   8: "UART0_CTSN"       unused   input  active-high
		line   9: "UART0_RTSN"       unused   input  active-high
		line  10:  "UART0_RXD"       unused   input  active-high
		line  11:  "UART0_TXD"       unused   input  active-high
		line  12:  "GPMC_AD12"      "P8_12"   input  active-high [used]
		line  13:  "GPMC_AD13"      "P8_11"   input  active-high [used]
		line  14:  "GPMC_AD14"      "P8_16"   input  active-high [used]
		line  15:  "GPMC_AD15"      "P8_15"   input  active-high [used]
		line  16:    "GPMC_A0"      "P9_15"   input  active-high [used]
		line  17:    "GPMC_A1"      "P9_23"   input  active-high [used]
		line  18:    "GPMC_A2"      "P9_14"   input  active-high [used]
		line  19:    "GPMC_A3"      "P9_16"   input  active-high [used]
		line  20:    "GPMC_A4"       unused   input  active-high
		line  21:    "GPMC_A5" "beaglebone:green:usr0" output active-high [used] <<== BBB user led 1
		line  22:    "GPMC_A6" "beaglebone:green:usr1" output active-high [used] <<== BBB user led 2
		line  23:    "GPMC_A7" "beaglebone:green:usr2" output active-high [used] <<== BBB user led 3
		line  24:    "GPMC_A8" "beaglebone:green:usr3" output active-high [used] <<== BBB user led 4
		line  25:    "GPMC_A9"       unused   input  active-high
		line  26:   "GPMC_A10"       unused   input  active-high
		line  27:   "GPMC_A11"       unused   input  active-high
		line  28:  "GPMC_BE1N"       unused   input  active-high
		line  29:  "GPMC_CSN0"      "P8_26"   input  active-high [used]
		line  30:  "GPMC_CSN1"      "P8_21"   input  active-high [used]
		line  31:  "GPMC_CSN2"      "P8_20"   input  active-high [used]

##### gpioget <chip #> <gpio line #>

The gpioget command will read the value of a GPIO line. For example, the following command will
read the GPIO line 28 of the gpio controller 1 (BBB GPIO 60):

	debian@arm:~/libgpiod$ gpioget 1 28
	1

##### gpioset <chip #> <gpio line #=value>

The gpioset command will set a GPIO line. For example, the following command will set the GPIO
line 28 of the gpio controller 1 (BBB GPIO 60):

	debian@arm:~/libgpiod$ sudo gpioset 1 28=1

##### gpiomon <chip #> <gpio line #=value>

The gpiomon command will wait for events on GPIO lines and print them to standard output:

	debian@arm:~/libgpiod$ sudo gpiomon 1 28
