#ifndef UNLINENCRY
#define UNLINENCRY

void createZi(int8_t *Z, int8_t *L, int8_t *K, int8_t *Q, int8_t *L2, int8_t C, unsigned int n);

int8_t coeffum(int8_t *L,int8_t *Q, int8_t *L2, unsigned int u, unsigned int m,unsigned int n);


void createSystem(int8_t* Sys, int8_t *L,int8_t *Q, int8_t *L2, unsigned int n);

void extractKey(int8_t *key, int8_t *res, unsigned int n);

int decrypt(int8_t *key, int8_t *res, int8_t *L,int8_t *Q, int8_t *L2, int8_t *Z,unsigned int n);

#endif
