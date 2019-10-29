#ifndef MATROIDINT_H
#define MATROIDINT_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
struct MatroidInt{
    int Ms[15];
    int Mi[15];
    bool (*w)(int);
};

bool MatroidInt_w(int x){
    return (x%2==0);
}
#endif // MATROIDINT_H
