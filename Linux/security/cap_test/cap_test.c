#define _GNU_SOURCE

#include <sys/capability.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>

#define EXEC_FILE_1 "/usr/bin/id"
#define EXEC_FILE_2 "/usr/bin/ls"

#define PROG_NAME "cap_test"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

enum rv_id {
	NO_ERROR = 0,
	ERROR_GETRESUID,
	ERROR_GETRESGID,
	ERROR_CAP_SETUID,
	ERROR_CAP_SETGROUPS,
	ERROR_EXEC_FILE_2,
	ERROR_EXEC_FILE_1
};

static int print_ids()
{
	int	rv;
	gid_t	egid, rgid, sgid;
	uid_t	euid, ruid, suid;

	rv = getresuid(&ruid, &euid, &suid);
	if (0 != rv) {
		printf("Unable to get UIDs: %s\n", strerror(errno));
		return ERROR_GETRESUID;
	}
	printf("RUID: % 5d, EUID: % 5d, SUID: % 5d\n", ruid, euid, suid);

	rv = getresgid(&rgid, &egid, &sgid);
	if (0 != rv) {
		printf("Unable to get GIDs: %s\n", strerror(errno));
		return ERROR_GETRESGID;
	}
	printf("RGID: % 5d, EGID: % 5d, SGID: % 5d\n", rgid, egid, sgid);

	return NO_ERROR;
}

int main(int argc, char **argv)
{
	char	*name;
	int	rv;
	pid_t	pid;

	if (argc < 1) {
		name = PROG_NAME;
	} else {
		name = argv[0];
	}

	pid = getpid();
	printf("Pid of '%s' is %d\n", name, pid);

	rv = print_ids();
	if (0 != rv)
		return rv;

	printf("Setting UID to root user\n");
	rv = cap_setuid((uid_t)0);
	if (0 != rv) {
		printf("Unable to set UID to root user: %s\n", strerror(errno));
		return ERROR_CAP_SETUID;
	}
	printf("Setting GID to root group\n");
	rv = cap_setgroups((gid_t)0, 0, NULL);
	if (0 != rv) {
		printf("Unable to set GID to root group: %s\n", strerror(errno));
		return ERROR_CAP_SETGROUPS;
	}

	printf("Parent's RUID, EUID, SUID\n");
	rv = print_ids();
	if (0 != rv)
		return rv;

	const char *exec_file1 = EXEC_FILE_1;
	char *const exec_args1[] = { EXEC_FILE_1, NULL };
	printf("Parent executing process");
	for (size_t i = 0; NULL != exec_args1[i]; i++) {
		printf(" '%s'", exec_args1[i]);
	}
	printf("\n");

	// Create a child process
	pid_t cpid = fork();
	// This is the child process pid = 0
	if (0 == cpid) {
		const char *exec_file2 = EXEC_FILE_2;
		char *const exec_args2[] = { EXEC_FILE_2, NULL };

		printf("Child executing process");
		for (size_t i = 0; NULL != exec_args2[i]; i++) {
			printf(" '%s'", exec_args2[i]);
		}
		printf("\n");
		printf("Child's RUID, EUID, SUID\n");
		rv = print_ids();
		if (0 != rv)
			return rv;
		rv = execv(exec_file2, exec_args2);
		printf("Unable to execute process: '%s'\n", strerror(errno));
		return ERROR_EXEC_FILE_2;
	}
	printf("Parent's RUID, EUID, SUID\n");
	rv = print_ids();
	if (0 != rv)
		return rv;
	rv = execv(exec_file1, exec_args1);
	printf("Unable to execute process: '%s'\n", strerror(errno));
	return ERROR_EXEC_FILE_1;
}
