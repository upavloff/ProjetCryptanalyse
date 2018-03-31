#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include "FonctionsDeBases.h"

#define LIN(i,j,m,n) ((i)*(n) + (j))

void changementLigneGauss(int8_t *A, unsigned int ligne1, unsigned int ligne2, unsigned int n){
	unsigned int j;
	int8_t temp;
	for (j = 0; j < n; j ++){
		temp = A[LIN(ligne1,j,n,n)];
		A[LIN(ligne1,j,n,n)] = A[LIN(ligne2,j,n,n)];
		A[LIN(ligne2,j,n,n)] = temp;	
	}	
}

void gaussianElimination( int8_t *A, int8_t *b, unsigned int n){
/*Cette fonction prend en argument une matrice A, un vecteur b, la taille n.
Elle modifie A et b en appliquant l'elimination de Gauss sur A et b.*/
	unsigned int i,j,r;
	
	for (i = 0; i < n; i++){
		int8_t temp=0;
		unsigned int cpt=i+1;
		int changementAvecDerniereLigne = 0;  //on regarde si on fait un changement avec la derniere ligne et dans ce cas on ne fera pas de soustractions sur les lignes en dessous
		//ON regarde si on a besoin de changer de ligne, si oui on le fait
		if (A[LIN(i,i,n,n)] == 0){
			//changementLigneOblige = 1;
			while(A[LIN(cpt,i,n,n)] == 0 && cpt<n){
				cpt++;
			}
			if (cpt < n){
				changementLigneGauss(A,i,cpt,n);//changement matrice 
				printf("changement entre la ligne %u et %u\n",i,cpt);
				temp = b[i];     //changement de ligne pour vecteur
				b[i] = b[cpt];
				b[cpt] = temp;				
				if(cpt == n-1){
					changementAvecDerniereLigne = 1;
				}
			}
		}
		//Maintenant on a soit changer une ligne, soit on pas 
		//Si besoin on fait la methode du pivot
		if (changementAvecDerniereLigne == 0){
			for (j = i+1; j < n; j++){
				if( A[LIN(j,i,n,n)]!= 0){   //on entre que si en dessous du pivot c'est un 1
					printf("addition de la ligne %u sur la ligne %u\n",i,j);
					b[j] = b[j] ^ b[i];
					for (r = i; r < n; r++){
						A[LIN(j,r,n,n)] = A[LIN(j,r,n,n)] ^ A[LIN(i,r,n,n)];
					}	
				}
			}
		}
	}
}

void solveTriangularUpper(int8_t *x, int8_t *A, int8_t *b, unsigned int n){
/*Cette fonction prend en argument une matrice A, deux vecteurs x et b, la taille n.
On suppose que l'elimination de Gauss est deja faite.
Elle resout AX = B et modifie X.*/
	int j;
	int i, r;
	//int8_t sum;
	copyVector( x,b,n);
	/*for (i = n-1; i >= 0; i--){
		sum = 0;
		for (j = i+1; j < n; j++){
			sum += A[LIN(i,j,n,n)]*x[j];
		}	
		x[i] = (b[i]-(sum))/A[LIN(i,i,n,n)];
	}*/
	for (i = n-1; i >= 0; i--){
		if(A[LIN(i,i,n,n)]==1){  //On verifie qu on ai besoint daddictioner la ligne
			for (r = i-1; r >= 0; r--){
				if(A[LIN(r,i,n,n)]==1){
					x[r] = x[r] ^ x[i];
					for (j = i; j < n; j++){
						A[LIN(r,j,n,n)] = A[LIN(r,j,n,n)] ^ A[LIN(i,j,n,n)];
					}
				}			
			}
		}
	}
}

void solveSystemGauss( int8_t *x, int8_t *A, int8_t *b, unsigned int n){
/*Cette fonction prend en argument une matrice A, deux vecteurs x et b, la taille n.
Elle resout le systeme AX=B et modifie X.*/
	int8_t *Abyss = allocateMatrix(n,n);
	int8_t *bis = allocateVector(n);
	copyMatrix( Abyss,A,n,n);
	copyVector( bis,b,n);
	gaussianElimination(Abyss,bis,n);
	printf("Voici la matrice gauBer\n");
	printMatrix(Abyss,n,n);
	solveTriangularUpper(x,Abyss,bis,n);
	printf("Voici la matrice triangulaire\n");
	printMatrix(Abyss,n,n);
	freeMatrix(Abyss);
	freeVector(bis);
}

int main (int argc, char **argv)
{	
	srand(time(NULL));
	unsigned int m = 3;
	unsigned int n = 3;
	if (argc == 2){
		printf("blablib\n");
		m = (unsigned int)atoi(argv[1]);
		n = m;
	}
	else if (argc == 3){
		m = (unsigned int)atoi(argv[1]);
		n = (unsigned int)atoi(argv[2]);
		printf("azeertyuio\n");
	}
	int8_t *A = allocateMatrix(m,n);
	int8_t *v = allocateVector(m);
	int8_t *x = allocateVector(m);
	printf("\nMatrice de depart A aleatoire :\n");
	randomMatrix(A,m,n);
	printMatrix(A,m,n);
	printf("Vecteur aleatoire v :\n");
	randomVector(v,m);
	printVector(v,m);
	resizeMatrix(A,m,n);
	printMatrix(A,m,m);
	solveSystemGauss(x,A,v,m);
	printf("\n Le resultat x pour A*x=v est :\n");
	printVector(x,m);
	/*printf("\nElimination de Gauss\n==================\n");
	gaussianElimination(A,v,m);
	printMatrix(A,m,m);
	printVector(v,m);
	printf("\nRemonter des pivots\n==================\n");
	solveTriangularUpper(x,A,v,m);
	printMatrix(A,m,m);
	printf("Vecteur x tel que A*x = v\n");*/
	return 0;	
}
