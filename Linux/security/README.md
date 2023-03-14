### Using suid bit after droping the privileges
https://www.oreilly.com/library/view/secure-programming-cookbook/0596003943/ch01s03.html

https://stackoverflow.com/questions/9297415/correct-way-to-run-setuid-programs-in-c

https://superuser.com/questions/1696909/what-is-the-meaning-of-using-euidif-ruid-and-euid-of-a-process-is-1000-0-and-i

### An example (how to test setuid.c)

	gcc -Wall setuid.c -o ./setuid
	sudo chown root:users setuid
	sudo chmod ug+s ./setuid
	./setuid.c
