// Based on Bryant and O'Halloran's original "datalab" assignment

#if 0

STEP 1: Read the following instructions carefully.

You will provide your solution to this part of the project by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function.

  Each expression in your code can use ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xFFFFFFFF.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  You are not restricted to one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operators, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int. This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses twos complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.

FLOATING POINT CODING RULES

  For the problems that require you to implement floating-point operations,
  the coding rules are less strict.  You are allowed to use looping and
  conditional control.  You are allowed to use both int and unsigned variables.
  You can use arbitrary integer and unsigned constants. You can use any arithmetic,
  logical, or comparison operations on int or unsigned data.

  You are expressly forbidden to:
    1. Define or use any macros.
    2. Define any additional functions in this file.
    3. Call any functions.
    4. Use any form of casting.
    5. Use any data type other than int or unsigned.  This means that you
       cannot use arrays, structs, or unions.
    6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the ndlc program (described in the spec) to check the legality of
     your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function. The max operator count is checked by ndlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the spec and in this file, consider
     this file the authoritative source.

STEP 2: Modify the following functions according the coding rules.

IMPORTANT. TO AVOID GRADING SURPRISES:
  1. Use the ndlc tool to check that your solutions conform to the coding rules.

YOU WILL RECEIVE NO CREDIT IF YOUR CODE DOES NOT PASS THIS CHECK.

  2. Run the provided tests to check that your solutions achieve the
     desired results.

#endif

/*
 * isZero - returns 1 if x == 0, and 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
    return !x;
}

/*
 * bitNor - Compute ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    return ~x & ~y;
}

/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
    return x & (~x + 1);
}

/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    return (x << 31) >> 31;
}

/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
    return !!(x ^ (~x + 1));
}

/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
    // claculate absolute value, bit of exponent, mantissa
    unsigned absVal = uf & 0x7FFFFFFF;
    unsigned exponent = absVal >> 23;
    unsigned mantissa = absVal & 0x7FFFFF;
    // Checking NaN value
    unsigned isMaxExp = !(exponent ^ 0xFF);
    // unsigned isNonZeroMantissa = (mantissa | (~mantissa + 1)) >> 31;
    unsigned isNonZeroMantissa = !(!(mantissa));
    if (isMaxExp & isNonZeroMantissa) {
        return uf;
    } else {
        return absVal;
    }
}
/*
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
    // operator, exponent, mantissa of uf
    unsigned operatorF = (uf >> 31) & 1;
    unsigned exponentF = (uf >> 23) & 0xFF;
    unsigned mantissaF = uf & 0x7FFFFF;
    // check if uf is NaN
    unsigned isNanF = 0;
    if (exponentF == 0xFF && mantissaF != 0) {
        isNanF = 1;
    }

    // operator, exponent, mantissa of ug
    unsigned operatorG = (ug >> 31) & 1;
    unsigned exponentG = (ug >> 23) & 0xFF;
    unsigned mantissaG = ug & 0x7FFFFF;
    // check if ug is NaN
    unsigned isNanG = 0;
    if (exponentG == 0xFF && mantissaG != 0) {
        isNanG = 1;
    }
    if (isNanF | isNanG) {    // return 0 is either of one is NaN
        return 0;
    }
    if ((exponentF == 0) && (exponentG == 0) && (mantissaF == 0) &&
        (mantissaG == 0)) {    // return 0 if -0 or 0
        return 0;
    }
    if (operatorF > operatorG) {    // when uf is smaller
        return 1;
    } else if (operatorF < operatorG) {    // when uf is bigger
        return 0;
    }
    if (operatorF == 0) {    // when uf and ug are positive value
        return uf < ug;
    }
    return uf > ug;
}

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int lower = x + (~0x30 + 1);
    int upper = 0x39 + (~x + 1);
    return !(lower >> 31) & !(upper >> 31);
}

/*
 * addOK - Determine if we can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    int sum = x + y;
    // operator of x and y
    int operatorX = x >> 31;
    int operatorY = y >> 31;
    int operatorSum = sum >> 31;    // operator of sum
    return !((!(operatorX ^ operatorY)) &
             (operatorX ^ operatorSum));    // checkinfg if operator had changed after sum
}

/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    // get operator for x
    int operatorX = (x >> 31) & 1;
    int operatorY = (y >> 31) & 1;
    int isSame = !(x ^ y);                         // check if x and y are same
    int checkSign = operatorX ^ operatorY;         // check if operator are different
    int isXPositive = (!operatorX) & operatorY;    // If x is positive and y is negative, return 1
    int subtract = x + (~y + 1);
    int operatorSubtract = (subtract >> 31) & 1;
    // x, y are not the same and x < y
    return (!isSame) & ((checkSign & isXPositive) | ((!checkSign) & (!operatorSubtract)));
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    // get operator, exponent, mantissa from uf
    unsigned operator=(uf >> 31) & 1;
    unsigned exponent = (uf >> 23) & 0xFF;
    unsigned mantissa = uf & 0x7FFFFF;

    if (exponent == 255) {    // if value for exponent is out of range
        return 0x80000000u;
    }
    int realExponent = exponent - 127;          // subtract bias
    int realMantissa = mantissa | (1 << 23);    // make mantissa with hidden value
    if (realExponent < 0) {
        return 0;
    }
    if (realExponent > 30) {    // check again exponent is out of range
        return 0x80000000u;
    }
    int result = 0;
    if (realExponent > 23) {    // when exponent is bigger than 23
        result = realMantissa << (realExponent - 23);
    } else if (realExponent < 23) {    // when exponent is smaller than 23
        result = realMantissa >> (23 - realExponent);
    }
    if (operator== 1) {    // switch the result to negative
        result = ~result + 1;
    }
    return result;
}

/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume INT_MIN <= x <= INT_MAX
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    int operator= x>> 31;    // when x is negative number, operator is going to be -1
    return (x + operator) ^ operator;
}
