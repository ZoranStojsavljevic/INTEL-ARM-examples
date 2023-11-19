#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

// Memory Mapped Files
// https://www.sao.ru/hq/sts/linux/doc/ipc_guide/mmap.html

int main(int argc, char *argv[])
{
	int fd;
	char *data;
	struct stat sbuf;

	if (argc != 1) {
		fprintf(stderr, "usage: mmapdemo \n");
		exit(1);
	}

	if (-1 == (fd = open("mmapdemo.c", O_RDONLY))) {
		perror("open file failed, fd = -1");
		exit(1);
	}

	if (-1 == stat("mmapdemo.c", &sbuf)) {
		perror("stat failed");
		printf("stat failed, &sbuf = %p\n", &sbuf);
		exit(1);
	}

	if ((caddr_t)(-1) == (data = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0))) {
		perror("mmap from fd to data copying failed");
		printf("mmap from fd to data copying failed, data = %p\n", data);
		exit(1);
	}

	if (-1 == close(fd)) {
		perror("close file failed");
		printf("close file failed, fd = %d\n", fd);
		exit(1);
	}

	for (int i=0; i < sbuf.st_size; i++)
		printf("%c", data[i]);

	if (-1 == munmap(data, sbuf.st_size)) {
		perror("munmap data failed");
		printf("munmap data failed, data = %p\n", data);
	}

	return 0;
}
