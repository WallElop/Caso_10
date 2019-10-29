#ifndef MATROID_H
#define MATROID_H
#include <stdio.h>
#include <stdbool.h>


typedef struct Matroid{
    int S[5];
    int I[5];
    bool (*function)();

}Matroid;

#endif // MATROID_H
