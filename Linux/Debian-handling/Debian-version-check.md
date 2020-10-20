### Check what Debian version exists on the Linux system (for all architectures)

The examples reflect armv7 A8 TI am33xx Sitara platform with Debian 10 installed.
These command are generic for other aarchitectures as well (x86, x86_64).

The easiest way on how to check what Debian version is to simply read a content
of /etc/issue file. Example:

	$ cat /etc/issue

Example (BeagleBone Black):

	debian@arm:~$ cat /etc/issue
	Debian GNU/Linux 10 \n \l

	default username:password is [debian:temppwd]

However, the above command may not show the current Debian update point releases.
Thus the more accurate info could be obtained with the following linux command:

	$ cat /etc/debian_version

Example (BeagleBone Black):

	debian@arm:~$ cat /etc/debian_version
	10.4

Check for /etc/os-release release file:

	$ cat /etc/os-release

Example (BeagleBone Black):

	debian@arm:~$ cat /etc/os-release
	PRETTY_NAME="Debian GNU/Linux 10 (buster)"
	NAME="Debian GNU/Linux"
	VERSION_ID="10"
	VERSION="10 (buster)"
	VERSION_CODENAME=buster
	ID=debian
	HOME_URL="https://www.debian.org/"
	SUPPORT_URL="https://www.debian.org/support"
	BUG_REPORT_URL="https://bugs.debian.org/"

An alternative way is by use of lsb_release command. This command may be missing
by default so it may need to be installed first:

	$ sudo apt-get install lsb-release

After the installation, the following linux command should be issued to find which
debian version is ran on the debian box:

	$ lsb_release -da

Example (BeagleBone Black):

	debian@arm:~$ lsb_release -da
	No LSB modules are available.
	Distributor ID:	Debian
	Description:	Debian GNU/Linux 10 (buster)
	Release:	10
	Codename:	buster

For systemd debian version hostnamectl might be issued:

	$ hostnamectl

Example	(BeagleBone Black):

	debian@arm:~$ hostnamectl
	   Static hostname: arm
	         Icon name: computer
	        Machine ID: 99b6faeb72761b3aaab187eb5e4184a6
	           Boot ID: 4fc3043b3ada446c9d2d6835977c9c7d
	  Operating System: Debian GNU/Linux 10 (buster)
	            Kernel: Linux 5.7.4-bone10
	      Architecture: arm
