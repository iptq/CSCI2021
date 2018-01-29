/* 
 * CS:APP Data Lab 
 * 
 * Michael Zhang <zhan4854@umn.edu>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  /** xor = (!x & y) | (x & !y) by definition.
      i'll use two variables, one for the first and one for the second
      and then OR the two at the end. but since OR isn't allowed, we can
      do a bit of manipulation with demorgan's laws to emulate OR:
        x | y
      = !(!x & !y)
    */
  int a = x & (~y);
  int b = (~x) & y;
  return ~(~a & ~b);
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void)
{
  /** even bits looks something like ...101010101010
      one way to construct this is starting with 8 bits and
      then bitshifting + ORing the result so it would look like:
      bits =                         10101010
      bits =                 1010101010101010
      bits = 10101010101010101010101010101010 <-- final answer
    */
  int bits = 85;
  bits |= (bits << 8);
  bits |= (bits << 16);
  return bits;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x)
{
  /** this REALLY short (clean) method relies on the fact that
      if we're looking for the least significant 1, then everything
      after it is a 0. take the example number:
          96 = 01100000
      looking at the operations that are available, i first try
      comparing it against its complement:
             = 10011111
      and the solution that we want:
             = 00100000
      if we want the smallest digit, we could add 1 to ~x, and it
      would push the one into the next digit, which is the smallest
      digit of x with a 1 (does that make sense?) as long as there
      is a 1 in that position, it doesn't matter what all the other
      digits are, we can just AND the two numbers and the zeros in
      x will automatically zero out all the unnecessary 1s in ~x

      phew
    */
  return x & (~x + 1);
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y)
{
  /** a property of ~x is that x + ~x will always equal -1. (well,
      i knew this before but it can be easily verified) using this
      property, we can simply test if
        (x + ~x) = -1
        (x + ~x) + 1 = 0 (since we can't use - or large numbers)
      then, in order to turn this into 0 or 1, i take advantage of
      the ! operator. 0 -> 1 and anything except 0 -> 0. since i want
      (x + ~x + 1) to be 0, i will just ! it
    */
  // return !(x + ~y + 1);
  /** wow i did it the hard way
      forgot about ^
    */
  return !(x ^ y);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
  int s = 32 + (~n + 1);
  int xprime = (x << s) >> s;
  return !(xprime ^ x);
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x)
{
  /** i noticed that this problem has a rather high "max ops" count,
      so i just took the most straightforward approach: just taking
      the int byte-by-byte and then appending it to a "result" variable
      in reverse order (had to do it this specific way because 255
      integer limit)
    */
  int byte = 255;
  int result = x & byte;
  byte <<= 8;
  result = (result << 8) | ((x & byte) >> 8 & 255);
  byte <<= 8;
  result = (result << 8) | ((x & byte) >> 16 & 255);
  byte <<= 8;
  result = (result << 8) | ((x & byte) >> 24 & 255);
  return result;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
  /** the most important thing in determining whether it's positive
      is the MSB. so i AND x with 0x10000... to extract its MSB and
      ! it (since if it's nonzero, then it is NOT positive.) but zero
      would also count as positive, which it apparently isn't, so we
      add the extra condition !!x, which would AND it with 0 if x is 0
    */
  return !(x & (1 << 31)) & !!x;
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 134217728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x)
{
  /** to multiply by 5, i'm just doing 4x + x, or (x << 2) + x, and
      then, to divide by 8, i'm using the method with rounding to divide
      by 2 ** 3:
        if it's positive, then just do x >> 3
        if it's negative, then compute (x + 2^3 - 1) / 2^3
      i used (x >> 31) to perform the conditional
    */
  int x5 = (x << 2) + x;
  int neg = x5 >> 31;
  int x8 = (neg & ((x5 + 7) >> 3)) | (~neg & (x5 >> 3));
  return x8;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  /** checking several things here, x <= y if:
        1. x is negative and y is positive (automatically pass)
        2. x is positive or y is negative but (y - x) is positive
        3. x == y
  */
  int diff = (~x + 1) + y;
  int xsign = (x >> 31) & 1;
  int ysign = (y >> 31) & 1;
  // printf("Diff: 0x%08x %d\n", diff, diff);
  return (xsign & !ysign) | (!ysign | xsign) & !((diff >> 31) & 1) | !(x ^ y);
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x)
{
  /** basically shifting it to the right in a compounding
      manner, so as long as one of them is set to 1, the
      LSB will eventually be set to 1. then just flip the 
      LSB with XOR.
    */
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return (x & 1) ^ 1;
}
/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x)
{
  /** the biggest problem here is to deal with whether or not x
      is negative as a conditional, but without using ifs or
      logical statements. the solution is to create either 11111...
      representing true or 00000... representing false, and then
      ANDing that with the respective outcome. the way i created
      this was with (~neg + 1). an alternative method (but using
      the same amount of ops is (neg << 31) >> 31)

      so that last line might as well read something like:
        if (neg) {
          return ((~x + 1) | msb);
        } else {
          return x;
        }
      where (~x + 1) is for the magnitude of the negative number
      and (1 << 31) is creating the sign.
    */
  int msb = (1 << 31);
  int neg = !!(x & msb);
  return ((~neg + 1) & ((~x + 1) | msb)) | ((~!neg + 1) & x);
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x)
{
  /** first check the first 16 bits, then the next 8 bits, and so
      on, and at each step, if it's not all 1s, then copy it down

      that was the original strategy, but it took way too many op-
      erations, so i decided to switch it up a bit. i noticed 
      that the line where it checks if it's all 1s took too many
      operations, so i started off inverting the number and then
      checking if it was all 0s, which took less operators
  */
  /*
  int check = (~0) << 16;
  int count = 0;
  int actual = x & check;
  int works = ((!(actual ^ check)) << 31) >> 31;
  count += (works & 16);
  x = (works & x) | (~works & (actual >> 16));
  // printf("%x\n", x);
  
  check = 0xff << 8;
  actual = x & check;
  works = ((!(actual ^ check)) << 31) >> 31;
  count += (works & 8);
  x = (works & x) | (~works & (actual >> 8));
  
  check = 0xf0;
  actual = x & check;
  works = ((!(actual ^ check)) << 31) >> 31;
  count += (works & 4);
  x = (works & x) | (~works & (actual >> 4));
  
  check = 0xc;
  actual = x & check;
  works = ((!(actual ^ check)) << 31) >> 31;
  count += (works & 2);
  x = (works & x) | (~works & (actual >> 2));
  
  check = 3;
  actual = x & check;
  works = ((!(actual ^ check)) << 31) >> 31;
  count += (works & 1);
  x = (works & x) | (~works & (actual >> 1));
  
  check = 1;
  count += (x & check);
  return count;*/
  int negone = ~0;
  int y = ~x;
  int check = ~0 << 16;
  int actual = y & check;
  int works = !actual + negone;
  int count = ~works & 16;
  // printf("Stage 1: %08x\n", y);
  y >>= works & 16;

  check = 0xff << 8;
  actual = y & check;
  works = !actual + negone;
  count += ~works & 8;
  // printf("Stage 2: %08x\n", y);
  y >>= works & 8;

  check = 0xf0;
  actual = y & check;
  works = !actual + negone;
  count += ~works & 4;
  // printf("Stage 3: %08x\n", y);
  y >>= works & 4;

  check = 0xc;
  actual = y & check;
  works = !actual + negone;
  count += ~works & 2;
  // printf("Stage 4: %08x\n", y);
  y >>= works & 2;

  check = 2;
  actual = y & check;
  works = !actual + negone;
  count += ~works & 1;
  // printf("Stage 5: %08x\n", y);
  y >>= works & 1;

  // printf("Stage 6: %08x\n", y);
  count += !y;

  // printf("Count: %d\n\n", count);
  return count;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf)
{
  /** first check if uf is nan by checking if the 8 exponent bytes
      is maxed out and the fractional part is greater than 0. this can
      be achieved by checking if uf is greater than 2139095040, which
      is 255 << 23. note that i have to AND uf by unsigned -1, in order
      to ignore the sign bit.

      then, all that's left is to flip the sign bit by XORing with 
      (1 << 31) which is the final bit.
    */
  int isnan = (uf & ~(1 << 31)) > (0xff << 23);
  if (isnan)
  {
    return uf;
  }
  else
  {
    return uf ^ (1 << 31);
  }
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf)
{
  /** case-bashing with rounding, with 0x00800000 as a "special"
      case (where it changes from normalized to denormalized)
  */
  int sign = uf & (1 << 31);
  int exp = (uf >> 23) & 0xff;
  int mantissa = uf & ((1 << 23) - 1);
  int rounding = !((mantissa & 3) ^ 3);

  // printf("0x%02x 0x%06x\n", exp, mantissa);
  if (exp == 0xff)
  {
    // printf("case 1\n");
    return uf;
  }
  if (exp <= 1)
  {
    if (exp == 1)
    {
      // SPECIAL CASE
      mantissa |= (1 << 23);
    }
    // printf("case 2\n");
    return (sign | (mantissa >> 1)) + rounding;
  }
  // printf("case 4\n");
  return sign | ((exp - 1) << 23) | mantissa;
}
