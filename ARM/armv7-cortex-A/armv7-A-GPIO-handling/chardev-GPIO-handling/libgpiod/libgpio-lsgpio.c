#include <stdio.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <gpiod.h>

#include "libgpio-lsgpio.h"

int main() {
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int req, value;

	chip = gpiod_chip_open("/dev/gpiochip0");
	if (!chip)
		return -1;

	printf("GPIO chip: %s, \"%s\", %u GPIO lines\n",
		chip->name, chip->label, chip->num_lines);

	for (int i=0; i < chip->num_lines; ++i) {
		line = gpiod_chip_get_line(chip, i);
		if (!line) {
			gpiod_chip_close(chip);
			return -1;
		}

		printf("line %2d: %s\n", line->offset, line->name);
	}

	gpiod_chip_close(chip);

	return 0;
}
