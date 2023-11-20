#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Represents MAP_SHARED flag using a fork() system call
// https://stackoverflow.com/questions/19672778/trying-to-write-to-an-int-in-shared-memory-using-mmap-with-a-child-process

int main(void) {
	int * shared = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	pid_t child;
	int childstate;

	printf("mmap's *shared %d\n", *shared);

	if(0 == (child = fork())) {
		*shared = 1;
		printf("child's *shared %d\n", *shared);
		exit(0);
	}
	waitpid (child, &childstate, 0);
	printf("parent's *shared %d\n", *shared);

	if (-1 == munmap(shared, sizeof(int))) {
		perror("munmap shared failed");
		printf("munmap shared failed, shared = %p\n", shared);
	}
}
