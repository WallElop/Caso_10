#ifndef MATROID_H
#define MATROID_H
#include <stdio.h>
#include <stdbool.h>


typedef struct Matroid{
    int S[1];
    int I[1];
    bool (*function)();

}Matroid;

#endif // MATROID_H
