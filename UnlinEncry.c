#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

#define LIN(i,j,m,n) ((i)*(n)+(j))

void createZi(int8_t *Z, int8_t *L, int8_t *K, int8_t *Q, int8_t *L2, int8_t C, unsigned int n){
	 unsigned int i;
	 int8_t *KLiTemp = allocateVector(n);
	 int8_t *KLi = allocateVector(n);
	 int8_t *KLiQ = allocateVector(n);
	 int8_t KLiQKLi;
	 int8_t L2KLi;
	 copyVector(KLi,K,n);
	 for(i = 0; i < n ; i++){
		printf("Calcul de K*(L^%u)...\n",i+1);
		vectorMatrixProduct(KLiTemp,KLi,L,n,n);
		copyVector(KLi,KLiTemp,n);
		printf("Calcul de K*(L^%u)*Q...\n",i+1);
		vectorMatrixProduct(KLiQ,KLi,Q,n,n);
		printf("Calcul de K*(L^%u)*Q*K*(L^%u)^t...\n",i+1,i+1);
		KLiQKLi = scalarBinProduct(KLiQ,KLi,n);
		printf("Calcul de L'*K*(L^%u)...\n",i+1);
		L2KLi = scalarBinProduct(L2,KLi,n);
  		Z[i] = KLiQKLi^L2KLi^C;
  		
	}
	free(KLiTemp);
	free(KLi);
	free(KLiQ);
}

/*void createSystem(int8_t* Sys, int8_t *F, int8_t* L, unsigned int n){
	unsigned int i, j, k;
	int8_t* Li = allocateMatrix(n,n);
	int8_t* L2 = allocateMatrix(n,n);
	identityMatrix(L2, n, n);
	for(i = 0; i < n; i++){
		matrixMatrixProduct(Li, L2, L, n, n, n);
		printf("Calcul de L^%u...\n",i+1);
		for(j = 0; j < n; ++j){
			Sys[LIN(i,j,n,n)] = 0;
			for(k = 0; k < n; ++k){
				Sys[LIN(i,j,n,n)] ^= F[k] & Li[LIN(j,k,n,n)];
			}
		}
		copyMatrix(L2, Li, n, n);
		
	
	}
	//printf("debug1\n");
	freeMatrix(L2);
	//printf("debug2\n");

	freeMatrix(Li);

}
int decrypt(int8_t *res, int8_t *L, int8_t *Z, int8_t *F, unsigned int n){
	int8_t* Sys = allocateMatrix(n,n);	
	createSystem(Sys, F, L, n);
	printf("Voici le systeme lineaire : \n");
	printMatrix(Sys,n,n);
	printVector(Z,n);
	int boolean = solveSystemGauss(res, Sys, Z, n);
	freeMatrix(Sys);
	return boolean;
}*/

