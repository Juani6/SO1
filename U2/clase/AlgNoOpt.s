	.file	"AlgPeterson.c"
	.text
	.globl	num
	.bss
	.align 4
	.type	num, @object
	.size	num, 4
num:
	.zero	4
	.globl	flag
	.align 8
	.type	flag, @object
	.size	flag, 8
flag:
	.zero	8
	.globl	turno
	.align 4
	.type	turno, @object
	.size	turno, 4
turno:
	.zero	4
	.text
	.globl	inc1
	.type	inc1, @function
inc1:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	num(%rip), %eax
	addl	$1, %eax
	movl	%eax, num(%rip)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$999, -4(%rbp)
	jle	.L3
	movl	$0, %edi
	call	pthread_exit@PLT
	.cfi_endproc
.LFE6:
	.size	inc1, .-inc1
	.globl	inc2
	.type	inc2, @function
inc2:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movl	num(%rip), %eax
	addl	$1, %eax
	movl	%eax, num(%rip)
	addl	$1, -4(%rbp)
.L5:
	cmpl	$999, -4(%rbp)
	jle	.L6
	movl	$0, %edi
	call	pthread_exit@PLT
	.cfi_endproc
.LFE7:
	.size	inc2, .-inc2
	.section	.rodata
.LC0:
	.string	"Entraron : %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-24(%rbp), %rax
	movl	$0, %ecx
	leaq	inc1(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	leaq	-16(%rbp), %rax
	movl	$0, %ecx
	leaq	inc2(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	movl	num(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
