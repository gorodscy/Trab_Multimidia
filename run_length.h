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
 #include <math.h>


unsigned short int elements[9][65] = {0}; // initialize huffman elements with 0

int number_of_bits(int number) {
	if(number == 0)
		return 0;

	int i = 1, sum = 1;

	while(number > sum) {
		sum += pow(2,i);
		i++;
	}

	return i;
}


void run_length(unsigned char* vet) {

	// create a table with number, number of bits and repetition
	int table[3][64];
	int j = 0, ant = vet[0];
	
	// initialize the first repetition of the vector
	table[0][0] = (int) vet[0];
	table[1][0] = number_of_bits( (int) vet[0] );
	table[2][0] = 0;

	// iterate through the vector and check for repetitions
	for(int i = 0; i < 64; i++) {
		if(ant == vet[i])
			table[2][j]++;
		else {
			j++;
			table[0][j] = (int) vet[i];
			table[1][j] = number_of_bits( (int) vet[i] );
			table[2][j] = 1;
			ant = vet[i];
		}
	}

	for(int i = 0; i <= j; i++)
		elements[table[1][i]][table[2][i]]++;

}
