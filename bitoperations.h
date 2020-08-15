/*
DO NOT USE THIS CODE IN ANYTYPE OF PROJECT(OFC YOUR NOT SO DUMB, ARE YOU!?)
NOT AT ALL OPTIMISED
[only char for simplicity]
this code base is nothing but for fun with bit manupulations, much of the write-ups
are from this website: https://graphics.stanford.edu/~seander/bithacks.html
which i found really fun, and though about trying it out myself
some basics:
"// to provide decimal numbers in variables write
int a = 10;     // thats simple
// to provide hexadecimal numbers
int a = 0xA;    // Yesh
// to provide octal numbers
int a = 012;    // ik yah can't convert that one
// to provide binary we write
int a = 0b110;  // easy
anyway, as this is all 'bout bit manipulations so, binary!"
this is only for reference, as i was not able to make out how to make a number
binary.
according to wikipedia, the basic bitwise opeators are:
& : bitwise AND
| : bitwise OR
^ : bitwise XOR(exclusive OR)
<< : left shift
>> : right shift
~ : bitwise NOT
here, i tried my best to write all code using these bitwise operators.
most probably, i have also used + - * and /, which i planned to replace even branching
by functions written using bitwise operators and loop(or recursion)

* as we have equal to and less than, we can make any other with playing
  with these configurations so no, <= or > or >= or !=
*/

#include <stdio.h>

#define CHAR_BIT 8  // this is the number of bits in a char(C)(i.e. in a byte)

// writing in hexa-decimal would have been better,
// check: https://stackoverflow.com/a/3208376
#define BYTE_TO_BINARY_FLAG "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
    (byte & 0b10000000? '1': '0'), \
    (byte & 0b01000000? '1': '0'), \
    (byte & 0b00100000? '1': '0'), \
    (byte & 0b00010000? '1': '0'), \
    (byte & 0b00001000? '1': '0'), \
    (byte & 0b00000100? '1': '0'), \
    (byte & 0b00000010? '1': '0'), \
    (byte & 0b00000001? '1': '0') \

//==========================declarations============================

// basics
// all based on 8-bit manupulation
void print8b(unsigned char byte);
char findsign(char num);
unsigned char _islessthan_(char left, char right);
char findsign2(char num);
unsigned char _isequalto_(char left, char right);
unsigned char _chackifoppsign_(char left, char right);
char addinverse(char num);
unsigned char abswb(char num);
unsigned char abswtb(char num);
unsigned char _add_carry(unsigned char left, unsigned char right, unsigned char carry);
unsigned char add(unsigned char left, unsigned char right);
unsigned char multiply(unsigned char left, unsigned char right);
void swap8b(unsigned char* a, unsigned char* b);
unsigned char _ternary_(unsigned char a, unsigned char b, unsigned char c);

// dependent on the above functions
void worstswap(void* a, void* b, unsigned int size);

//===========================definitions==============================

// print 8 bits 
void print8b(unsigned char byte){
    printf(BYTE_TO_BINARY_FLAG" ", BYTE_TO_BINARY(byte));
}

// find the sign of the given number
// returns -1 for negative, 0 for otherwise
// this function can also be used as (a < 0)
char findsign(char num){
    char sign;

    // this is the most straight forward method
    // -1 for negative, 0 for otherwise
    // sign = -(a < 0)
    // but the next one is even better, cause it doesn't use any logical operator

    // here, we take the last bit of the whole byte i.e. the 8th bit
    // cause thats what decides, if the number is negative or non-negative
    // returns -1 for negative, 0 for otherwise
    sign = ((num) >> (sizeof(num) * CHAR_BIT - 0b00000001));

    return sign;
}

// find whether "left < right"
// return 1 if true
// return 0 if false
unsigned char _islessthan_(char left, char right){
    // if left < right
    // that means (left - right) < 0
    left = left - right;

    // now check the sign of left
    return addinverse(findsign(left));
}

// this can be more usefull 
// find sign the other way
// returns +1 if positive, 0 if 0, and -1 if negative
char findsign2(char num){
    char sign;

    // sign = (0 < a) - (a < 0)
    // if a is greater than 0, sign = 1 - 0 = +1
    // if a is equal to 0, sign = 0 - 0 = 0
    // if a is smaller than 0, sign = 0 - 1 = -1
    sign = _islessthan_(0b0, num) - _islessthan_(num, 0b0);
    return sign;
}

unsigned char _isequalto_(char left, char right){
    // if (a == b), ie. ((a-b) == 0)
    left = left - right;

    unsigned char sign = findsign2(left);

    // now "sign" can get one of 3 numbers from findsign2
    // 11111111(-1) or
    // 00000000(0) or
    // 00000001(+1)
    // here we can see the first bit is something we have to take care of
    // as we want -1 and 1 to give 0(false) result, 0 to give 1(true)
    sign = 0b00000001 & sign; // this is obsolute
    // now invert it and get the 1st bit
    // if sign = ~00000000 -> 111111111 & 0b1(00000001) -> 00000001
    // if sign = ~00000001 -> 111111110 & 0b1(00000001) -> 00000000
    // and get the first bit
    // it gives us 1(when a == b, a-b == 0) or 0(a != b)
    sign = ~sign & 0b00000001; 
    /*
        IMPORTANT:
        the best way is to directly execute "sign = ~sign & 0b00000001;"
        here "sign = 0b00000001 & sign;" is obsolute(only for understanding, ig)
    */

    return sign;
}

