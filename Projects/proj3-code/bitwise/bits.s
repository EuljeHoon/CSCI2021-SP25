# Read the following instructions carefully
#
# You will provide your solution to this part of the project by
# editing the collection of functions in this source file.
#
# Some rules from the C bitwise puzzles are still in effect for your assembly
# code here:
#  1. No global variables are allowed
#  2. You may not define or call any additional functions in this file
#  3. You may not use any floating-point assembly instructions
#
# You may assume that your machine:
#  1. Uses two's complement, 32-bit representations of integers.
#  2. Has unpredictable behavior when shifting if the shift amount
#     is less than 0 or greater than 31.

# TO AVOID GRADING SURPRISES:
#   Pay attention to the results of the call_cc script, which is run
#   as part of the provided tests.
#
#   This makes sure you have adhered to the x86-64 calling convention
#   in your assembly code. If it reports any errors, make sure to fix
#   them before you submit your code.
#
# YOU WILL RECEIVE NO CREDIT IF YOUR CODE DOES NOT PASS THIS CHECK

# isZero - returns 1 if x == 0, and 0 otherwise
#   Examples: isZero(5) = 0, isZero(0) = 1
#   Rating: 1
.global isZero
isZero:
    movl %edi, %eax
    negl %eax # -x
    orl %eax, %edi # if x is 0 return 0
    shrl $31, %edi # get operater
    xorl $1, %edi
    movl %edi, %eax
    ret

# bitNor - Compute ~(x|y)
#   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
#   Rating: 1
.global bitNor
bitNor:
    movl %edi, %eax  # set x to the %eax
    movl %esi, %ecx  # set y to the %ecx
    notl %eax        # ~x
    notl %ecx        # ~y
    andl %ecx, %eax
    ret

# leastBitPos - return a mask that marks the position of the
#               least significant 1 bit. If x == 0, return 0
#   Example: leastBitPos(96) = 0x20
#   Rating: 2
.global leastBitPos
leastBitPos:
    movl %edi, %eax  # move x to the %eax
    movl %eax, %ecx  # save original value for %eax into the %ecx
    notl %eax        # ~ %eax
    addl $1, %eax
    andl %ecx, %eax
    ret

# copyLSB - set all bits of result to least significant bit of x
#   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
#   Rating: 2
.global copyLSB
copyLSB:
    movl %edi, %ecx  # move x to the %eax
    shll $31, %ecx   # shift 31 beat to the left
    sarl $31, %ecx   # shift 31 beat to the right with keep the operator
    movl %ecx, %eax
    ret

# distinctNegation - returns 1 if x != -x.
#     and 0 otherwise
#   Rating: 2
.global distinctNegation
distinctNegation:
    movl %edi, %eax  # move x to the %eax
    movl %eax, %edx  # save original value for %eax into the %edx
    notl %eax        # ~ %eax
    addl $1, %eax    # ~ %eax + 1
    xorl %edx, %eax  # %eax ^ ~ %eax
    movl %eax, %ecx
    sarl $31, %ecx   # make %ecx as a sign bit
    movl %ecx, %r8d
    movl %eax, %ecx
    sarl $31, %ecx   # make %ecx as a sign bit
    movl %ecx, %eax
    negl %eax        # %eax is equal to ~(%eax)
    orl %r8d, %eax   # if one of those is sign bit, return 1
    andl $1, %eax
    ret

# floatAbsVal - Return bit-level equivalent of absolute value of f for
#   floating point argument f.
#   Both the argument and result are passed as unsigned int's, but
#   they are to be interpreted as the bit-level representations of
#   single-precision floating point values.
#   When argument is NaN, return argument.
#   Rating: 2
.global floatAbsVal
floatAbsVal:
    movl %edi, %edx
    andl $0x7FFFFFFF, %edx  # make abs
    movl %edx, %eax

    movl %edx, %ecx
    shrl $23, %ecx          # get exponent from %ecx
    andl $0xFF, %ecx

    movl %edx, %r8d
    andl $0x7FFFFF, %r8d    # get mantissa from %ecx

    cmpl $0xFF, %ecx        # check if it is NaN
    jne .NOTNAN
    testl %r8d, %r8d        # check if %r8d is 0 or not
    je .NOTNAN

    movl %edi, %eax
    ret                     # return the %edi
