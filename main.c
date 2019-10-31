#include <stdio.h>
#include "matroid.h"
#include <stdbool.h>
#include <ctype.h>
#include "library.h"

typedef char* string;
define_list(int)
define_list(bool)
define_list(string)

bool functionA(int x){
    if(x>0){
        return true;
    }else{
        return false;
    }
}

bool functionB(bool x){
    if(x == false){
        return true;
    }else{
        return false;
    }
}

bool functionC(string x){
    if(x != "Josue"){
        return true;
    }else{
        return false;
    }
}




int main(){

//    printf("%f\n", 3.23456);

    List(int) *l1 = new_list(int);
    insert(l1,3);
    insert(l1,3);
    insert(l1,1);
    insert(l1,2);
    insert(l1,9);

    List(bool) *l2 = new_list(bool);
    insert(l2,true);
    insert(l2,false);
    insert(l2,false);
    insert(l2,false);
    insert(l2,true);

    List(string) *l3 = new_list(string);
    insert(l3,"Walter");
    insert(l3,"Eduard");
    insert(l3,"Josue");
    insert(l3,"Lopez");
    insert(l3,"Molinares");

    Matroid matroid = {.S = l1, .I = new_list(int) , .function = functionA };
    Matroid matroid2 = { .S = l2,.I = new_list(bool), .function = functionB };
    Matroid matroid3 = {.S = l3, .I = new_list(string), .function = functionC};

    Matroid matroids[] = {matroid, matroid2, matroid3};

    int tamanioArreglo = sizeof (matroids)/sizeof (matroids[0]);
    printf("Opcion A)\n");
    optionA(matroids, tamanioArreglo);


    List(int) *l4 = new_list(int);
    insert(l4,3);
    insert(l4,3);
    insert(l4,1);
    insert(l4,2);
    insert(l4,9);

    List(int) *l5 = new_list(int);
    insert(l5,1);
    insert(l5,3);
    insert(l5,-3);
    insert(l5,4);
    insert(l5,5);

    List(int) *l6 = new_list(int);
    insert(l6,3);
    insert(l6,2);
    insert(l6,1);
    insert(l6,-4);
    insert(l6,-7);

    List(int) *l7 = new_list(int);
    insert(l7,9);
    insert(l7,-3);
    insert(l7,3);
    insert(l7,1);
    insert(l7,5);

    List(int) *l8 = new_list(int);
    insert(l8,3);
    insert(l8,-2);
    insert(l8,1);
    insert(l8,-9);
    insert(l8,7);

    Matroid matroid4 = {.S = l4, .I = new_list(int) , .function = functionA };
    Matroid matroid5 = {.S = l5,.I = new_list(int), .function = functionA };
    Matroid matroid6 = {.S = l6, .I = new_list(int), .function = functionA };
    Matroid matroid7 = {.S = l7,.I = new_list(int), .function = functionA };
    Matroid matroid8 = {.S = l8, .I = new_list(int), .function = functionA };

    Matroid matroids2[] = {matroid4, matroid5, matroid6, matroid7, matroid8};

    int tamanioArreglo2 = sizeof (matroids2)/sizeof (matroids2[0]);
    printf("\n\n\nopcion B)\n");
    optionB(matroids2, tamanioArreglo2);

    printf("Hello World!\n");


    return 0;
}
