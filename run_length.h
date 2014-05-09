/*
 * TRABALHO 02
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Run length encoding
 */

#ifndef _MULTIMEDIA_RUN_LENGTH_H_
#define _MULTIMEDIA_RUN_LENGTH_H_

#include "open_image.h"
#include "huffman.h"
#include "save_bits.h"
#include <math.h>


buffer_t elements[65] = {0}; // initialize huffman elements with 0

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


void run_length(unsigned char* vet, huffman_tree_t** ht, FILE* file) {

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
    
    if (ht != NULL && file != NULL) {
        for(int i = 0; i <= j; i++) {
            int rep_huffman;
            //buffer_t size = ht_encode(ht, 65, table[2][i], &rep_huffman);
            buffer_t size = 0;
            write_byte(file, (unsigned char) rep_huffman, size);
            unsigned char nbits = (unsigned char) table[1][i];
            write_byte(file, nbits, bit_size_of(table[1][i]));
            unsigned char value = (unsigned char) table[0][i];
            write_byte(file, value, bit_size_of(table[0][i]));
        }
    }
    else {
        for(int i = 0; i <= j; i++)
            elements[table[2][i]]++;
    }

}

huffman_tree_t** call_huffman(huffman_tree_t* root, FILE* file) {
    // Grava a lista de frequencia no arquivo para poder
    // recontruir a arvore na hora de decode
    fwrite(elements, 65, sizeof(buffer_t), file);
    huffman_tree_t** ht = ht_create(elements, 65, root);
    return ht;
}

#endif
