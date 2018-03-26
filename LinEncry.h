#ifndef LINENCRY
#define LINENCRY

int8_t fonc(int8_t *KLi, int8_t *F, unsigned int n);

void createSystem(int8_t* Sys, int8_t *F, int8_t* L, unsigned int n);

void decrypt(int8_t *res, int8_t *L, int8_t *Z, int8_t *F, unsigned int n);


#endif
