GCC_FLAGS = -Wall -Werror
all: TestGauBinaire TestAddEncry

addEncry.o	: addEncry.c
	gcc $(GCC_FLAGS) -c addEncry.c

FonctionsDeBases.o	: FonctionsDeBases.c
	gcc $(GCC_FLAGS) -c FonctionsDeBases.c -lm

GauBinaire.o	: GauBinaire.c FonctionsDeBases.h
	gcc $(GCC_FLAGS) -c GauBinaire.c FonctionsDeBases.c
	
TestAddEncry		: TestAddEncry.c addEncry.o FonctionsDeBases.o 
	gcc $(GCC_FLAGS) -o TestAddEncry TestAddEncry.c addEncry.o FonctionsDeBases.o 
	
TestGauBinaire		: TestGauBinaire.c GauBinaire.o FonctionsDeBases.o
	gcc $(GCC_FLAGS) -o TestGauBinaire TestGauBinaire.c GauBinaire.o FonctionsDeBases.o


clean	:
	rm -f *.o TestGauBinaire TestAddEncry
