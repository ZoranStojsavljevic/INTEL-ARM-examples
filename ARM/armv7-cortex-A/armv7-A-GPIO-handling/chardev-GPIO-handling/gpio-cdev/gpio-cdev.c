/*
 * Demonstrate using gpio-cdev i/f blinking BBB user LED
 ^
 * --- GPIO1_21 is user LED 1
 * --- GPIO1_22 is user LED 2
 * --- GPIO1_23 is user LED 3
 * --- GPIO1_24 is user LED 4
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

int main(int argc, char **argv)
{
	int				fd;
	int				ret;
	struct  gpiohandle_request	req;
	struct  gpiohandle_data		data;

	fd = open("/dev/gpiochip1", O_RDONLY);
	req.lineoffsets[0] = 24; // --- GPIO1_24 is user LED 4
	req.flags = GPIOHANDLE_REQUEST_OUTPUT; /* Request as output */
	req.default_values[0] = 0;
	strcpy(req.consumer_label, "gpio-output"); /* up to 31 characters */
	req.lines = 1;

	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

	while (1) { // Blinking BBB user LED
		/* Note that there is a new file descriptor in req.fd to handle the GPIO lines */
		data.values[0] = 1;
		ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		sleep(1); // 1s delay
		data.values[0] = 0;
		ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		sleep(1); // 1s delay
	}
	close(fd);

	return 0;
}
