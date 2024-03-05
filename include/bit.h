#ifndef BIT_H
#define BIT_H
#include <stdbool.h>
// - - - - - - - - - -

/*
JUST SOMEBODY: This is how we will define a bit: a struct with just a boolean value of size 1 
Here is how we can use it:
int main()
{
    Bit myBit;
    myBit.value = 0; //Reset the bit
    myBit.value = 1; //Set the bit
}

If you give more than 1 as a value, the bit is considered set.
*/

typedef struct Bit
{
    bool value : 1;
} Bit;

// - - - - - - - - - - 
#endif //BIT_H
 