// checks whether left and right are opposite in signs
// if true then it returns 1
// else 0 is returned
unsigned char _chackifoppsign_(char left, char right){
    // if the signs are opposite then xor of the 8th bit
    // will give 1, for example: 10000000 ^ 00000000 = 10000000
    // if the signs are same then xor of the 8th bit will give
    // 0
    left = left ^ right;
    // now left shift the value
    // as left is signed so left shift will
    // led to -1 to cope with that - is put infront of that
    // cause we need +1 when true not -1
    // and if left's 8th bit is 0 then the result will be zero
    // and the - is ignored
    left = addinverse(left >> (sizeof(char) * CHAR_BIT - 1));
    return left;
}

// changes the sign of the given number
// find the additive inverse of the given number
char addinverse(char num){
    // observe:
    // 2 in binary is   0b00000010
    // -2 in binary is  0b11111110
    // so if num is 2
    // then much of the bits(3th to 8th) can be convert by
    // performing bitwise not, which gives
    // ~2 = ~(0b00000010) = 0b11111101
    // now this result can be added by +1 to get -2
    // i.e. ~2 + 1 = 0b11111101 + 0b00000001 = 0b11111110
    // which is -2 in decimal
    // same can be done for negative signed numbers
    // idk, this didn't came to me intuitively,
    // it was with observation with trail and error
    // that i was able to reach this result
    // ig i'm just too dumb to get it intuitively
    // num = ~num + 1;
    num = ~num + 1;
    return num;
}

// read */as "abs with branching"
// i.e. to find the absolute value 
// conditional statements are used
// returns the absolute value
unsigned char abswb(char num){
    // if num is negative return -num else return the same number
    // return _islessthan_(num, 0) ? addinverse(num): num;
    // now that i have ternery operator
    return _ternary_(_islessthan_(num, 0), addinverse(num), num);
}

// read as "abs without branching"
// i.e. to find the absolute value without any
// conditional statements.
// returns the absolute value
unsigned char abswtb(char num){
    // first find the sign
    char const sign = findsign(num);
    unsigned char result;
    // if num is negative
    // then sign = 0b11111111
    // then (num ^ sign) is nothing but ~num 
    // now adding -sign i.e. -(-1) => +1
    // which is (~num + 1)
    // and when num is positive
    // sign = 0b00000000
    // then (num ^ sign) is num
    // now subtracting sign(which is 0) will also led to numk+
    result = (unsigned char)((num ^ sign) - sign);
    return result;
}

// not at all recommended
// adding two number, with a default carry
// in character adding it might not be that of usefull
// but when we add more than 1 byte data types
// it might get used
// just speculating
unsigned char _add_carry(unsigned char left, unsigned char right, unsigned char carry){
    // carry can be 0 or 1
    // this gives us carry 1 if negative or positive
    // else carry is 0
    carry = abswtb(findsign2(carry));
    unsigned char ptr;  // the pointer that points to which bit is being added
    ptr = 0b00000001;   // default to 1, i.e. pointing first bit, 
                        // 'cause that is what wiil be added first
    unsigned char result = 0b00000000;
    while(ptr){
        result = (result | (ptr & (left ^ right ^ carry)));
        carry = ptr & ((left & right) | (left & carry) | (right & carry));
        ptr = ptr << 1;
        carry = carry << 1;
    }
    return result;
}

// uses _add_carry where carry is 0
unsigned char add(unsigned char left, unsigned char right){
    return _add_carry(left, right, 0);
}

// not at all recommended
// multiplies two numbers
unsigned char multiply(unsigned char left, unsigned char right){
    unsigned char result = 0b00000000;
    unsigned char counter = 0;
    unsigned char ptr = 0b00000001;
    unsigned char bit;  // stores what bit of right at ptr 
    while(ptr){
        bit = (ptr & right) >> counter;
        if(bit)
            result = add(result, (left << counter));
        counter = add(counter, 1);
        ptr = ptr << 1;
    }
    return result;
}

// swaps values using xor swap
// only for 8-bit values
void swap8b(unsigned char* a, unsigned char* b){
    if(_isequalto_(*a, *b))
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// returns b if a is true
// else returns c
unsigned char _ternary_(unsigned char a, unsigned char b, unsigned char c){
    // first convert a to true if 1, i.e. convert to (0b00000001 -> 0b11111111)
    // if 0 don't convert
    // if a  is equal to zero, returns true
    // i.e. converted to false, i.e. 1
    // now that is converted to -1
    // for better calculation afterwards
    // a may be a number instead of a bit, for example 10 is a valid true statement in 10?b:c, here!
    // thats the reason it is converted
    a = addinverse(!_isequalto_(a, 0));

    // if a is true then it is converted to -1 ie. 0b11111111 above
    // this is now used to check here, if a is -1 then b is returned
    // as 0b11111111 & b = b
    // and ~0b11111111 & c = 0b00000000 & c = 0b00000000(i.e. c is not choosen)
    // but if a is 0 vice-versa.
    return (a & b) | (~a & c);
}

//==============================for expanded bits(more than 8)=================================

// this is not at all optimised
// so don't use
// swap values upto size of (2**(sizeof(int) * 8) - 1) bytes 
void worstswap(void* a, void* b, unsigned int size){
    // get the array of 8-bits
    // for example, if a is int
    // the [-------- -------- -------- --------]
    // will convert to [--------], [--------], [--------], [--------]
    // x will have 4 array of 8-bits of a
    unsigned char* x = (unsigned char*)(a);
    unsigned char* y = (unsigned char*)(b);
    // now swap the bits one by one
    while (size)
    {
        size = add(size, addinverse(1));
        swap8b(&x[size], &y[size]);
    }
}