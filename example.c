/*
DO NOT USE THIS CODE IN ANYTYPE OF PROJECT(OFC YOUR NOT SO DUMB, ARE YOU!?)
NOT AT ALL OPTIMISED
[only int and float data type, for simplicity]
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
most probably, i have also used + - * and /, which i planned to replace
by functions written using bitwise operators and loop(or recursion)
*/
#include <stdio.h>
#include <math.h>
#include "bitoperations.h"

// =======================declarations=============================
void opearations_testing();
void mysmalltests();

//==========================main====================================

int main(){
    opearations_testing();
    // mysmalltests();
    return 0;
}

//==============================definitions============================

void mysmalltests(){
}

void opearations_testing(){
    char a, b;

    a = 67;
    printf("a = %d\n", a);
    printf("which in binary = ");
    print8b(a);
    printf("\n");
    a = -67;
    printf("a = %d\n", a);
    printf("which in binary = ");
    print8b(a);
    printf("\n");
    a = 0;
    printf("a = %d\n", a);
    printf("which in binary = ");
    print8b(a);
    printf("\n\n");

    a = -20;
    printf("a = %d\n", a);
    printf("here a is %s(%d)\n", (findsign(a)==-1 ? "negative": "non-negative"), findsign(a));
    a = 20;
    printf("a = %d\n", a);
    printf("here a is %s(%d)\n\n", (findsign(a)==-1 ? "negative": "non-negative"), findsign(a));

    a = 13, b = 14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a < b is %d\n", _islessthan_(a, b));
    a = -13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a < b is %d\n", _islessthan_(a, b));
    a = 13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a < b is %d\n", _islessthan_(a, b));
    a = -13, b = 14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a < b is %d\n\n", _islessthan_(a, b));

    a = -20;
    printf("a = %d\n", a);
    printf("here a is %s(%d)\n", (findsign2(a)==-1 ? "negative": (findsign2(a)==0? "zero": "positive")), findsign2(a));
    a = 0;
    printf("a = %d\n", a);
    printf("here a is %s(%d)\n", (findsign2(a)==-1 ? "negative": (findsign2(a)==0? "zero": "positive")), findsign2(a));
    a = 20;
    printf("a = %d\n", a);
    printf("here a is %s(%d)\n\n", (findsign2(a)==-1 ? "negative": (findsign2(a)==0? "zero": "positive")), findsign2(a));

    a = 13, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n", _isequalto_(a, b));
    a = -13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n", _isequalto_(a, b));
    a = 13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n", _isequalto_(a, b));
    a = 13, b = 14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n", _isequalto_(a, b));
    a = -14, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n", _isequalto_(a, b));
    a = 0, b = 0;
    printf("a = %d and b = %d\n", a, b);
    printf("here a == b is %d\n\n", _isequalto_(a, b));

    a = 13, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("here a and b are opposite in sign %d\n", _chackifoppsign_(a, b));
    a = -13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a and b are opposite in sign %d\n", _chackifoppsign_(a, b));
    a = 13, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a and b are opposite in sign %d\n", _chackifoppsign_(a, b));
    a = -13, b = 14;
    printf("a = %d and b = %d\n", a, b);
    printf("here a and b are opposite in sign %d\n", _chackifoppsign_(a, b));
    a = 0, b = -0;
    printf("a = %d and b = %d\n", a, b);
    printf("here a and b are opposite in sign %d\n\n", _chackifoppsign_(a, b));

    a = 10;
    printf("a = %d\n", a);
    printf("additive inverse of a = %d\n", addinverse(a));
    a = -10;
    printf("a = %d\n", a);
    printf("additive inverse of a = %d\n", addinverse(a));
    a = 0;
    printf("a = %d\n", a);
    printf("additive inverse of a = %d\n\n", addinverse(a));

    a = 10;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n", abswb(a));
    a = -10;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n", abswb(a));
    a = 0;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n\n", abswb(a));

    a = -123;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n", abswtb(a));
    a = 123;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n", abswtb(a));
    a = 0;
    printf("a = %d\n", a);
    printf("absolute value of a = %d\n\n", abswtb(a));

    a = 12, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n", _add_carry(a, b, 0));
    printf("a + b + 1 is equal to %d\n", _add_carry(a, b, 1));
    a = -13, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n", _add_carry(a, b, 0));
    printf("a + b + 1 is equal to %d\n", _add_carry(a, b, 1));
    a = -13, b = -23;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n", (char)_add_carry(a, b, 0));
    printf("a + b + 1 is equal to %d\n\n", (char)_add_carry(a, b, 1));

    a = 12, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n", add(a, b));
    a = -13, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n", add(a, b));
    a = -13, b = -23;
    printf("a = %d and b = %d\n", a, b);
    printf("a + b is equal to %d\n\n", (char)add(a, b));

    a = 1, b = -1;
    printf("a = %d and b = %d\n", a, b);
    printf("a * b is equal to %d\n", (char)multiply(a, b));
    a = 7, b = 13;
    printf("a = %d and b = %d\n", a, b);
    printf("a * b is equal to %d\n", multiply(a, b));
    a = 6, b = -14;
    printf("a = %d and b = %d\n", a, b);
    printf("a * b is equal to %d\n\n", (char)multiply(a, b));

    a = 1, b = -1;
    printf("a = %d and b = %d\n", a, b);
    swap8b(&a, &b);
    printf("swaping a and b we get a = %d and b = %d\n", a, b);
    a = 7, b = 13;
    printf("a = %d and b = %d\n", a, b);
    swap8b(&a, &b);
    printf("swaping a and b we get a = %d and b = %d\n", a, b);
    a = 6, b = -14;
    printf("a = %d and b = %d\n", a, b);
    swap8b(&a, &b);
    printf("swaping a and b we get a = %d and b = %d\n\n", a, b);

    typedef struct{
        int x;
        int y;
        char z[10];
    } S;
    S p = {1, 2, "hello"};
    S q = {-1, -2, "world"};
    printf("sizeof S = %d\n", sizeof(S));
    printf("p contains {%d, %d, %s}\n", p.x, p.y, p.z);
    printf("q contains {%d, %d, %s}\n", q.x, q.y, q.z);
    worstswap(&p, &q, sizeof(S));
    printf("after swap p contains {%d, %d, %s}\n", p.x, p.y, p.z);
    printf("after swap q contains {%d, %d, %s}\n\n", q.x, q.y, q.z);

    a = 10, b = 12;
    printf("a = %d and b = %d\n", a, b);
    printf("if a is 10 print 12 is %d\n", _ternary_(_isequalto_(a, 10), 12, 0));
    a = 10, b = 12;
    printf("a = %d and b = %d\n", a, b);
    printf("if a is 12 print 12 is %d\n\n", _ternary_(_isequalto_(a, 12), 12, 0));
    return;
}
