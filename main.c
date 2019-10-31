#include <stdio.h>
#include "matroid.h"
#include <stdbool.h>

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
    printf("Entro en search\n");
    #pragma omp parallel
    #pragma omp for
    printf("Tamanio de la lista: ");
    printf("%d\n", pMatroid.I->_size);
    for(int posInI = 0; posInI<pMatroid.I->_size ; posInI++){
        printf("%d\n", get(pMatroid.I, posInI));
        printf("%d\n", pTarget);
        if(get(pMatroid.I, posInI) == pTarget){
            printf("Verdadero\n");
            return true;
        }
    }
    printf("Falso\n");
    return false;
}

void deleteRepeateds(Matroid *pConjunto){
    printf("Entro en eliminar repetidos");
    for (int posInConjunto = 0; posInConjunto<(pConjunto->I->_size-1); posInConjunto++) {
        printf("entro en el for\n");
        int posInConjunto2 = posInConjunto+1;
        while(posInConjunto2<pConjunto->I->_size){
            printf("Entro en el while\n");
            printf("%d\n", pConjunto->I->_size);
            printf("%d", get(pConjunto->I, posInConjunto));
            printf(" == ");
            printf("%d\n", get(pConjunto->I, posInConjunto2));
            if(get(pConjunto->I, posInConjunto) == get(pConjunto->I, posInConjunto2)){
                delete(pConjunto->I, posInConjunto2);
            }else {
                posInConjunto2++;
            }
        }
    }
}

void intersection(Matroid *pConjunto, Matroid pMatroid2){
    printf("Entro en interssection\n");
    #pragma omp parallel
    #pragma omp for
    for (int posInIMatroid1 = 0; posInIMatroid1<pConjunto->I->_size; posInIMatroid1++ ) {
        printf("%d\n", get(pConjunto->I,posInIMatroid1));
        if(!(search(pMatroid2, get(pConjunto->I,posInIMatroid1)))){
            printf("va a borrar jaja XD\n");
            delete(pConjunto->I, posInIMatroid1);
        }
        printf("no se borro yeeei\n");
    }
}

void B(Matroid matroids[], int pSize){
    printf("entro en B\n");
    evaluateMatroids(matroids, pSize);
    Matroid *conjunto;
    conjunto->I = matroids[0].I;
    deleteRepeateds(conjunto);
    printf("resultado de eliminar el repetido\n");
    Matroid matroid;
    matroid.I = conjunto->I;
    showMatroid(matroid);

    #pragma omp parallel
    #pragma omp for
    for (int posInMatroids = 1; posInMatroids<pSize; posInMatroids++){
        intersection(conjunto, matroids[posInMatroids]);
    }

//    Matroid matroid;
    matroid.I = conjunto->I;
    printf("resultado de la intersection\n");
    showMatroid(matroid);

}


int main(){

    printf("%f\n", 3.23456);

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

    Matroid matroids[] = {matroid, matroid2};
    Matroid matroidsInter[] = {matroid, matroid3};


    int tamanioArreglo = sizeof (matroids)/sizeof (matroids[0]);

    evaluateMatroids(matroids, tamanioArreglo);

    B(matroidsInter, 2);

    printf("Hello World!\n");


    return 0;
}
