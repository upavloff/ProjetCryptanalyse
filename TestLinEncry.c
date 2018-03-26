#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "LinEncry.h"
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

int main(int argc, char ** argv){
	unsigned int n = 128u ;
	if(argc == 2) n = (unsigned int)atoi(argv[1]);
	int8_t *K = allocateVector(n);
	int8_t *KLi = allocateVector(n);
	int8_t *KLiTemp = allocateVector(n);
	int8_t *L = allocateMatrix(n,n);
	int8_t *F = allocateVector(n);
	int8_t *Z = allocateVector(n);
	int8_t *Li = allocateVector(n);
	
	unsigned int i = 0;
	srand(time(NULL));
	
	randomBinVector(K, n);
	printf("Voici K : \n");
	printVector(K, n);
	randomBinVector(F, n);
	printf("Voici F : \n");
	printVector(F, n);
	randomBinMatrix(L, n, n);
	printf("Voici L : \n");
	copyMatrix(Li, L, n, n);
	printMatrix(L, n, n);
	copyVector(KLi,K,n);
	for(i = 0; i < n ; ++i){
		vectorMatrixProduct(KLiTemp,KLi, L, n, n);
		copyVector(KLi,KLiTemp,n);
		printf("Voici K*L^%u :", i+1);
		printVector(KLi, n);
		Z[i] = fonc(KLi, F, n);
	}
	printf("Voici Z : \n");
	printVector(Z, n);
	
	
	int8_t *Kcalc = allocateVector(n);
	decrypt(Kcalc,L,Z,F,n);
	printf("Voici K : \n");
	printVector(K, n);
	printf("Voici K2 : \n");
	printVector(Kcalc, n);
	
	free(K);
	free(KLi);
	free(KLiTemp);
	free(L);
	free(F);
	free(Z);
	free(Li);
	free(Kcalc);
	return 0 ;
}
