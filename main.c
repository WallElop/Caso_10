#include <stdio.h>
#include <matroid.h>
#include <stdbool.h>

bool prueba(int x){
    if(x>0){
        return true;
    }else{
        return false;
    }

}

void imprimirMatroid(Matroid matroid){
    printf("entro en imprimir\n");
    for(int i = 0; i<(sizeof (matroid.I)/sizeof (matroid.I[0])); i++){
        printf("%d\n", matroid.I[i]);
    }
}


Matroid evaluarMatroid(Matroid matroid){
    printf("Entro en evaluar matroid!\n");
    #pragma omp parallel
    #pragma omp for
    int cont = 0;

    printf("%d\n",(sizeof (matroid.S)/sizeof (matroid.S[0])));
    for(int i=0; i<(sizeof (matroid.S)/sizeof (matroid.S[0])); i++){
        if(matroid.function(matroid.S[i])){
            printf("Es mayor a 0\n");
            matroid.I[cont] = matroid.S[i];
            cont++;
        }
    }
    return matroid;
}


void evaluarMatroids(Matroid matroids[], int pTamanio){
    #pragma omp parallel
    #pragma omp for
//    printf("Va a evaluar los matroids\n");

    for(int i = 0; i<pTamanio; i++){
        matroids[i] = evaluarMatroid(matroids[i]);
        imprimirMatroid(matroids[i]);
    }
    return ;

}





int main()
{

    Matroid matroid = {.S = {1,2,-1,3,4}, .function = prueba};
    Matroid matroid2 = { .S = {5,-2,1,-3,7}, .function = prueba };

    Matroid matroids[] = {matroid, matroid2};
    int tamanioArreglo = sizeof (matroids)/sizeof (matroids[0]);

    evaluarMatroids(matroids, tamanioArreglo);
//    matroid = evaluarMatroid(matroid);
//    printf("Va a imprimir\n");
//    imprimirMatroid(matroid);
//    printf("Evaluo el matroid\n");
//    printf("%d\n", sizeof (matroid.I)/sizeof (matroid.I[0]));
//    for(int i = 0; i<(sizeof (matroids[0].I)/sizeof (matroids[0].I[0])); i++){
//        printf("%d\n", matroids[0].I[i]);
//    }


    printf("Hello World!\n");

    return 0;
}