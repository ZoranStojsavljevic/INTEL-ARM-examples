// https://www.oreilly.com/library/view/secure-programming-cookbook/0596003943/ch01s03.html
// https://stackoverflow.com/questions/9297415/correct-way-to-run-setuid-programs-in-c
// https://superuser.com/questions/1696909/what-is-the-meaning-of-using-euidif-ruid-and-euid-of-a-process-is-1000-0-and-i

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int status;
	int euid=geteuid();

	printf("Euid : geteuid() : %d\n", euid);

	int uid=getuid();
	printf(" uid : getuid()  : %d\n", uid);

	int egid=getegid();
	printf("Egid : getegid() : %d\n", egid);

	int gid=getgid();
	printf(" gid : getgid()  : %d\n", gid);

	int fd = open("/dev/sda", O_RDONLY);
	if (fd < 0) {
		printf("File open error %d\n", errno);
		exit (errno);
	}

	printf("File opened\n");

	/*  Drop superuser privileges in correct order */

	status = setgid(getgid());
	if (status < 0) {
		/* handle error condition */
		exit (status);
	}

	status = setuid(getuid());
	if (status < 0) {
		/* handle error condition */
		exit (status);
	}

	/*
	 * Not possible to regain group privileges due to
	 * correct relinquishment order
	 */

	euid=geteuid();
	printf("Euid : geteuid() : %d\n", euid);

	egid=getegid();
	printf("Egid : getegid() : %d\n", egid);

	char buff[512];

	int r = read(fd, buff, sizeof(buff));

	if(r > 0)
		printf("File read %d bytes\n", r);
	else
		printf("File read error %d\n", errno);

	if (fd >= 0) close(fd);

	return 0;
}

//	gcc -Wall setuid.c -o ./setuid
//	sudo chown root:users setuid
//	sudo chmod ug+s ./setuid
//	./setuid.c
