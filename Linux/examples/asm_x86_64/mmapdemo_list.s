   1              		.file	"mmapdemo.c"
   2              		.text
   3              	.Ltext0:
   4              		.section	.rodata
   5              	.LC0:
   6 0000 75736167 		.string	"usage: mmapdemo \n"
   6      653A206D
   6      6D617064
   6      656D6F20
   6      0A00
   7              	.LC1:
   8 0012 6D6D6170 		.string	"mmapdemo.c"
   8      64656D6F
   8      2E6300
   9              	.LC2:
  10 001d 6F70656E 		.string	"open"
  10      00
  11              	.LC3:
  12 0022 73746174 		.string	"stat"
  12      00
  13              	.LC4:
  14 0027 6D6D6170 		.string	"mmap"
  14      00
  15              		.text
  16              		.globl	main
  18              	main:
  19              	.LFB6:
  20              		.file 1 "mmapdemo.c"
   1:mmapdemo.c    **** #include <stdio.h>
   2:mmapdemo.c    **** #include <stdlib.h>
   3:mmapdemo.c    **** #include <fcntl.h>
   4:mmapdemo.c    **** #include <unistd.h>
   5:mmapdemo.c    **** #include <sys/types.h>
   6:mmapdemo.c    **** #include <sys/mman.h>
   7:mmapdemo.c    **** #include <sys/stat.h>
   8:mmapdemo.c    **** #include <errno.h>
   9:mmapdemo.c    ****
  10:mmapdemo.c    **** // Memory Mapped Files
  11:mmapdemo.c    **** // https://www.sao.ru/hq/sts/linux/doc/ipc_guide/mmap.html
  12:mmapdemo.c    ****
  13:mmapdemo.c    **** int main(int argc, char *argv[])
  14:mmapdemo.c    **** {
  21              		.loc 1 14 1
  22              		.cfi_startproc
  23 0000 F30F1EFA 		endbr64
  24 0004 55       		pushq	%rbp
  25              		.cfi_def_cfa_offset 16
  26              		.cfi_offset 6, -16
  27 0005 4889E5   		movq	%rsp, %rbp
  28              		.cfi_def_cfa_register 6
  29 0008 4881ECC0 		subq	$192, %rsp
  29      000000
  30 000f 89BD4CFF 		movl	%edi, -180(%rbp)
  30      FFFF
  31 0015 4889B540 		movq	%rsi, -192(%rbp)
  31      FFFFFF
  32              		.loc 1 14 1
  33 001c 64488B04 		movq	%fs:40, %rax
  33      25280000
  33      00
  34 0025 488945F8 		movq	%rax, -8(%rbp)
  35 0029 31C0     		xorl	%eax, %eax
  15:mmapdemo.c    **** 	int fd;
  16:mmapdemo.c    **** 	char *data;
  17:mmapdemo.c    **** 	struct stat sbuf;
  18:mmapdemo.c    ****
  19:mmapdemo.c    **** 	if (argc != 1) {
  36              		.loc 1 19 5
  37 002b 83BD4CFF 		cmpl	$1, -180(%rbp)
  37      FFFF01
  38 0032 742A     		je	.L2
  20:mmapdemo.c    **** 		fprintf(stderr, "usage: mmapdemo \n");
  39              		.loc 1 20 3
  40 0034 488B0500 		movq	stderr(%rip), %rax
  40      000000
  41 003b 4889C1   		movq	%rax, %rcx
  42 003e BA110000 		movl	$17, %edx
  42      00
  43 0043 BE010000 		movl	$1, %esi
  43      00
  44 0048 488D3D00 		leaq	.LC0(%rip), %rdi
  44      000000
  45 004f E8000000 		call	fwrite@PLT
  45      00
  21:mmapdemo.c    **** 		exit(1);
  46              		.loc 1 21 3
  47 0054 BF010000 		movl	$1, %edi
  47      00
  48 0059 E8000000 		call	exit@PLT
  48      00
  49              	.L2:
  22:mmapdemo.c    **** 	}
  23:mmapdemo.c    ****
  24:mmapdemo.c    **** 	if ((fd = open("mmapdemo.c", O_RDONLY)) == -1) {
  50              		.loc 1 24 12
  51 005e BE000000 		movl	$0, %esi
  51      00
  52 0063 488D3D00 		leaq	.LC1(%rip), %rdi
  52      000000
  53 006a B8000000 		movl	$0, %eax
  53      00
  54 006f E8000000 		call	open@PLT
  54      00
  55 0074 898554FF 		movl	%eax, -172(%rbp)
  55      FFFF
  56              		.loc 1 24 5
  57 007a 83BD54FF 		cmpl	$-1, -172(%rbp)
  57      FFFFFF
  58 0081 7516     		jne	.L3
  25:mmapdemo.c    **** 		perror("open");
  59              		.loc 1 25 3
  60 0083 488D3D00 		leaq	.LC2(%rip), %rdi
  60      000000
  61 008a E8000000 		call	perror@PLT
  61      00
  26:mmapdemo.c    **** 		exit(1);
  62              		.loc 1 26 3
  63 008f BF010000 		movl	$1, %edi
  63      00
  64 0094 E8000000 		call	exit@PLT
  64      00
  65              	.L3:
  27:mmapdemo.c    **** 	}
  28:mmapdemo.c    ****
  29:mmapdemo.c    **** 	if (stat("mmapdemo.c", &sbuf) == -1) {
  66              		.loc 1 29 6
  67 0099 488D8560 		leaq	-160(%rbp), %rax
  67      FFFFFF
  68 00a0 4889C6   		movq	%rax, %rsi
  69 00a3 488D3D00 		leaq	.LC1(%rip), %rdi
  69      000000
  70 00aa E8000000 		call	stat@PLT
  70      00
  71              		.loc 1 29 5
  72 00af 83F8FF   		cmpl	$-1, %eax
  73 00b2 7516     		jne	.L4
  30:mmapdemo.c    **** 		perror("stat");
  74              		.loc 1 30 3
  75 00b4 488D3D00 		leaq	.LC3(%rip), %rdi
  75      000000
  76 00bb E8000000 		call	perror@PLT
  76      00
  31:mmapdemo.c    **** 		exit(1);
  77              		.loc 1 31 3
  78 00c0 BF010000 		movl	$1, %edi
  78      00
  79 00c5 E8000000 		call	exit@PLT
  79      00
  80              	.L4:
  32:mmapdemo.c    **** 	}
  33:mmapdemo.c    ****
  34:mmapdemo.c    **** 	if ((data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (caddr_t)(-1)) {
  81              		.loc 1 34 35
  82 00ca 488B4590 		movq	-112(%rbp), %rax
  83              		.loc 1 34 14
  84 00ce 4889C6   		movq	%rax, %rsi
  85 00d1 8B8554FF 		movl	-172(%rbp), %eax
  85      FFFF
  86 00d7 41B90000 		movl	$0, %r9d
  86      0000
  87 00dd 4189C0   		movl	%eax, %r8d
  88 00e0 B9010000 		movl	$1, %ecx
  88      00
  89 00e5 BA010000 		movl	$1, %edx
  89      00
  90 00ea BF000000 		movl	$0, %edi
  90      00
  91 00ef E8000000 		call	mmap@PLT
  91      00
  92 00f4 48898558 		movq	%rax, -168(%rbp)
  92      FFFFFF
  93              		.loc 1 34 5
  94 00fb 4883BD58 		cmpq	$-1, -168(%rbp)
  94      FFFFFFFF
  95 0103 7516     		jne	.L5
  35:mmapdemo.c    **** 		perror("mmap");
  96              		.loc 1 35 3
  97 0105 488D3D00 		leaq	.LC4(%rip), %rdi
  97      000000
  98 010c E8000000 		call	perror@PLT
  98      00
  36:mmapdemo.c    **** 		exit(1);
  99              		.loc 1 36 3
 100 0111 BF010000 		movl	$1, %edi
 100      00
 101 0116 E8000000 		call	exit@PLT
 101      00
 102              	.L5:
 103              	.LBB2:
  37:mmapdemo.c    **** 	}
  38:mmapdemo.c    ****
  39:mmapdemo.c    **** 	for (int i=0; i < sbuf.st_size; i++)
 104              		.loc 1 39 11
 105 011b C78550FF 		movl	$0, -176(%rbp)
 105      FFFF0000
 105      0000
 106              		.loc 1 39 2
 107 0125 EB27     		jmp	.L6
 108              	.L7:
  40:mmapdemo.c    **** 		printf("%c", data[i]);
 109              		.loc 1 40 20 discriminator 3
 110 0127 8B8550FF 		movl	-176(%rbp), %eax
 110      FFFF
 111 012d 4863D0   		movslq	%eax, %rdx
 112 0130 488B8558 		movq	-168(%rbp), %rax
 112      FFFFFF
 113 0137 4801D0   		addq	%rdx, %rax
 114 013a 0FB600   		movzbl	(%rax), %eax
 115              		.loc 1 40 3 discriminator 3
 116 013d 0FBEC0   		movsbl	%al, %eax
 117 0140 89C7     		movl	%eax, %edi
 118 0142 E8000000 		call	putchar@PLT
 118      00
  39:mmapdemo.c    **** 		printf("%c", data[i]);
 119              		.loc 1 39 35 discriminator 3
 120 0147 838550FF 		addl	$1, -176(%rbp)
 120      FFFF01
 121              	.L6:
  39:mmapdemo.c    **** 		printf("%c", data[i]);
 122              		.loc 1 39 18 discriminator 1
 123 014e 8B8550FF 		movl	-176(%rbp), %eax
 123      FFFF
 124 0154 4863D0   		movslq	%eax, %rdx
  39:mmapdemo.c    **** 		printf("%c", data[i]);
 125              		.loc 1 39 24 discriminator 1
 126 0157 488B4590 		movq	-112(%rbp), %rax
  39:mmapdemo.c    **** 		printf("%c", data[i]);
 127              		.loc 1 39 2 discriminator 1
 128 015b 4839C2   		cmpq	%rax, %rdx
 129 015e 7CC7     		jl	.L7
 130              	.LBE2:
  41:mmapdemo.c    ****
  42:mmapdemo.c    **** 	return 0;
 131              		.loc 1 42 9
 132 0160 B8000000 		movl	$0, %eax
 132      00
  43:mmapdemo.c    **** }
 133              		.loc 1 43 1
 134 0165 488B4DF8 		movq	-8(%rbp), %rcx
 135 0169 6448330C 		xorq	%fs:40, %rcx
 135      25280000
 135      00
 136 0172 7405     		je	.L9
 137 0174 E8000000 		call	__stack_chk_fail@PLT
 137      00
 138              	.L9:
 139 0179 C9       		leave
 140              		.cfi_def_cfa 7, 8
 141 017a C3       		ret
 142              		.cfi_endproc
 143              	.LFE6:
 145              	.Letext0:
 146              		.file 2 "/usr/lib/gcc/x86_64-linux-gnu/9/include/stddef.h"
 147              		.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
 148              		.file 4 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h"
 149              		.file 5 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h"
 150              		.file 6 "/usr/include/stdio.h"
 151              		.file 7 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
 152              		.file 8 "/usr/include/x86_64-linux-gnu/sys/types.h"
 153              		.file 9 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h"
 154              		.file 10 "/usr/include/x86_64-linux-gnu/bits/stat.h"
 155              		.file 11 "/usr/include/unistd.h"
 156              		.file 12 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
 1356              		.section	.note.gnu.property,"a"
 1357              		.align 8
 1358 0000 04000000 		.long	 1f - 0f
 1359 0004 10000000 		.long	 4f - 1f
 1360 0008 05000000 		.long	 5
 1361              	0:
 1362 000c 474E5500 		.string	 "GNU"
 1363              	1:
 1364              		.align 8
 1365 0010 020000C0 		.long	 0xc0000002
 1366 0014 04000000 		.long	 3f - 2f
 1367              	2:
 1368 0018 03000000 		.long	 0x3
 1369              	3:
 1370 001c 00000000 		.align 8
 1371              	4:
