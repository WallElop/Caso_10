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
    for(int posInS=0; posInS<matroid.S->_size; posInS++){
        printf("%d\n", get(matroid.S,posInS));
        if(matroid.function(get(matroid.S,posInS))){
            insert(matroid.I,get(matroid.S,posInS));
        }
    }
    return matroid;
}



void evaluateMatroids(Matroid matroids[], int pSize){
    #pragma omp parallel
    #pragma omp for
    for(int posInMatroids = 0; posInMatroids<pSize; posInMatroids++){
        matroids[posInMatroids] = evaluateMatroid(matroids[posInMatroids]);
        showMatroid(matroids[posInMatroids]);
    }
    return ;

}

bool search(Matroid pMatroid, void* pTarget){
    #pragma omp parallel
    #pragma omp for
    for(int posInI = 0; posInI<pMatroid.S->_size ; posInI++){
        if(get(pMatroid.I, posInI) == pTarget){
            return true;
        }
    }
    return false;
}

void intersection(Matroid *pConjunto, Matroid pMatroid2){
    #pragma omp parallel
    #pragma omp for
    for (int posInIMatroid1 = 0; posInIMatroid1<pConjunto->I->_size; posInIMatroid1++ ) {
        if(!(search(pMatroid2, get(pConjunto->I,posInIMatroid1)))){
            insert(pConjunto->I, get(pConjunto->I,posInIMatroid1));
        }
    }
}

void B(Matroid matroids[], int pSize){
    evaluateMatroids(matroids, pSize);
    Matroid *conjunto;
    conjunto->I = matroids[0].I;
    #pragma omp parallel
    #pragma omp for
    for (int posInMatroids = 1; posInMatroids<pSize; posInMatroids++){
        intersection(conjunto, matroids[posInMatroids]);
    }

    Matroid matroid;
    matroid.I = conjunto->I;
    showMatroid(matroid);

}


int main(){

    printf("%f\n", 3.23456);

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

    evaluateMatroids(matroids, tamanioArreglo);

    printf("Hello World!\n");


    return 0;
}
