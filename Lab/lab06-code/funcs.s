.text
.global my_max
.global my_pow

# Computes maximum of 2 arguments
# You can assume argument 1 (x) is in %edi
# You can assume argument 2 (y) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.
my_max:
    movl %edi, %eax
    movl %esi, %ecx
    cmpl %ecx, %eax
    jge END
    jle SMALL
SMALL:
    movl %ecx, %eax
    ret
END:
    ret

# Computes base^exp
# You can assume argument 1 (base) is in %edi
# You can assume argument 2 (exp) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.
my_pow:
    movl $1, %eax
    movl %esi, %ecx
    movl $0, %edx
    jmp FOR
FOR:
    imull %edi, %eax
    addl $1, %edx
    cmpl %ecx, %edx
    jne FOR
    jmp LAST
LAST:
    ret

1
