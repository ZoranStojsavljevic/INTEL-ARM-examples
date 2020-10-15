## Linux GPIO: Evolution and Current State of the User API - Bartosz Golaszewski, BayLibre
https://www.youtube.com/watch?v=0APvuY2eLkY

https://static.sched.com/hosted_files/lvc20/c2/LVC20_%20gpio%20and%20pinctrl%20BoF.pdf

### GPIO Aggregator
https://www.kernel.org/doc/html/latest/admin-guide/gpio/gpio-aggregator.html

Added very recently (06/2020): it's in 5.8.x+ (5.7.x is eol).

#### GPIO aggregator features

	● Access control for GPIO character devices is provided using unix persmissions
	● All or nothing - either all lines are accessible to user or none are
	● Sometimes it’s necessary to grant users access to certain GPIO lines
	● “Aggregate” them via a virtual GPIO chip device

#### GPIO aggregator example

	$ cd /sys/bus/platform/drivers/gpio-aggregator
	$ lsbind delete_device module new_device uevent unbind
	$ gpiodetect
	gpiochip0 [gpio-mockup-A] (4 lines)
	gpiochip1 [gpio-mockup-B] (4 lines)
	$ echo "gpio-mockup-A 0,2 gpio-mockup-B 1" > new_device
	$ ls
	bind delete_device gpio-aggregator.2 module new_device uevent unbind
	$ gpiodetect
	gpiochip0 [gpio-mockup-A] (4 lines)
	gpiochip1 [gpio-mockup-B] (4 lines)
	gpiochip2 [gpio-aggregator.2] (3 lines)
	$ gpioinfo gpiochip0
	gpiochip0 - 4 lines:
		line	0:	unnamed "gpio-aggregator.2" input active-high [used]
		line	1:	unnamed       unused   input  active-high
		line	2:	unnamed "gpio-aggregator.2" input active-high [used]
		line	3:	unnamed       unused   input  active-high
	$

#### Enable GPIO-Aggregator in kernel
https://github.com/torvalds/linux/blob/master/drivers/gpio/Kconfig

	config GPIO_AGGREGATOR
		tristate "GPIO Aggregator"
		help
		  Say yes here to enable the GPIO Aggregator, which provides a way to
		  aggregate existing GPIO lines into a new virtual GPIO chip.
		  This can serve the following purposes:
		    - Assign permissions for a collection of GPIO lines to a user,
		    - Export a collection of GPIO lines to a virtual machine,
		    - Provide a generic driver for a GPIO-operated device in an
		      industrial control context, to be operated from userspace using
		      the GPIO chardev interface.

### GPIO chardev v2

Current GPIO devchar version is v1.

GPIO chardev v2 - current status

	● New uAPI proposed on linux-gpio
	● Don’t break user-space - v1 ABI must remain stable
	● Fix 64-bit kernel to 32-bit user-space issues
	● Add padding to structures
	● Rework flags
	● Merge linehandle and lineevent requests

#### gpio cdev uAPI v2

	●[PATCH v9 00/20] gpio: cdev: add uAPI v2 by Kent Gibson (September 22, 2020)
	https://lore.kernel.org/linux-gpio/20200922023151.387447-1-warthog618@gmail.com/

		“This patchset defines and implements a new version of the GPIO CDEV uAPI to address
		existing 32/64-bit alignment issues, add suppor t for debounce, event sequence numbers,
		and allow for requested lines with different configurations.

		It provides some future proofing by adding optional configuration fields and padding
		reserved for future use.

		The series can be partitioned into three blocks; the first two patches are minor fixes
		that impact later patches, the next eleven contain the v2 uAPI definition and
		implementation, and the final seven port the GPIO tools to the v2 uAPI and extend them
		to use new uAPI features.”
