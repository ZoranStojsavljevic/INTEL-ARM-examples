/*
 * Demonstrate using gpio-cdev i/f BBB gpiochip0 and lines' statuses
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>

#define DEV_GPIO  "/dev/gpiochip0"

int main(int argc, char *argv[])
{
	int fd;
	int ret;

	struct gpiochip_info		cinfo;
	struct gpioline_info		linfo;
	// struct gpiohandle_request	req;
	struct gpiohandle_data		data;

	/* open gpio */
	fd = open(DEV_GPIO, O_RDONLY);
	if (fd < 0) {
		printf("ERROR: open %s ret=%d\n", DEV_GPIO, fd);
		return -1;
	}

	/* get gpio chip info */
	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
	if (ret < 0) {
		printf("ERROR get chip info ret=%d\n", ret);
		close(fd);
		return -1;
	}
	printf("GPIO chip: %s, \"%s\", %u GPIO lines\n",
		cinfo.name, cinfo.label, cinfo.lines);

	memset(&linfo, 0, sizeof(linfo));

	for (int i=0; i < cinfo.lines; ++i) {
		linfo.line_offset = i;

		ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &linfo);
		if (ret < 0) {
			printf("ERROR get line info ret=%d\n", ret);
			close(fd);
			return -1;
		}
		printf("line %2d: %s\n", linfo.line_offset, linfo.name);
	}

	/* close gpio */
	close(fd);

	return 0;
}
