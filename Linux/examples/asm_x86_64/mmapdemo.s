	.file	"mmapdemo.c"
	.text
	.section	.rodata
.LC0:
	.string	"usage: mmapdemo \n"
.LC1:
	.string	"mmapdemo.c"
.LC2:
	.string	"open"
.LC3:
	.string	"stat"
.LC4:
	.string	"mmap"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movl	%edi, -180(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -180(%rbp)
	je	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$17, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	movl	$0, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -172(%rbp)
	cmpl	$-1, -172(%rbp)
	jne	.L3
	leaq	.LC2(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L3:
	leaq	-160(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	call	stat@PLT
	cmpl	$-1, %eax
	jne	.L4
	leaq	.LC3(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L4:
	movq	-112(%rbp), %rax
	movq	%rax, %rsi
	movl	-172(%rbp), %eax
	movl	$0, %r9d
	movl	%eax, %r8d
	movl	$1, %ecx
	movl	$1, %edx
	movl	$0, %edi
	call	mmap@PLT
	movq	%rax, -168(%rbp)
	cmpq	$-1, -168(%rbp)
	jne	.L5
	leaq	.LC4(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L5:
	movl	$0, -176(%rbp)
	jmp	.L6
.L7:
	movl	-176(%rbp), %eax
	movslq	%eax, %rdx
	movq	-168(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar@PLT
	addl	$1, -176(%rbp)
.L6:
	movl	-176(%rbp), %eax
	movslq	%eax, %rdx
	movq	-112(%rbp), %rax
	cmpq	%rax, %rdx
	jl	.L7
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