.NOTNAN:
    ret

# floatIsLess - Compute f < g for floating point arguments f and g.
#   Both the arguments are passed as unsigned int's, but
#   they are to be interpreted as the bit-level representations of
#   single-precision floating point values.
#   If either argument is NaN, return 0.
#   +0 and -0 are considered equal.
#   Rating: 3
.global floatIsLess
floatIsLess:
    movl %edi, %eax
    shrl $23, %eax
    andl $0xFF, %eax  # calculate exponent of %edi
    movl %edi, %ecx
    andl $0x7FFFFF, %ecx  # calculate mantissa of %edi
    cmpl $0xFF, %eax
    jne .UGNAN
    testl %ecx, %ecx
    jne .RET0
.UGNAN:
    movl %esi, %eax
    shrl $23, %eax
    andl $0xFF, %eax  # calculate exponent of %esi
    movl %esi, %ecx
    andl $0x7FFFFF, %ecx  # calculate mantissa of %esi
    cmpl $0xFF, %eax
    jne .CHECKSIGN
    testl %ecx, %ecx
    jne .RET0
.CHECKSIGN:
    movl %edi, %eax  # Check if both are zero
    movl %esi, %ecx
    sall $1, %eax             # take %eax without sign bit
    sall $1, %ecx             # take %ecx without sign bit
    testl %eax, %eax  # check if uf is positive
    jne .NEXT_CHECK
    testl %ecx, %ecx  # check if ug is positive
    jne .NEXT_CHECK
    jmp .RET0
.NEXT_CHECK:
    movl %edi, %eax  # Compare the sign
    movl %esi, %ecx
    shrl $31, %eax            # take sign bit
    shrl $31, %ecx            # take sign bit
    cmpl %ecx, %eax
    je .SAMESIGN
    cmpl $1, %eax     # if both are negatives
    je .RET1        # if ug is bigger
    jmp .RET0
.SAMESIGN:
    cmpl $1, %eax  # when both are negatives
    je .NEGATIVES
    cmpl %esi, %edi
    jl .RET1
    jmp .RET0
.NEGATIVES:
    cmpl %edi, %esi
    jl .RET1
    jmp .RET0
.RET0:
    movl $0, %eax
    ret
.RET1:
    movl $1, %eax
    ret


# isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
#   Example: isAsciiDigit(0x35) = 1.
#            isAsciiDigit(0x3a) = 0.
#            isAsciiDigit(0x05) = 0.
#   Rating: 3
.global isAsciiDigit
isAsciiDigit:
    movl %edi, %eax  # get parameter
    subl $0x30, %eax # check if %eax is less then 0x30
    movl %eax, %ecx  # move it to %ecx for bit shift
    sarl $31, %ecx   # get sign bit
    movl $0x39, %eax
    subl %edi, %eax  # check if %eax is greater then 0x39
    movl %eax, %edx
    sarl $31, %edx
    orl %ecx, %edx   # check if one of them are out of range (0x30 - 0x39)
    notl %edx        # convert 0 to 1, -1 to 0
    andl $1, %edx    # LSB
    movl %edx, %eax
    ret

# addOK - Determine if we can compute x+y without overflow
#   Example: addOK(0x80000000,0x80000000) = 0,
#            addOK(0x80000000,0x70000000) = 1,
#   Rating: 3
.global addOK
addOK:
    movl %edi, %eax
    addl %esi, %eax  # add two parameters
    movl %edi, %ecx  # move %edi to %ecx for bit shift
    sarl $31, %ecx   # get operator
    movl %esi, %edx  # move %esi to %edi for bit shift
    sarl $31, %edx
    movl %eax, %r8d  # save %eax in %r8d
    sarl $31, %r8d
    xorl %ecx, %edx  # operatorX ^ operatorY
    notl %edx        # !(operatorX ^ operatorY)
    xorl %ecx, %r8d  # operatorX ^ operatorSum
    andl %r8d, %edx  # sameOperator & changedOperator
    notl %edx
    andl $1, %edx    # LSB
    movl %edx, %eax
    ret

