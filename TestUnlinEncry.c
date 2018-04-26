#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include "UnlinEncry.h"
#include "FonctionsDeBases.h"
#include "GauBinaire.h"

int main(int argc, char ** argv){
	unsigned int n = 20;
	if(argc == 2) n = (unsigned int)atoi(argv[1]);
	int8_t *K = allocateVector(n);
	int8_t *L = allocateMatrix(n,n);
	int8_t *Q = allocateMatrix(n,n);
	int8_t *L2 = allocateVector(n);
	int8_t *Z = allocateVector(n);	

	srand(time(NULL));
	
	int8_t C = randomBinValue();
	printf("Voici C : %"PRId8 "\n",C);

	randomBinVector(K,n);
	printf("Voici K : \n");
	printVector(K,n);
	
	randomBinVector(L2,n);
	printf("Voici L' : \n");
	printVector(L2,n);
	
	randomBinMatrix(L,n,n);
	printf("Voici L : \n");
	printMatrix(L,n,n);

	randomBinMatrix(Q,n,n);
	printf("Voici Q : \n");
	printMatrix(Q,n,n);
		
	createZi(Z,L,K,Q,L2,C,n);
	printf("Voici Z : \n");
	printVector(Z,n);	
	

	free(K);
	free(L);
	free(Q);
	free(L2);
	free(Z);
	return 0;
}
