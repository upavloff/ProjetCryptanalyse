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
	 for(i = 0; i < n*n ; i++){
		vectorMatrixProduct(KLiTemp,KLi,L,n,n);
		copyVector(KLi,KLiTemp,n);
		vectorMatrixProduct(KLiQ,KLi,Q,n,n);
		KLiQKLi = scalarBinProduct(KLiQ,KLi,n);
		printf("Voici KLiQKLi : %"PRId8"\n",KLiQKLi);
		L2KLi = scalarBinProduct(L2,KLi,n);
		printf("Voici L2KLi : %"PRId8"\n",L2KLi);
  		Z[i] = KLiQKLi^L2KLi^C;
  		
	}
	free(KLiTemp);
	free(KLi);
	free(KLiQ);
}

int8_t coeffum(int8_t *L,int8_t *Q, int8_t *L2, unsigned int u, unsigned int m,unsigned int n){
	unsigned int i,j;
	int8_t coef = 0;
	for(i = 0;i<n;i++){
		for(j=0;j<n;j++){
			coef ^= L[LIN(u,j,n,n)] & L[LIN(m,i,n,n)] & Q[LIN(j,i,n,n)];
		}
	}
	if (u == m){
		for (i=0;i<n;i++){
			for (j=0;j<n;j++){
				coef ^= L2[i] & L[LIN(j,i,n,n)];
			}
		}
	}
	printf("coeff[%u,%u]\n",u,m);
	return coef;
}


void createSystem(int8_t* Sys, int8_t *L,int8_t *Q, int8_t *L2, unsigned int n){
	unsigned int i,j;
	unsigned int compt1 = 0;
	unsigned int compt2 = 0;
	
	int8_t* Li = allocateMatrix(n,n);
	int8_t* LiTemp = allocateMatrix(n,n);
	identityMatrix(LiTemp, n, n);
	for(i = 0; i < n*n; i++){
		printf("Calcul de L^%u...\n",i+1);
		matrixMatrixProduct(Li, LiTemp, L, n, n, n);
		printf("Voici L^%u...\n",i+1);
		printMatrix(Li,n,n);
		compt1 = 0;
		compt2 = 0;
		for(j=0;j<n*n;j++){
			Sys[LIN(i,j,n*n,n*n)] = coeffum(Li,Q,L2,compt1,compt2,n);
			compt2++;
			if (compt2 == n){
				compt2 = 0;
				compt1++;
			}
		}
		copyMatrix(LiTemp,Li,n,n);
		
	
	}
	//printf("debug1\n");
	freeMatrix(LiTemp);
	//printf("debug2\n");

	freeMatrix(Li);

}

void extractKey(int8_t *key, int8_t *res, unsigned int n){
	unsigned int i;
	for(i=0;i<n;i++){
		key[i] = res[(n+1)*i];
	}
}




int decrypt(int8_t *key, int8_t *res, int8_t *L,int8_t *Q, int8_t *L2, int8_t *Z,unsigned int n){
	int8_t* Sys = allocateMatrix(n*n,n*n);	
	createSystem(Sys,L,Q,L2,n);
	printf("Voici le systeme lineaire : \n");
	printMatrix(Sys,n*n,n*n);
	printVector(Z,n*n);
	int boolean = solveSystemGauss(res, Sys, Z, n*n);
	freeMatrix(Sys);
	if (boolean){
		extractKey(key,res,n);
	}
	return boolean;
}

