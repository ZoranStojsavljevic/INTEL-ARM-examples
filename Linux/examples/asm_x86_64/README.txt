### Let us focus a bit onto the asm_x86_64

This example shows a complexity of the translation from c to asm.

### Very beginning of the code mmapdemo_list.s: 

enter n,0 is exactly equivalent to (and should be replaced with):

21				.loc 1 14 1
22				.cfi_startproc
23 0000 F30F1EFA		endbr64
24 0004 55			pushq	%rbp		<<===== save %rbp
25				.cfi_def_cfa_offset 16
26				.cfi_offset 6, -16
27 0005 4889E5			movq	%rsp, %rbp	<<===== copy SP to BP
28				.cfi_def_cfa_register 6
29 0008 4881ECC0		subq	$192, %rsp	<<===== allocate space on the stack

### End of the code mmapdemo_list.s:

139 0179 C9			leave

Which translates totally in opposite way:

leave is exactly equivalent to:

				mov   %rbp, %rsp	<<===== restore rsp = rbp
				pop   %rbp		<<===== restore rbp

### Example:

I hope, other mappings are clear for you from the mmapdemo_list.s !

19:mmapdemo.c	****		if (argc != 1) {	<<===== cmpl    $1, -180(%rbp)
36				.loc 1 19 5
37 002b 83BD4CFF		cmpl    $1, -180(%rbp)
37      FFFF01
38 0032 742A			je      .L2		<<===== if argc $1 continue, othwerwise exit!
20:mmapdemo.c	****		fprintf(stderr, "usage: mmapdemo \n");