# isGreater - if x > y  then return 1, else return 0
#   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
#   Rating: 3
.global isGreater
isGreater:
    cmpl %esi, %edi          # check if x and y are same
    je .SAME                 # if same

    movl %edi, %eax
    movl %esi, %ecx
    sarl $31, %eax           # get sign bit
    sarl $31, %ecx
    andl $1, %eax            # LSB
    andl $1, %ecx

    movl %eax, %r8d          # save operator of x in %r8d
    movl %r8d, %edx
    xorl %ecx, %edx          # operatorX ^ operatorY
    movl %r8d, %r9d          # save value of %r8d into %r9d for bit shift
    xorl $1, %r9d            # !operatorX
    andl %ecx, %r9d          # If x is positive and y is negative, return 1
    movl %edi, %eax

    subl %esi, %eax          # x - y
    sarl $31, %eax           # get the operator of the %eax
    andl $1, %eax            # LSB
    xorl $1, %eax            # !operator of subtracted value

    movl %eax, %r10d
    movl %edx, %eax          # save %edx(different operator)
    andl %r9d, %eax
    xorl $1, %edx            # !differentOperator
    andl %r10d, %edx         # !differentOperator & !operatorSubtract
    orl %edx, %eax           # calaulate final result
    ret
.SAME:
    movl $0, %eax            # if x == y, return 0
    ret


# floatFloat2Int - Return bit-level equivalent of expression (int) f
#   for floating point argument f.
#   Argument is passed as unsigned int, but
#   it is to be interpreted as the bit-level representation of a
#   single-precision floating point value.
#   Anything out of range (including NaN and infinity) should return
#   0x80000000u.
#   Rating: 4
.global floatFloat2Int
floatFloat2Int:
    movl %edi, %eax
    movl %eax, %r9d  # move to %r9d for bit shift
    shrl $31, %r9d   # operator

    movl %eax, %edx
    shrl $23, %edx   # exponent
    andl $0xFF, %edx # get just exponent bit

    andl $0x7FFFFF, %eax # mantissa
    orl $0x800000, %eax       # mantissa with hidden bit

    cmpl $255, %edx
    je .OUT_OF_RANGE

    movl %edx, %r8d
    subl $127, %r8d  # -127 to get real exponent

    cmpl $0, %r8d    # return zero if real exponent is less than 0
    jl .ZERO

    cmpl $30, %r8d   # out of range if real exponent is greater than 30
    jg .OUT_OF_RANGE

    cmpl $23, %r8d
    jle .TORIGHT

    subl $23, %r8d
    movb %r8b, %cl
    shll %cl, %eax  # real mantissa >> (23 - real exponent)
    jmp .WITHSIGN
.TORIGHT:
    movl $23, %ecx  # real exponent - 23
    subl %r8d, %ecx
    movb %cl, %cl
    shrl %cl, %eax
    jmp .WITHSIGN
.WITHSIGN:
    testl %r9d, %r9d  # check if operator is equal to 1
    je .RET # return if it is positive value
    negl %eax  # change the opetrator if it is negative value
    jmp .RET
.ZERO:
    movl $0, %eax
    ret
.OUT_OF_RANGE:
    movl $0x80000000, %eax
    ret
.RET:
    ret

# absVal - absolute value of x
#   Example: absVal(-1) = 1.
#   You may assume INT_MIN <= x <= INT_MAX
#   Rating: 4
.global absVal
absVal:
    movl %edi, %eax
    movl %eax, %ecx # save the value for %eax
    sarl $31, %ecx  # get operator
    addl %ecx, %eax # x + operator
    xorl %ecx, %eax # (x + operator) ^ operator
    ret

