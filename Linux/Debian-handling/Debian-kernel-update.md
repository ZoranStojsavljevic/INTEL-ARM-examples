### Tutorial on Updating Debian Kernel (for x86_64 architectures ONLY)
https://phoenixnap.com/kb/how-to-update-kernel-ubuntu

Option to use the System Update Process

#### Step 1: Check Current Kernel Version

At a terminal window issue the following:

	$ uname –sr

A terminal should respond with something like:

	Linux 5.4.0-64 generic (or similar)

The first two digits (in this case, 4.4) are the overall kernel package. The third digit is the version,
and the fourth digit shows the level of patches and fixes.

#### Step 2: Update the Repositories

At a terminal window issue the following:

	$ sudo apt-get update

This command refreshes the local list of software, making a note of any newer revisions and updates. If
there’s a newer version of the kernel, this will find it and mark it for download and installation.

#### Step 3: Run the upgrade

While still in the terminal, issue the following:

	$ sudo apt-get dist-upgrade

Using the “dist-upgrade” switch will ask Ubuntu to handle any dependencies intelligently. That is, if
one particular software package is dependent another software package to run, this command will make
sure that the second package is upgraded before upgrading the first one.

This is a safe way to upgrade the Debian/Ubuntu Linux kernel. All of the kernel updates accessible
through this utility have been tested and verified to work with any newer version of Debian/Ubuntu.
