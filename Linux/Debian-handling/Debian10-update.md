### Debian 10 Buster update/upgrade

The file “/etc/apt/sources.list” should look like this:

	deb http://httpredir.debian.org/debian buster main
	deb http://httpredir.debian.org/debian buster-updates main
	deb http://security.debian.org buster/updates main

	echo 'deb http://httpredir.debian.org/debian buster-backports main' > /etc/apt/sources.list.d/buster-backports.list
	deb http://httpredir.debian.org/debian buster-backports main

Please, update the package index (for every now on, monthly):

	$ sudo apt-get update --fix-missing
	$ sudo apt-get upgrade
	$ sudo systemctl daemon-reload
