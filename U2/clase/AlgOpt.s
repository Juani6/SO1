	.file	"AlgPeterson.c"
	.text
	.p2align 4
	.globl	inc1
	.type	inc1, @function
inc1:
.LFB52:
	.cfi_startproc
	endbr64
	pushq	%rax
	.cfi_def_cfa_offset 16
	popq	%rax
	.cfi_def_cfa_offset 8
	xorl	%edi, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	addl	$1000, num(%rip)
	call	pthread_exit@PLT
	.cfi_endproc
.LFE52:
	.size	inc1, .-inc1
	.p2align 4
	.globl	inc2
	.type	inc2, @function
inc2:
.LFB56:
	.cfi_startproc
	endbr64
	pushq	%rax
	.cfi_def_cfa_offset 16
	popq	%rax
	.cfi_def_cfa_offset 8
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	inc1
	.cfi_endproc
.LFE56:
	.size	inc2, .-inc2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Entraron : %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	endbr64
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	xorl	%ecx, %ecx
	leaq	inc1(%rip), %rdx
	xorl	%esi, %esi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %rdi
	call	pthread_create@PLT
	xorl	%ecx, %ecx
	leaq	inc2(%rip), %rdx
	xorl	%esi, %esi
	leaq	16(%rsp), %rdi
	call	pthread_create@PLT
	movq	8(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movq	16(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join@PLT
	movl	num(%rip), %edx
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	movl	$2, %edi
	call	__printf_chk@PLT
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L9
	xorl	%eax, %eax
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE54:
	.size	main, .-main
	.globl	turno
	.bss
	.align 4
	.type	turno, @object
	.size	turno, 4
turno:
	.zero	4
	.globl	flag
	.align 8
	.type	flag, @object
	.size	flag, 8
flag:
	.zero	8
	.globl	num
	.align 4
	.type	num, @object
	.size	num, 4
num:
	.zero	4
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
