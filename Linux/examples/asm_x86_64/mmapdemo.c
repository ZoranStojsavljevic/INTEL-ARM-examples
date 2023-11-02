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

	if ((fd = open("mmapdemo.c", O_RDONLY)) == -1) {
		perror("open");
		exit(1);
	}

	if (stat("mmapdemo.c", &sbuf) == -1) {
		perror("stat");
		exit(1);
	}

	if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
		perror("mmap");
		exit(1);
	}

	for (int i=0; i < sbuf.st_size; i++)
		printf("%c", data[i]);

	return 0;
}
