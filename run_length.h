/*
 * TRABALHO 02
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Run length encoding
 */

 #include "open_image.h"


 // create struct to define the number and the times it repeats
// or two vectors


void run_length(unsigned char* vet) {

	// create a table with number, number of bits and repetition

	int j = 0, ant = vet[0];
	int table[3][64];
	table[0][0] = (int) vet[0];
	table[1][0] = 0; //number of bits *****
	table[2][0] = 1;
	for(int i = 0; i < 64; i++) {
		if(ant == vet[i])
			table[2][j]++;
		else {
			j++;
			table[0][j] = (int) vet[i];
			table[1][j] = 0; //number of bits *****
			table[2][j] = 1;
			ant = vet[i];
		}
	}

	for(int i = 0; i <= j; i++) {
		printf("%d 	%d 	%d \n", table[0][j], table[1][j], table[2][j]);
	}
	printf("\n\n");


}
