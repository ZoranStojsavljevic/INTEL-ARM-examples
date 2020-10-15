### Open Source general aproach how to access common GPIOs - gpio-cdev

In this approach, user space processes are using directly kernel system calls to the GPIO
kernel driver, which is represented as set of char devices given by the set of the GPIO
controllers:

	debian@arm:~$ ls -al /dev/gpio*
	crw-rw---- 1 root gpio 254, 0 Oct 14 11:33 /dev/gpiochip0
	crw-rw---- 1 root gpio 254, 1 Oct 14 11:33 /dev/gpiochip1
	crw-rw---- 1 root gpio 254, 2 Oct 14 11:33 /dev/gpiochip2
	crw-rw---- 1 root gpio 254, 3 Oct 14 11:33 /dev/gpiochip3

Controllers are called chips, while individual GPIOs within controllers are called lines.

#### Examples presented

	gpio-cdev.c
	lsgpio.c

#### Compilation/Linkage (on target platform - BBB with Debian Buster installed)

	$ gcc gpio-cdev.c -o gpio-cdev
	$ gcc lsgpio.c -o lsgpio
