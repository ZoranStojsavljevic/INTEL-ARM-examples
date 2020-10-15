/*
 * Demonstrate using gpio-cdev to output a single bit
 * on a BeagleBone Black, GPIO1_21 is user LED 1
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
	req.lineoffsets[0] = 21;
	req.flags = GPIOHANDLE_REQUEST_OUTPUT; /* Request as output */
	req.default_values[0] = 0;
	strcpy(req.consumer_label, "gpio-output"); /* up to 31 characters */
	req.lines = 1;

	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

	/* Note that there is a new file descriptor in req.fd to handle the GPIO lines */
	data.values[0] = 1;
	ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	close(fd);

	/*
	 * The GPIO settings die after the process setting them up dies.
	 * This is why here is while(1); - just for testing that GPIO
	 * states set within the process stay alive while process is up.
	 */
	// while(1);

	return 0;
}
