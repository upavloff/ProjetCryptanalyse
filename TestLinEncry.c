#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include "LinEncry.h"
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

int main(int argc, char ** argv){
	unsigned int n = 20;
	if(argc == 2) n = (unsigned int)atoi(argv[1]);
	int8_t *K = allocateVector(n);
	int8_t *L = allocateMatrix(n,n);
	int8_t *F = allocateVector(n);
	int8_t *Z = allocateVector(n);
	int8_t *Kcalc = allocateVector(n);
	
	srand(time(NULL));
	do{
		randomBinVector(K,n);
		printf("Voici K : \n");
		printVector(K,n);
	
		randomBinVector(F,n);
		printf("Voici F : \n");
		printVector(F,n);
	
		randomBinMatrix(L,n,n);
		printf("Voici L : \n");
		printMatrix(L,n,n);
		
		createZi(Z,L,K,F,n);
		printf("Voici Z : \n");
		printVector(Z,n);
		
	}while(!decrypt(Kcalc,L,Z,F,n));
	
	printf("Rappel de K : \n");
	printVector(K,n);
	
	printf("Voici K2 : \n");
	printVector(Kcalc,n);
	
	
	
	printf("Voici Z : \n");
	printVector(Z,n);
	createZi(Z,L,Kcalc,F,n);
	
	printf("Voici le nouveau Z calcule a partir de K2: \n");
	printVector(Z,n);
	
	int k = 0,sum = 0;
	for(k=0;k<n;k++){
		if (K[k]==Kcalc[k]) sum++;
	}
	printf("Comparaison entre K et K2 : \n");
	printf("nombres qui coincident par rapport a %d : %d\n",n,sum);
	
	
	free(K);
	free(L);
	free(F);
	free(Z);
	free(Kcalc);
	return 0;
}
