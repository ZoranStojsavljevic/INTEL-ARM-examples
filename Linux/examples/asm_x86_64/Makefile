build:
	### This command generates mmapdemo.s
	gcc -c -S mmapdemo.c

	### This command generates obj code mmapdemo.o from mmapdemo.s
	gcc -c mmapdemo.s -o mmapdemo.o

	### To invoke the linker the following should be done:
	gcc mmapdemo.o -o mmapdemo

	### This command generates mmapdemo_list.s - combined/interleaved obj, asm and c code
	gcc -Wa,-adhln -g mmapdemo.c > mmapdemo_list.s

