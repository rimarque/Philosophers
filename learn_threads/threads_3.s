	.text
	.file	"threads_3.c"
	.globl	routine                         # -- Begin function routine
	.p2align	4, 0x90
	.type	routine,@function
routine:                                # @routine
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	$0, -12(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	addl	$1, %ecx
	movl	%ecx, -12(%rbp)
	cmpl	$100, %eax
	jge	.LBB0_3
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movq	-8(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
	jmp	.LBB0_1
.LBB0_3:
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	routine, .Lfunc_end0-routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, -36(%rbp)
	leaq	-36(%rbp), %rcx
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	movabsq	$routine, %rdx
	callq	pthread_create
	cmpl	$0, %eax
	je	.LBB1_2
# %bb.1:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_2:
	leaq	-36(%rbp), %rcx
	leaq	-32(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	movabsq	$routine, %rdx
	callq	pthread_create
	cmpl	$0, %eax
	je	.LBB1_4
# %bb.3:
	movl	$2, -4(%rbp)
	jmp	.LBB1_9
.LBB1_4:
	movq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	cmpl	$0, %eax
	je	.LBB1_6
# %bb.5:
	movl	$3, -4(%rbp)
	jmp	.LBB1_9
.LBB1_6:
	movq	-32(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	cmpl	$0, %eax
	je	.LBB1_8
# %bb.7:
	movl	$4, -4(%rbp)
	jmp	.LBB1_9
.LBB1_8:
	movl	-36(%rbp), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf
	movl	$0, -4(%rbp)
.LBB1_9:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"number of mails: %d\n"
	.size	.L.str, 21

	.ident	"Ubuntu clang version 12.0.0-3ubuntu1~20.04.5"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym routine
	.addrsig_sym pthread_create
	.addrsig_sym pthread_join
	.addrsig_sym printf
