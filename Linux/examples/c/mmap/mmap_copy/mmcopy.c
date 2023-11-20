/*
 * mmcopy.c
 * Copy the contents of one file to another
 * file, using memory mappings.
 * Usage mmcopy <source-file> <dest-file>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int	fdSrc, fdDst;

	if (argc != 3) {
		fprintf(stderr, "%s source-file dest-file\n", argv[0]);
		exit(1);
	}

	if (-1 == (fdSrc = open(argv[1], O_RDONLY))) {
		perror("open file failed, src_fd = -1");
		exit(1);
	}

	// Use fstat() to obtain size of file: we use this
	// to specify the size of the two mappings
	struct stat sb;
	if (-1 == fstat(fdSrc, &sb)) {
		perror("fstat failed");
		printf("fstat failed, &sb = %p\n", &sb);
		exit(1);
	}

	// Handle zero-length file specially, since specifying a size
	// of zero to mmap() will fail with the error EINVAL
	if (0 == sb.st_size) {
		perror("sb.st_size is 0");
		printf("sb.st_size is %d\n", sb.st_size);
		exit(EXIT_SUCCESS);
	}

	char *src = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fdSrc, 0);
	if (MAP_FAILED == src) {
		perror("mmap from fdSrc to src copying failed");
		printf("mmap from fdSrc = %d to src = %p copying failed\n", fdSrc, src);
		exit(1);
	}

	if (-1 == (fdDst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR))) {
		perror("open file failed, fdDst = -1");
		exit(1);
	}

	if (-1 == ftruncate(fdDst, sb.st_size)) {
		perror("ftruncate failed, return is -1");
		exit(1);
	}

	char *dst = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdDst, 0);
	if (MAP_FAILED == dst) {
		perror("mmap from fdDst to dst failed");
		printf("mmap from fdDst = %d to dst = %p failed\n", fdDst, dst);
		exit(1);
	}

	// Copy bytes between mappings
	memcpy(dst, src, sb.st_size);

	if (-1 == msync(dst, sb.st_size, MS_SYNC))
		exit(1);

	if (-1 == munmap(src, sb.st_size))
		printf("munmap src failed, src = %p\n", src);

	if (-1 == munmap(dst, sb.st_size))
		printf("munmap dst failed, dst = %p\n", dst);

	if (-1 == close(fdSrc)) {
		perror("closing the fdSrc file failed");
		printf("closing the fdSrc file failed, fdSrc = %d\n", fdSrc);
		exit(1);
	}

	if (-1 == close(fdDst)) {
		perror("closing the fdDst file failed");
		printf("closing the fdDst file failed, fdDst = %d\n", fdDst);
		exit(1);
	}

	exit(EXIT_SUCCESS);
}
