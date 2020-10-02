/*
 * Must be run as root.
 * It outputs something like this:
 *
 * 5004-5007h: 20 0 0 0 <<== Please, do note Little Endian order
 * 5008-500Bh: 10 0 0 0 <<== Please, do note Little Endian order
 *
 * The interesting part is the second byte (from the left).
 *
 * According to Intel's 10th-gen-core datasheet:
 * 00h or 01h: ECC disabled.
 * 10h or 11h: ECC is active in I/O; ECC logic is not active.
 * 20h or 21h: ECC is disabled in I/O, but ECC logic is enabled.
 * 30h or 31h: ECC active in both I/O and ECC logic.
 *
 * Does apply for Core 6, 7 (32KB), 8, 9, 10 (64KB) silicons (does NOT apply up to Core 5)
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
 * ONLY CORE 10 Generation
 *
 * MCHBAR Base Address Register (MCHBAR_0_0_0_PCI) - Offset 48h
 *
 * 38:16 000000h - RW MCHBAR:
 *			This field corresponds to bits 38 to 16 of the
 *			base address Host Memory Mapped configuration
 *			space. BIOS will program this register resulting
 *			in a base address for a 64KB block of contiguous
 *			memory address space.
 */
// #define FILESIZE	64*1024 /* Because of a 64KB mapping, impossible to run on lower cores */

/*
 * CORE 4, 5, 6, 7, 8, 9, (supports 10 as well) Generations
 *
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
