Memory Map Manipulation with mmap
CS 301 Lecture, Dr. Lawlor

https://www.cs.uaf.edu/2016/fall/cs301/lecture/11_02_mmap.html

So your program's memory doesn't actually correspond 1-to-1 with the system's physical RAM; there's one layer of indirection called the "page table" that maps program "virtual addresses" into real "physical addresses".   Virtual addresses aren't listed byte-by-byte, which would make the table huge, instead the table granularity is "pages" usually 4KB or 4MB in size that all get mapped to adjacent places in physical memory. 

In addition to storing the location in physical memory, a page table entry usually contains a bunch of access control bits indicating what operations are allowed by whom on that page.  For example, a page can be marked readonly to a particular process by just flipping a bit in that page's page table entry.  Most processes don't have very much memory mapped into them, so no matter what pointers they use, they can't break things they don't own.

(The dirtycow kernel bug is a multithreaded problem in the way Linux updated the page table.)

Bottom line: the pagetable is the cool CPU hardware support that is useful to do crazy stuff with memory. 
UNIX Mapping
The UNIX system calls to manipulate the page table are:

    mmap to put physical memory at a given location in program virtual memory, and optionally copying a file's contents there.
    munmap to remove physical memory from a given location in virtual memory.
    mprotect changes your access rights on a particular piece of memory.  For example, you can remove your right to write to a particular chunk of memory.
    brk and sbrk are older (pre-mmap) calls that adjust the "heap boundary", adding zero-filled physical memory at the end of the heap virtual address space.  They should almost always now be replaced with calls to mmap.

Here's an example of how to call mmap, to get 1MB of readable, writeable memory.  The first argument is a "suggested address" where you want the memory to go; try putting your own page-aligned address in there and see what happens!

#include <sys/mman.h>

int foo(void) {
	int len=1024*1024; 
	void *addr=mmap((void *)0,len, /* address and data size (bytes) */
		PROT_READ+PROT_WRITE,MAP_ANONYMOUS+MAP_SHARED, /* access flags */
		-1,0); /* <- file descriptor (none needed) and file offset */
	if (addr==MAP_FAILED) {perror("mmap"); exit(1);}

	int *buf=(int *)addr; /* <- make mmap'd region into an int pointer */
	buf[3]=7;
	buf[2]=buf[3];
	printf("mmap returned %p, which seems readable and writable\n",addr);
	munmap(addr,len);

	return 0;
}

(executable NetRun link)

The six arguments to mmap are:

    address, a pointer to the first byte to change.  This pointer and the length must both be a multiple of 4096 bytes (0x1000 bytes), since this is the size of a page.  You can round down to the nearest aligned page size with "ptr&~0xfff" (you may need to typecast the pointer to a "long" first).  Passing a zero pointer asks for the next unused area of memory.
    length, the number of bytes to change.  Must be a multiple of 4096 bytes (0x1000 bytes).
    access requested, some combination of PROT_READ+PROT_WRITE+PROT_EXEC.  In theory you can mark memory read-only, write-only, read-and-execute, etc.  The hardware will give you *at least* this access; although real machines might not be able to do every combination exactly in hardware.  For example, for decades x86 merged read and execute rights; they only split these (as XD/NX) during the 64-bit transition.
    flags, which are typically MAP_ANONYMOUS+MAP_SHARED.  MAP_ANONYMOUS is just plain memory, with no file attached.  MAP_SHARED makes your writes visible to anybody else that has the same piece of memory mapped; the alternative is MAP_PRIVATE, which gives you a unique scratch copy of the memory.
    a file descriptor, a previously opened file to use as the initial contents of the memory.  PROT_WRITE and MAP_SHARED can be used to change the file, by writing data to memory. Not used for an anonymous mapping, so typically left as -1.
    a file offset, the location in the file to start the mapping.  Not used for an anonymous mapping, so typically left as 0.

Mmap gets used for lots of different purposes:

You just want some memory from the OS.  void *mem=mmap(0,length, PROT_READ+PROT_WRITE, MAP_ANONYMOUS+MAP_SHARED, -1,0);
You want to put some memory at a given location, for example to service a page fault, or operate with old code, so you pass in an address.  	mmap((void *)0xabcde000,length, PROT_READ+PROT_WRITE, MAP_ANONYMOUS+MAP_SHARED, -1,0);
You want to mark a given location as unreadable, for example to cause pagefaults when people try to access there.
	mmap((void *)0xabcde000,length, PROT_NONE, MAP_ANONYMOUS+MAP_SHARED, -1,0);
You want to create some executable memory, for example to write some machine code there and have it be runnable.
	void *mem=mmap(0,length, PROT_READ+PROT_WRITE+PROT_EXEC, MAP_ANONYMOUS+MAP_SHARED, -1,0);
You want to bring in the file "fd" for reading.  This is useful because I can mmap a 100GB file and use pointer arithmetic to read parts of it, and the OS will only bring in the parts I use.
	void *mem=mmap(0,length, PROT_READ, MAP_ANONYMOUS+MAP_SHARED, fd,0);
You want to bring in the file "fd" for reading and writing. 
	void *mem=mmap(0,length, PROT_READ+PROT_WRITE, MAP_ANONYMOUS+MAP_SHARED, fd,0);

Nearly every combination of protection flags is useful for something:
Flags
	What
	Why
	Weirdness
PROT_NONE
	Disable all access to the memory. Basically requesting a page fault when accessed.  Used by debug tools like "electric fence" to find memory access errors.

PROT_READ
	Read only area.  Useful for input files, or big read-only tables.

PROT_WRITE
	Write only area.  Can't be read, though.  Secure shared drop box?

PROT_EXEC
	Execute only area.  Secure code?

PROT_READ+PROT_WRITE
	Read-write access.  Most ordinary memory from "new" is allocated like this.  You can't execute code here, as a security feature.

PROT_READ+PROT_EXEC
	Readable (for constants) and executable (for code).
	Most programs are mapped this way.

PROT_WRITE+PROT_EXEC
	Write and execute, but not read? Maybe for a dynamically generated program, plus security?

PROT_READ+PROT_WRITE+PROT_EXEC
	Allow all access: do what thou wilt.
	Once used for everything.  Good for dynamically created code.

Windows Memory Mapping
The Windows calls to manipulate the page table are:

    VirtualAlloc puts physical memory at a given virtual address.  You first have to MEM_RESERVE, then MEM_COMMIT a range of virtual addresses.
    VirtualFree removes physical memory from a given virtual address.

They do exactly the same things as mmap, with a very slightly different interface.

Memory Mapping and Threads, GPU, etc

Threads actually share the page table, but the OS sets up a separate stack for each thread.  Print a local variable (or rsp) from several threads, and you'll see they get stored in different locations.

CUDA can use mmap to allow the CPU and GPU to share data, called "Unified Memory".  (At the moment, it's definitely slower than manual cudaMalloc and cudaMemcpy, but they're working on improving that.)

SSE accesses to 4 floats are 16-byte aligned.  Pages are 4096-byte aligned (!).
