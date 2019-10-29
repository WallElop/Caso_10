#ifndef MATROID_H
#define MATROID_H
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

typedef void* dataType;
define_list(dataType)
typedef struct Matroid{
    List(dataType)*S;
    List(dataType)*I;
    bool (*function)();

}Matroid;

#endif // MATROID_H
