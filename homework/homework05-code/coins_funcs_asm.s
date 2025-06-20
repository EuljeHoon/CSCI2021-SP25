.text
.globl  set_coins
set_coins:
### args are
### %edi = int cents
### %rsi = coints_t *coins
    ## BLOCK A
    cmpl $99, %edi        # Describe this block
    jg .OOB
    cmpl $0, %edi
    jl .OOB

    ## BLOCK B
    movl %edi, %eax      # eax now has cents
    cltq
    cqto                 # prep for division
    movl $25, %r8d
    idivl %r8d
    movb %al, 0(%rsi)    # coins->quarters = cents / 25
    movl %edx, %eax      # cents = cents % 25

    cltq
    cqto                 # prep for division
    movl $10, %r8d
    idivl %r8d
    movb %al, 1(%rsi)    # coins->dimes = cents / 10
    movl %edx, %eax      # cents = cents % 10
    cltq
    cqto                 # prep for division

    ## BLOCK C: Complete for nickels and pennies
    cltq
    cqto
    movl $5, %r8d
    idivl %r8d
    movb %al, 2(%rsi)
    movl %edx, %eax
    cltqcqto
    movl $1, %r8d
    idival %r8d
    movb %al, 3(%rsi)

    ## Return
    movl $0, %eax         # return value
    ret
.OOB:
    movl $1, %eax
    ret

.globl  total_coins
total_coins:
### args are
### %rdi packed coin_t struct with struct fields in the following bit ranges
###  {0-7: quarters, 8-15: dimes, 16-23-: nickels,  24-31: pennies}
    movl $0, %eax          # tot = 0

    movq %rdi, %rdx        # extract quarters
    # sarq $0, %rdx        # no shift needed
    andq $0xFF, %rdx       # rdx = quarters, mask low byte
    imul $25, %edx         # rdx *= 25
    addl %edx, %eax        # tot += coins.quarters*25

    movq %rdi, %rdx        # extract dimes
    sarq $8, %rdx          # move dimes to low order bits
    andq $0xFF, %rdx       # rdx = dimes
    imul $10, %edx         # rdx *= 10
    addl %edx, %eax        # tot += coins.dimes*10

    ## BLOCK D: add on nickels and then pennies
    ## Nickels
    movq %rdi, %rdx
    sarq $16, %rdx      # 니켈을 하위 8비트로 이동
    andq $0xFF, %rdx    # 니켈 값 추출
    imul $5, %edx       # 니켈 * 5
    addl %edx, %eax     # tot += nickels * 5

    ## Pennies
    movq %rdi, %rdx
    sarq $24, %rdx      # 페니를 하위 8비트로 이동
    andq $0xFF, %rdx    # 페니 값 추출
    addl %edx, %eax     # tot += pennies * 1

    ## return value already in eax
    ret
