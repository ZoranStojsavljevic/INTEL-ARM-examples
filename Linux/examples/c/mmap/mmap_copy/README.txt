### Compiling command

	gcc mmcopy.c -o mmcopy

### Execution command

	### general command:
	./mmcopy <input_file> <output_file>

	### the example used here:
	./mmcopy mmcopy.c outfile.txt

### Why this example?

It is a part of much wider project/context. It proves the concept
of reading input file using mmap() to designated memory virtual
space, and as writing from this virtual space to another designated
virtual space created by mmap(), used to write to output file.

