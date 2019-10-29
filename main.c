#include <stdio.h>
#include "matroid.h"
#include <stdbool.h>

define_list(int)
define_list(bool)

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

void showMatroid(Matroid matroid){
    printf("entro en imprimir\n");
    for(int posInI = 0; posInI<matroid.I->_size; posInI++){
        printf("%d\n", get(matroid.I,posInI));
    }
}

Matroid evaluateMatroid(Matroid matroid){
    printf("Entro en evaluar matroid!\n");
    #pragma omp parallel
    #pragma omp for

    printf("%d\n",matroid.S->_size);
    for(int posInS=0; posInS<matroid.S->_size; posInS++){
        printf("%d\n", get(matroid.S,posInS));
        if(matroid.function(get(matroid.S,posInS))){
            printf("Es mayor a 0\n");
            insert(matroid.I,get(matroid.S,posInS));
        }
    }
    return matroid;
}


void evaluarMatroids(Matroid matroids[], int pSize){
    #pragma omp parallel
    #pragma omp for
//    printf("Va a evaluar los matroids\n");

    for(int posInMatroids = 0; posInMatroids<pSize; posInMatroids++){
        matroids[posInMatroids] = evaluateMatroid(matroids[posInMatroids]);
        showMatroid(matroids[posInMatroids]);
    }
    return ;

}


int main(){

    List(int) *l1 = new_list(int);
    insert(l1,3);
    insert(l1,-3);
    insert(l1,1);
    insert(l1,-2);
    insert(l1,-9);

    List(bool) *l2 = new_list(bool);
    insert(l2,true);
    insert(l2,false);
    insert(l2,false);
    insert(l2,false);
    insert(l2,true);

    Matroid matroid = {.S = l1, .I = new_list(int) , .function = functionA };
    Matroid matroid2 = { .S = l2,.I = new_list(bool), .function = functionB };

    Matroid matroids[] = {matroid, matroid2};
    int tamanioArreglo = sizeof (matroids)/sizeof (matroids[0]);

    evaluarMatroids(matroids, tamanioArreglo);

    printf("Hello World!\n");

    return 0;
}
