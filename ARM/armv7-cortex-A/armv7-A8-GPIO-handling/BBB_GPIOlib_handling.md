## BBB GPIOlib handling (armv7 A8 Sitara am33xx silicon used for Beagle Bone Black)

### GPIOchip & GPIO descriptions within sysfs directory (example: gpiochip32, gpio60)

	ls -al /sys/class/gpio/

	gpiochip0 -> ../../devices/platform/ocp/44c00000.interconnect/44c00000.interconnect:segment@200000/44e07000.target-module/44e07000.gpio/gpio/gpiochip0
	gpiochip32 -> ../../devices/platform/ocp/48000000.interconnect/48000000.interconnect:segment@0/4804c000.target-module/4804c000.gpio/gpio/gpiochip32
	gpiochip64 -> ../../devices/platform/ocp/48000000.interconnect/48000000.interconnect:segment@100000/481ac000.target-module/481ac000.gpio/gpio/gpiochip64
	gpiochip96 -> ../../devices/platform/ocp/48000000.interconnect/48000000.interconnect:segment@100000/481ae000.target-module/481ae000.gpio/gpio/gpiochip96

#### GPIOchip32 description

	debian@arm:/sys/class/gpio$ cd gpiochip32
	debian@arm:/sys/class/gpio/gpiochip32$ ls -al
	total 0
	drwxrwx--- 3 root gpio    0 Jan  1  2000 .
	drwxrwxr-x 3 root gpio    0 Jan  1  2000 ..
	-rwxrwx--- 1 root gpio 4096 Jan  1  2000 base // The starting GPIO number (32)
	lrwxrwxrwx 1 root gpio    0 Oct  8 17:12 device -> ../../../4804c000.gpio
	-rwxrwx--- 1 root gpio 4096 Jan  1  2000 label // A label to identify the chio (gpio-32-63)
	-rwxrwx--- 1 root gpio 4096 Jan  1  2000 ngpio // The number of GPIO pins (32)
	drwxrwx--- 2 root gpio    0 Jan  1  2000 power
	lrwxrwxrwx 1 root gpio    0 Oct  8 17:12 subsystem -> ../../../../../../../../../class/gpio
	-rwxrwx--- 1 root gpio 4096 Jan  1  2000 uevent

#### Handling GPIOs within GPIOchip

Each gpio pin on the BBB has three different numbering schemes associated with it!

	The physical pin location, in the form of PX_Y (P9_12)
	The gpio name, in the form of GPIOX_Y (GPIO1_28)
	The gpio number, in the form of 32*X + Y (60)

Expose the GPIO to userspace:

	debian@arm:/sys/class/gpio$ echo 60 > /sys/class/gpio/export
	debian@arm:/sys/class/gpio$ cd /sys/class/gpio/export/gpio60
	debian@arm:/sys/class/gpio/gpio60$ ls -al
	total 0
	drwxrwx---  3 root gpio    0 Jan  1  2000 .
	drwxrwx--- 22 root gpio    0 Jan  1  2000 ..
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 active_low // Set to 1 to invert values of input and output
	lrwxrwxrwx  1 root gpio    0 Oct  8 17:12 device -> ../../../gpiochip1
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 direction // Set direction by writing "out or "in". Default "in"
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 edge
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 label // P9_12 (BBB's P9 connector, 12th pin)
	drwxrwx---  2 root gpio    0 Jan  1  2000 power
	lrwxrwxrwx  1 root gpio    0 Oct  8 17:12 subsystem -> ../../../../../../../../../../class/gpio
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 uevent
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 value // The logic level of the pin. Change the level of outputs by writing 0 or 1.

##### Inputs and Outputs

Default values for gpio60:

	debian@arm:/sys/class/gpio/gpio60$ cat active_low
	0
	debian@arm:/sys/class/gpio/gpio60$ cat direction
	in
	debian@arm:/sys/class/gpio/gpio60$ cat value // "input" set to 1, weak internal (by default) pull-up resisdtor
	1
	debian@arm:/sys/class/gpio/gpio60$

Make it an output:

	debian@arm:/sys/class/gpio/gpio60$ echo out > /sys/class/gpio/gpio60/direction

And set it high:

	debian@arm:/sys/class/gpio/gpio60$ echo 1 > /sys/class/gpio/gpio60/value

Values for gpio60 after setup:

	debian@arm:/sys/class/gpio/gpio60$ cat active_low
	0
	debian@arm:/sys/class/gpio/gpio60$ cat direction
	out
	debian@arm:/sys/class/gpio/gpio60$ cat value
	1

Alltogether, generic:

	$ echo 60 > /sys/class/gpio/export
	$ echo out > /sys/class/gpio/gpio60/direction
	$ echo 1 > /sys/class/gpio/gpio60/value

Read the final setup from the /sys/class/gpio file system:

	$ cat > /sys/class/gpio/gpio60/active_low
	$ cat /sys/class/gpio/gpio60/direction
	$ cat /sys/class/gpio/gpio60/value

##### Interrupts

If the GPIO can generate the interrupt, the file edge can be used to control interrupt handling:

	debian@arm:/sys/class/gpio/gpio60$ ls -al
	total 0
	drwxrwx---  3 root gpio    0 Jan  1  2000 .
	drwxrwx--- 22 root gpio    0 Jan  1  2000 ..
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 active_low // Set to 1 to invert values of input and output
	lrwxrwxrwx  1 root gpio    0 Oct  8 17:12 device -> ../../../gpiochip1
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 direction // Set direction by writing "out or "in". Default "in"
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 edge // The file edge can be used to control interrupt handling
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 label // P9_12 (BBB's P9 connector, 12th pin)
	drwxrwx---  2 root gpio    0 Jan  1  2000 power
	lrwxrwxrwx  1 root gpio    0 Oct  8 17:12 subsystem -> ../../../../../../../../../../class/gpio
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 uevent
	-rwxrwx---  1 root gpio 4096 Jan  1  2000 value // The logic level of the pin. Change the level of outputs by writing 0 or 1.

Edge default value is [none]:

	-rwxrwx---  1 root gpio 4096 Jan  1  2000 edge // The file edge can be used to control interrupt handling

	debian@arm:/sys/class/gpio/gpio60$ cat edge
	none

Edge can take four vaues: edge = ["none", "rising", "falling", "both"].

For example, to make gpio60 interrupt on a falling edge:

	debian@arm:/sys/class/gpio/gpio60$ echo "falling" > /sys/class/gpio/gpio60/edge

To wait for an interrupt, use poll(2) function.
