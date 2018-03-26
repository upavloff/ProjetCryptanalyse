#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

#define LIN(i,j,m,n) ((i)*(n)+(j))

int8_t fonc(int8_t *KLi, int8_t *F, unsigned int n){
	  unsigned int i ;
	  int8_t zi = KLi[0] & F[0] ;
	 	 for(i = 1; i < n; ++i){
   		 zi += KLi[i] & F[i];
  	}
  
  	return zi%2 ;
  
}
void createSystem(int8_t* Sys, int8_t *F, int8_t* L, unsigned int n){
	unsigned int i, j, k;
	int8_t* Li = allocateMatrix(n,n);
	int8_t* L2 = allocateMatrix(n,n);
	//printf("L : \n");
	//printMatrix(L,n,n);
	identityMatrix(L2, n, n);
	for(i = 0; i < n; ++i){
		matrixMatrixProduct(Li, L2, L, n, n, n);
		//printf("Li : \n");
		//printMatrix(Li,n,n);
		for(j = 0; j < n; ++j){
			Sys[LIN(i,j,n,n)] = F[0] & Li[LIN(0,j,n,n)];
			for(k = 1; k < n; ++k){
				Sys[LIN(i,j,n,n)] += F[k] & Li[LIN(k,j,n,n)];
			}
			Sys[LIN(i,j,n,n)] %= 2;
				
			
		}
		copyMatrix(L2, Li, n, n);
		//printf("L2 : \n");
		//printMatrix(L2,n,n);
	
	}
	freeMatrix(Li);
	freeMatrix(L2);


}
void decrypt(int8_t *res, int8_t *L, int8_t *Z, int8_t *F, unsigned int n){
	int8_t* Sys = allocateMatrix(n ,n);	
	createSystem(Sys, F, L, n);
	printf("Voici le systeme lineaire : \n");
	printMatrix(Sys,n,n);
	solveSystemGauss(res, Sys, Z, n);
	freeMatrix(Sys);
}

