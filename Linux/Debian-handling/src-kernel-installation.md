### Kernel source code installation
https://wiki.debian.org/BuildADebianKernelPackage

#### Headers installation

	$ sudo apt-get install linux-headers-`uname -r`

#### Source code installation

	$ sudo apt-get install build-essential linux-source bc kmod cpio flex libncurses5-dev xz-utils

	IMPORTANT: sudo apt-get install linux-source <<==== (and others, will need 'em)

If stalled, please, execute the next:

	$ sudo apt-get update --fix-missing
	$ sudo apt-get upgrade
	$ sudo systemctl daemon-reload

And repeat the command:

	$ sudo apt-get install build-essential linux-source bc kmod cpio flex libncurses5-dev xz-utils

Source code `uname -r` resides in /usr/src, a config to be taken from linux-headers-`uname -r`

Do not forget (at the end):

	$ sudo chown -R <user>:<usergroup> linux-source-xyz

#### Optional exercize (with some potential addtional work)

	$ sudo apt-get source linux-image-$(uname -r)

#### Additional literature
https://askubuntu.com/questions/1047017/do-i-need-to-apply-the-diff-that-came-with-my-ubuntu-kernel-source
