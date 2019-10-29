#ifndef MATROIDPARALLEL_H
#define MATROIDPARALLEL_H
#include <omp.h>
#include <matroid.h>



void evaluarMatroid(int matroid){
//    #pragma omp parallel{
//        #pragma omp for
        for(int i=0; i<sizeof (matroid.S); i++){
            int cont = 0;
            if(matroid.function(matroid.S[i])){
                matroid.I[cont] = matroid.S[i];
                cont++;
            }
        }

//    }
//    return matroid;

}

Matroid evaluarMatroids(){

}




#endif // MATROIDPARALLEL_H
