### MEMMAP script

#### Short description

This script exploits /sys kernel drivers database directory, namely /sys/firmware/memmap .

	Please, follow the following set of commands (from my PC based on Core i5-4300U):

	$ cd /sys/firmware/memmap
	$ ls -al

	total 0
	drwxr-xr-x. 15 root root 0 Sep 30 13:27 .
	drwxr-xr-x.  6 root root 0 Sep 21 08:22 ..
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 0
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 1
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 10
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 11
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 12
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 2
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 3
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 4
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 5
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 6
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 7
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 8
	drwxr-xr-x.  2 root root 0 Sep 30 15:32 9

Please, continue exploring deeper in order to get a full picture.

The script gives the coarse granularity of the physical memory map/layout for the DDRAM used:

#### Usage

	$ ./memmap.sh | sort

	0000000000000000-0000000000058000 (System RAM)
	0000000000058000-0000000000059000 (Reserved)
	0000000000059000-000000000009d000 (System RAM)
	000000000009d000-00000000000a0000 (Reserved)
	0000000000100000-00000000aab7f000 (System RAM)
	00000000aab7f000-00000000abe7f000 (Reserved)
	00000000abe7f000-00000000abf7f000 (ACPI Non-volatile Storage)
	00000000abf7f000-00000000abfff000 (ACPI Tables)
	00000000abfff000-00000000ac000000 (System RAM)
	00000000e00f8000-00000000e00f9000 (Reserved)
	00000000fed1c000-00000000fed20000 (Reserved)
	00000000ffdb0000-00000000ffdcf000 (Reserved)
	0000000100000000-000000034ee00000 (System RAM)
