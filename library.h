#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "matroid.h"

void showMatroid(Matroid matroid){
    printf("entro en imprimir\n");
    for(int posInI = 0; posInI<matroid.I->_size; posInI++){
        void *data = get(matroid.I,posInI);
        if(isalpha(data) != 0){
           printf("%s\n", get(matroid.I,posInI));
        }else if (data != (int)data) {
            printf("%f\n", data);
        }else {
            printf("%d\n", data);
        }
    }
}

Matroid evaluateMatroid(Matroid matroid){
    printf("Entro en evaluar matroid!\n");
    #pragma omp parallel
    #pragma omp for
    for(int posInS=0; posInS<matroid.S->_size; posInS++){
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
    for(int posInI = 0; posInI<pMatroid.I->_size ; posInI++){
        if(get(pMatroid.I, posInI) == pTarget){
            return true;
        }
    }
    return false;
}

void deleteRepeateds(Matroid *pConjunto){
    for (int posInConjunto = 0; posInConjunto<(pConjunto->I->_size-1); posInConjunto++) {
        int posInConjunto2 = posInConjunto+1;
        while(posInConjunto2<pConjunto->I->_size){
            if(get(pConjunto->I, posInConjunto) == get(pConjunto->I, posInConjunto2)){
                delete(pConjunto->I, posInConjunto2);
            }else {
                posInConjunto2++;
            }
        }
    }
}

void intersection(Matroid *pConjunto, Matroid pMatroid2){
    #pragma omp parallel
    #pragma omp for
    for (int posInIConjunto = 0; posInIConjunto<pConjunto->I->_size; posInIConjunto++ ) {
        if(!(search(pMatroid2, get(pConjunto->I,posInIConjunto)))){
            delete(pConjunto->I, posInIConjunto);
            posInIConjunto-=1;
        }
    }
}

void optionB(Matroid matroids[], int pSize){
    evaluateMatroids(matroids, pSize);
    Matroid *conjunto;
    conjunto->I = matroids[0].I;
    deleteRepeateds(conjunto);

    #pragma omp parallel
    #pragma omp for
    for (int posInMatroids = 1; posInMatroids<pSize; posInMatroids++){
        intersection(conjunto, matroids[posInMatroids]);
    }

    Matroid matroid;
    matroid.I = conjunto->I;
    printf("resultado de la intersection\n");
    showMatroid(matroid);

}

void optionA(Matroid matroids[], int pSize){
    evaluateMatroids(matroids, pSize);
}

#endif // LIBRARY_H
