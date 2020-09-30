### Understanding the linkerscript for an ARM Cortex-M microcontroller
https://stackoverflow.com/questions/40532180/understanding-the-linkerscript-for-an-arm-cortex-m-microcontroller

I am using the STM32F746NG microcontroller from STMicroelectronics. This device is based on the ARM
Cortex-M7 architecture. I invested quite some time in understanding the linkerscript from example
projects. I figured out the basics, but I still cannot grasp big parts of it. Please help me to
understand those parts.

#### Start of the linkerscript

The linkerscript starts as follows:

	/* Entry Point */
	ENTRY(Reset_Handler) /* The function named 'Reset_Handler' is defined */
			     /* in the 'startup.s' assembly file.             */

	/* Highest address of the user mode stack */
	/* Remember: the stack points downwards */
	_estack = 0x20050000;    /* End of RAM */

	/* Generate a link error if heap and stack don't fit into RAM */
	_Min_Heap_Size = 0x200;  /* Required amount of heap  */
	_Min_Stack_Size = 0x400; /* Required amount of stack */

	/* --------------------------------------------------------------------*/
	/*                    MEMORY AREAS                                     */
	/* --------------------------------------------------------------------*/
	MEMORY
	{
	    /* FLASH MEMORY */
	    /* ------------ */
	    /* Remember: the flash memory on this device can   */
	    /* get accessed through either the AXIM bus or the */
	    /* ITCM bus. Accesses on the ITCM bus start at     */
	    /* address 0x0020 0000. Accesses on the AXIM bus   */
	    /* at address 0x0800 0000.                         */
	    FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 1024K
	    /* FLASH (rx)     : ORIGIN = 0x00200000, LENGTH = 1024K */

	    /* RAM MEMORY */
	    /* ---------- */
	    RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 320K
	}

#### Vector table

After defining the memory areas, the linkerscript proceeds with defining the sections. The first
section defined in the linkerscript is the vector table. It has to end up in the first bytes of
the flash memory.

	/* --------------------------------------------------------------------*/
	/*                    OUTPUT SECTIONS                                  */
	/* --------------------------------------------------------------------*/
	SECTIONS
	{
	    /****************************/
	    /*      VECTOR TABLE        */
	    /****************************/
	    .isr_vector :
	    {
		. = ALIGN(4);
		KEEP(*(.isr_vector)) /* Vector Table */
		. = ALIGN(4);
	    } >FLASH

#### Program code

	After the vector table is inserted, it's time for the program code:

	    /****************************/
	    /*      PROGRAM CODE        */
	    /****************************/
	    .text :
	    {
		. = ALIGN(4);
		*(.text)           /* .text sections (code) */
		*(.text*)          /* .text* sections (code) */
		*(.glue_7)         /* Glue ARM to Thumb code */
		*(.glue_7t)        /* Glue Thumb to ARM code */
		*(.eh_frame)

		/* Note: The function ‘.text.Reset_Handler’ is one of the *(.text*) sections,      */
		/* such that it gets linked into the output .text section somewhere here.          */
		/* We can verify the exact spot where the Reset_Handler section is positioned, by  */
		/* examining the second entry of the vector table.                                 */
		/* A test has given the following results:					   */
		/*    FLASH (rx) : ORIGIN = 0x0800 0000    ==>  Reset_Handler = 0x0800 1C91        */
		/*    FLASH (rx) : ORIGIN = 0x0020 0000    ==>  Reset_Handler = 0x0020 1CB9        */
		/*										   */
		/* In both cases, the Reset_Handler section ends up a few hundred bytes after the  */
		/* vector table in Flash. But in the first case, the “Reset_Handler” symbol points */
		/* to the Reset-code through AXIM-interface, whereas in the latter case it points  */
		/* to the Reset-code through the ITCM-interface.                                   */

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		_etext = .;        /* Define a global symbol at end of code */

	    } >FLASH

The linkerscript defines the e_text global symbol that represents the address where the program
code in flash ends.

#### Constant data

The read-only data ends up in the flash memory as well (it makes no sense to put it in RAM, which
is volatile). The linkerscript defines that the .rodata section should be in flash:

	    /****************************/
	    /*      CONSTANT DATA       */
	    /****************************/
	    .rodata :
	    {
		. = ALIGN(4);
		*(.rodata)         /* .rodata sections (constants, strings, etc.) */
		*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
		. = ALIGN(4);
	    } >FLASH

#### Mysterious sections in flash

After defining where the constant read-only data should go, the linkerscript defines that a few
'mysterious' sections should end up in flash as well:

	    .ARM.extab :
	    {
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	    } >FLASH
	    .ARM :
	    {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	    } >FLASH
	    .preinit_array :
	    {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	    } >FLASH
	    .init_array :
	    {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	    } >FLASH
	    .fini_array :
	    {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	    } >FLASH

I have no idea what those sections are. So let this be the first question. What are these sections,
and in what object files do they show up? As you know, the linkerscript needs to link together some
object files. I have no idea in what object files these mysterious sections exist:

	.ARM.extab
	.ARM
	.preinit_array
	.init_array
	.fini_array

This is the end of allocations to the flash memory. The linkerscript continues with defining sections
that end up in the RAM.

#### Sections in RAM

The .data and .bss sections are clear to me. No questions about this.

	    /****************************/
	    /*    INITIALIZED DATA      */
	    /****************************/
	    _sidata = LOADADDR(.data);
	    .data :
	    {
		. = ALIGN(4);
		_sdata = .;        /* create a global symbol at data start */
		*(.data)           /* .data sections */
		*(.data*)          /* .data* sections */

		. = ALIGN(4);
		_edata = .;        /* define a global symbol at data end */

	    } >RAM AT> FLASH

	    /****************************/
	    /*    UNINITIALIZED DATA    */
	    /****************************/
	    . = ALIGN(4);
	    .bss :
	    {
		_sbss = .;         /* define a global symbol at bss start */
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss*)
		*(COMMON)

		. = ALIGN(4);
		_ebss = .;         /* define a global symbol at bss end */
		__bss_end__ = _ebss;

	    } >RAM

