.text
	.align 4
.globl bmp_mosaic
	.type bmp_mosaic,@function

bmp_mosaic:
    pushq %rbx
    pushq %rdx
    pushq %rsi
    pushq %rcx
    movq $0, %rdx
    movq $4, %rbx
    leaq 3(%rsi, %rsi, 2), %rax
    divq %rbx
    imulq %rbx, %rax
    pushq %rax
    movq $0, %rdx
    movq %rsi, %rax
    divq %rcx
    pushq %rax
    pushq %rax
    movq $0, %rdx
    movq 40(%rsp), %rax
    divq %rcx
    pushq %rax
    movq 32(%rsp), %rbx
    imulq %rbx, %rax
    movq 48(%rsp), %rbx
    subq %rax, %rbx
    movq 24(%rsp), %rax
    movq 32(%rsp), %rdx
    pushq %rax
    pushq %rdi
    pushq %rdx
    pushq %rbx
    cmpq $0, %rbx
    jle again11
again:
    call candf
    movq 16(%rsp), %rdi
    movq 64(%rsp), %rax
    leaq (%rax, %rax, 2), %rax
    leaq (%rdi, %rax), %rdi
    movq %rdi, 16(%rsp)
    movq 40(%rsp), %rax
    decq %rax
    movq %rax, 40(%rsp)
    cmpq $0, %rax
    jg again
    movq 72(%rsp), %rax
    movq 48(%rsp), %rbx
    movq 64(%rsp), %rdx
    imulq %rdx, %rbx
    subq  %rbx, %rax
    movq %rax, 8(%rsp)
    cmp $0, %rax
    jle next
    call candf
next:  movq 16(%rsp), %rdi
    movq 48(%rsp), %rax
    movq 64(%rsp), %rbx
    leaq (%rbx, %rbx, 2), %rbx
    imulq %rbx, %rax
    subq %rax, %rdi
    movq (%rsp), %rax
    movq 24(%rsp), %rbx
    imulq %rbx, %rax
    leaq (%rax, %rdi), %rdi
    movq %rdi, 16(%rsp)
again11:
    movq 64(%rsp), %rax
    movq %rax, (%rsp)
    movq %rax, 8(%rsp)
    movq 48(%rsp), %rax
    movq %rax, 40(%rsp)
again1:
    call candf
    movq 16(%rsp), %rdi
    movq 64(%rsp), %rax
    leaq (%rax, %rax, 2), %rax
    leaq (%rdi, %rax), %rdi
    movq %rdi, 16(%rsp)
    movq 40(%rsp), %rax
    decq %rax
    movq %rax, 40(%rsp)
    cmpq $0, %rax
    jg again1
    movq 72(%rsp), %rax
    movq 48(%rsp), %rbx
    movq 64(%rsp), %rdx
    imulq %rdx, %rbx
    subq  %rbx, %rax
    movq %rax, 8(%rsp)
    cmpq $0, %rax
    jle ss
    call candf
ss:    movq 16(%rsp), %rdi
    movq 24(%rsp), %rbx
    movq 48(%rsp), %rax
    movq 64(%rsp), %rdx
    leaq (%rax, %rax, 2), %rax
    imulq %rdx, %rax
    subq %rax, %rdi
    movq (%rsp), %rax
    imulq %rbx, %rax
    leaq (%rax, %rdi), %rdi
    movq %rdi, 16(%rsp)
    movq 32(%rsp), %rax
    decq %rax
    movq %rax, 32(%rsp)
    cmpq $0, %rax
    jg again11
    leaq 88(%rsp), %rsp
    popq %rbx
	ret
candf:
    movq 24(%rsp), %rdi
    movq 8(%rsp), %rax
    movq 16(%rsp), %rbx
    pushq %rax
    pushq %rbx
    pushq $0
    pushq $0
    pushq $0
loop:
    movq (%rsp), %rax
    movzbq (%rdi), %rbx
    addq %rax, %rbx
    movq %rbx, (%rsp)
    movq 8(%rsp), %rax
    movzbq 1(%rdi), %rbx
    addq %rax, %rbx
    movq %rbx, 8(%rsp)

    movq 16(%rsp), %rax
    movzbq 2(%rdi), %rbx
    addq %rax, %rbx
    movq %rbx, 16(%rsp)

    movq 24(%rsp), %rax
    leaq -1(%rax), %rax
    movq %rax, 24(%rsp)
    leaq 3(%rdi), %rdi
    cmpq $0, %rax
    jg loop
    movq 72(%rsp), %rax
    movq 64(%rsp), %rdi
    movq 48(%rsp), %rbx
    movq 32(%rsp), %rdx
    decq %rdx
    movq %rdx, 32(%rsp)
    subq %rdx, %rbx
    imulq %rbx, %rax
    leaq (%rdi, %rax), %rdi
    movq 56(%rsp), %rax
    movq %rax , 24(%rsp)
    cmp $0, %rdx
    jg loop
    movq 48(%rsp), %rax
    movq 56(%rsp), %rbx
    imulq %rax, %rbx
    movq $0, %rdx
    cmpq $0, %rbx
    je lop
    movq (%rsp), %rax
    divq %rbx
    movq %rax, (%rsp)
    movq $0, %rdx
    movq 8(%rsp), %rax
    divq %rbx
    movq %rax, 8(%rsp)
    movq $0, %rdx
    movq 16(%rsp), %rax
    divq %rbx
    movq %rax, 16(%rsp)
lop:    movq 48(%rsp), %rax
    movq %rax, 32(%rsp)
    movq 56(%rsp), %rax
    movq %rax, 24(%rsp)

    movq 64(%rsp), %rdi

loop1:
    movb (%rsp), %al
    movb %al, (%rdi)
    movb 8(%rsp), %al
    movb %al, 1(%rdi)
    movb 16(%rsp), %al
    movb %al, 2(%rdi)
    movq 24(%rsp), %rax
    leaq -1(%rax), %rax
    movq %rax, 24(%rsp)
    leaq 3(%rdi), %rdi
    cmpq $0, %rax
    jg loop1
    movq 32(%rsp), %rax
    leaq -1(%rax), %rax
    movq %rax, 32(%rsp)
    cmp $0, %rax
    jle sjp
    movq 72(%rsp), %rax
    movq 64(%rsp), %rdi
    movq 48(%rsp), %rbx
    movq 32(%rsp), %rdx
    subq %rdx, %rbx
    imulq %rbx, %rax
    leaq (%rdi, %rax), %rdi
    movq 56(%rsp), %rdx
    movq %rdx , 24(%rsp)
    jmp loop1
    sjp:movq $5, %rax
    leaq 40(%rsp), %rsp
    ret