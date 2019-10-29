#include <stdio.h>
#include "library.h"
#include "matroidint.h"

int main()
{
    struct MatroidInt mInt = {
    {12,52,5,14,76,2,50,6,77,11,28,29,45,34,85},
    {},
    MatroidInt_w
    };
    if(!mInt.w(mInt.Ms[2])){
        mInt.Mi[2] = mInt.Ms[2];
        printf("%i", mInt.Mi[2]);
    }
}
