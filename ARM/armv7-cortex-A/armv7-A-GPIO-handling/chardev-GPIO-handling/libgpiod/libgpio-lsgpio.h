#ifndef _LIBGPIO_LSGPIO_H_
#define _LIBGPIO_LSGPIO_H_

struct gpiod_line {
	unsigned int offset;

	/* The direction of the GPIO line. */
	int direction;

	/* The active-state configuration. */
	int active_state;

	/* The logical value last written to the line. */
	int output_value;

	/* The GPIOLINE_FLAGs returned by GPIO_GET_LINEINFO_IOCTL. */
	__u32 info_flags;

	/* The GPIOD_LINE_REQUEST_FLAGs provided to request the line. */
	__u32 req_flags;

	/*
	 * Indicator of LINE_FREE, LINE_REQUESTED_VALUES or
	 * LINE_REQUESTED_EVENTS.
	 */
	int state;

	struct gpiod_chip *chip;
	struct line_fd_handle *fd_handle;

	char name[32];
	char consumer[32];
};

struct gpiod_chip {
	struct gpiod_line **lines;
	unsigned int num_lines;

	int fd;

	char name[32];
	char label[32];
};

#endif /* _LIBGPIO_LSGPIO_H_ */
