#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ioctl.h>

#define MMIO_ADDR 0xd0800000	// MMIO region start address (from kernel driver)
#define MMIO_SIZE 0x1000	// MMIO region size (4KB)

int main() {
	int		fd;
	unsigned char	*virtualAddress, *localAddress;
	void		*mmio_base;
	uint32_t	reg_val;

	// Open /dev/mem to access physical memory
	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if (-1 == fd) {
		perror("Failed to open /dev/mem");
		return -1;
	}

	// Memory-map the MMIO region
	virtualAddress = localAddress = mmap(NULL, MMIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, MMIO_ADDR);
	// if (MAP_FAILED == mmio_base) {
	if (MAP_FAILED == virtualAddress) {
		perror("Failed to mmap virtualAddress region");
		printf("MMIO_ADDR mapped at virtual address: %p\n", virtualAddress);
		close(fd);
		return -1;
	}

	printf("MMIO region mapped at virtual address: %p\n", mmio_base);

	// Read a 32-bit value from the MMIO region (e.g., the first register)
	reg_val = *((volatile uint32_t *)mmio_base);
	printf("Read value from MMIO register: 0x%x\n", reg_val);

	// Optionally, write to the MMIO region (e.g., writing a value)
	// *((volatile uint32_t *)mmio_base) = 0x12345678;
	// printf("Wrote value 0x12345678 to MMIO register\n");

	// Clean up
	if (-1 == munmap(mmio_base, MMIO_SIZE)) {
		perror("Failed to unmap MMIO region");
	}

	close(fd);

	return 0;
}