The linkerscript defines also a ._user_heap_stack section:

	    /****************************/
	    /* USER_HEAP_STACK SECTION  */
	    /****************************/
	    /* User_heap_stack section, used to check that there is enough RAM left */
	    ._user_heap_stack :
	    {
		. = ALIGN(8);
		PROVIDE ( end = . );
		PROVIDE ( _end = . );
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(8);
	    } >RAM

Apparently this section is not used immediately. It is only defined to check if the RAM has still enough
space for the stack and the heap. A linker error is thrown when this is not the case (the . exceeds the
top RAM address).

#### The end of the linkerscript

This is how the linkerscript ends. And honestly, I have no idea what it does. So this is the second
question: What does the following mean?

	    /* Remove information from the standard libraries */
	    /DISCARD/ :
	    {
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	    }

	    .ARM.attributes 0 : { *(.ARM.attributes) }
	}
	/* END OF LINKERSCRIPT */

#### Some answers

.ARM.extab and .ARM.exidx are related to unwinding. You can find more information here:

http://infocenter.arm.com/help/topic/com.arm.doc.ihi0044e/index.html

You don't need them if you don't care about unwinding (unwinding is useful for C++ exception and
for debugging).

These symbols are related to the C / C++ constructor and destructor startup and tear down code that
is called before / after main(). Sections named .init, .ctors, .preinit_array, and .init_array are
to do with initialization of C/C++ objects, and sections .fini, .fini_array, and .dtors are for tear
down. The start and end symbols define the beginning and end of code sections related to such
operations and might be referenced from other parts of the runtime support code.

The .preinit_array and .init_array sections contain arrays of pointers to functions that will
be called on initialization. The .fini_array is an array of functions that will be called on
destruction. Presumably the start and end labels are used to walk these lists.

heap: not really, that part permits to reserve some space for the heap and some space for the stack.
Obviously it rises an error if the sum of reserved areas goes outside the RAM boundaries. This is an
example:

_Min_Heap_Size = 0; /* required amount of heap / _Min_Stack_Size = 0x400; / required amount of stack */

._user_heap_stack : { . = ALIGN(4); PROVIDE ( end = . ); PROVIDE ( _end = . ); . = . + _Min_Heap_Size; . = . + _Min_Stack_Size; . = ALIGN(4); } >RAM

To link libraries I prefer a different notation, this is just an example for a bare-metal no RTOS
C++ project: GROUP(libgcc.a libc_nano.a libstdc++_nano.a libm.a libcr_newlib_nohost.a crti.o crtn.o
crtbegin.o crtend.o)
