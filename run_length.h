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
#include "vectorization.h"
#include <math.h>


buffer_t elements[65] = {0}; // initialize huffman elements with 0


void run_length(unsigned char* vet, huffman_tree_t** ht, FILE* file) {

	// create a table with number, number of bits and repetition
	int table[3][65];
	int j = 0, ant = vet[0];
	
	// initialize the first repetition of the vector
	table[0][0] = (int) vet[0];
	table[1][0] = bit_size_of( (int) vet[0] );
	table[2][0] = 0;

	// iterate through the vector and check for repetitions
	for(int i = 0; i < 64; i++) {
		if(ant == vet[i])
			table[2][j]++;
		else {
			j++;
			table[0][j] = (int) vet[i];
			table[1][j] = bit_size_of( (int) vet[i] );
			table[2][j] = 1;
			ant = vet[i];
		}
	}
    
    if (ht != NULL && file != NULL) {
        for(int i = 0; i <= j; i++) {
            int rep_huffman;
            buffer_t size = ht_encode(ht, 65, table[2][i], &rep_huffman);
            printf("%d -- %d \n", size, rep_huffman);
            //write_byte(file, (unsigned char) rep_huffman, bit_size_of(rep_huffman));
            write_byte(file, table[2][i], 7);
            unsigned char nbits = (unsigned char) table[1][i];
            write_byte(file, nbits, 3);
            unsigned char value = (unsigned char) table[0][i];
            write_byte(file, value, nbits);
            
#ifdef DEBUG_RUN_LENGTH
            static int i = 0;
            printf("%d ", value);
            i++;
            if(i==3){
                printf("\n-----------\n");
                i=0;
            }
#endif
        }
    }
    else {
        for(int i = 0; i <= j; i++) {
            elements[table[2][i]]++;
        }
    }

}

huffman_tree_t** call_huffman(huffman_tree_t** root, FILE* file) {
    // Grava a lista de frequencia no arquivo para poder
    // recontruir a arvore na hora de decode
    fwrite(elements, 65, sizeof(buffer_t), file);

    huffman_tree_t** ht = ht_create(elements, 65, root);
    return ht;
}

huffman_tree_t** read_huffman(huffman_tree_t** root, FILE* file) {
    // Grava a lista de frequencia no arquivo para poder
    // recontruir a arvore na hora de decode
    fread(elements, 65, sizeof(buffer_t), file);
    huffman_tree_t** ht = ht_create(elements, 65, root);
    return ht;
}

unsigned char* reverse_run_length(FILE* file, huffman_tree_t* root){
    
    unsigned char* vet = (unsigned char*) malloc(64*sizeof(unsigned char));
    
//    bitstream_t* bs = bs_create(file, BS_MODE_READ);
    
    char freq;
    int vet_size = 0, i, j;
    
    while (vet_size < 64){
        //int size = ht_decode(root, &freq, file);
        freq = read_bits(file, 7);
        unsigned char nbits = read_bits(file, 3);
        nbits = nbits == 0 ? 8 : nbits;
        unsigned char value = read_bits(file, nbits);
        
#ifdef DEBUG_RUN_LENGTH
        static int w = 0;
        printf("%d ", value);
        w++;
        if(w==3){
            printf("\n-----------\n");
            w = 0;
        }
#endif
        j = (int) freq;

        for (i=vet_size; i<j+vet_size; i++) {
            vet[i] = value;
        }
        vet_size += j;
    }

    return vet;
}

#endif
