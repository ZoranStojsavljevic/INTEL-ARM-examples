/*
 * Net pointer to: https://hardforum.com/threads/ecc-check-on-intel-i3-processors.1693051/
 * Must be run as root.
 * It outputs something like this:
 *
 * 5004-5007h: 20 0 62 0 <<== Please, do note Little Endian order
 * 5008-500Bh: 10 0 62 0 <<== Please, do note Little Endian order
 *
 * The interesting part is the first byte (from the right).
 * In the case of i5-4300U the 0 means that ECC is not enabled,
 ^ and this is normal/ecc not implemented.
 *
 * According to Intel's 4th-gen-core datasheet:
 * 0: ECC disabled.
 * 1: ECC is active in I/O; ECC logic is not active.
 * 2: ECC is disabled in I/O, but ECC logic is enabled.
 * 3: ECC active in both I/O and ECC logic.
 *
 * Does comply with Core 4 and 5 silicons
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MCHBAR		0xFED10000

/*
 * MCHBAR—Host Memory Mapped Register Range Base - Offset 48h
 *
 * 38:15 000000h - RW MCHBAR:
 *			This field corresponds to bits 38 to 15 of the
 *			base address Host Memory Mapped configuration
 *			space. BIOS will program this register resulting
 *			in a base address for a 32KB block of contiguous
 *			memory address space.
 */
#define FILESIZE	32*1024

int main(int argc, char *argv[]) {
	int i;
	int fd = -1;
	unsigned long pagesize;
	unsigned char *map;
	unsigned char *mem;

	fd = open("/dev/mem", O_RDONLY | O_SYNC);
	if (-1 == fd) {
		perror("Error opening /dev/mem for reading");
		exit(EXIT_FAILURE);
	}

	map = mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, MCHBAR);
	if (MAP_FAILED == map) {
		close(fd);
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}

	// Get RAM info
	printf("5004-5007h: ");
	for (i = 0x5004; i < 0x5004+4; i++)
		printf("%lx ", map[i]);
	printf("\n");

	printf("5008-500Bh: ");
	for (i = 0x5008; i < 0x5008+4; i++)
		printf("%lx ", map[i]);
	printf("\n");

	// Unmap the file
	if (-1 == munmap(map, FILESIZE))
		perror("Error un-mmapping the file");
	close(fd);

	return 0;
}
