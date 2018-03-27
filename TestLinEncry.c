#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "LinEncry.h"
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

int main(int argc, char ** argv){
	unsigned int n = 5u ;
	if(argc == 2) n = (unsigned int)atoi(argv[1]);
	int8_t *K = allocateVector(n);
	
	
	int8_t *L = allocateMatrix(n,n);
	int8_t *F = allocateVector(n);
	int8_t *Z = allocateVector(n);
	int8_t *Li = allocateVector(n);
	
	
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
	
	
	
//==========CREATION Zi===============	
	
	createZi(Z,L, K, F, n);
	
	
	printf("Voici Z : \n");
	printVector(Z, n);
	
	
	int8_t *Kcalc = allocateVector(n);
	decrypt(Kcalc,L,Z,F,n);
	
	printf("Rappel de K : \n");
	printVector(K, n);
	
	printf("Voici K2 : \n");
	printVector(Kcalc, n);
	
	free(K);
	free(L);
	free(F);
	free(Z);
	free(Li);
	free(Kcalc);
	return 0 ;
}
