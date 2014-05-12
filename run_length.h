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

/* inicializa o vetor com as frequencias de huffman com 0 */
buffer_t elements[512] = {0};


void run_length(unsigned char* vet, huffman_tree_t** ht, FILE* file) {

	/* cria uma tabela com o 
	 * 0 - valor do pixel, 
	 * 1 - numero de bits e 
	 * 2 - a quantidade de repeticoes
	 */
	int table[3][65];
	int i, j = 0, ant = vet[0];
	
	/* inicializa a primeira "repeticao" do vetor */
	table[0][0] = (int) vet[0];
	table[1][0] = bit_size_of( (int) vet[0] );
	table[2][0] = 0;
    
	/* itera pelo vetor procurando repeticoes */
	for(i = 0; i < 64; i++) {
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
        for(i = 0; i <= j; i++) {
            int cod_huffman;
            int nbitsfreq = nbits_freq(table[1][i], table[2][i]);
            buffer_t size = ht_encode(ht, 512, nbitsfreq, &cod_huffman);
            write_byte(file, cod_huffman, size);
            unsigned char nbits = (unsigned char) table[1][i];
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
        for(i = 0; i <= j; i++) {
        	/* modifica os valores da tabela de frequencia de huffman */
            int pos = nbits_freq(table[1][i], table[2][i]);
            elements[pos]++;
        }
    }

}

huffman_tree_t** call_huffman(huffman_tree_t** root, FILE* file) {
    /* Grava a lista de frequencia no arquivo para poder
     * recontruir a arvore na hora de decode
     */
    fwrite(elements, 512, sizeof(buffer_t), file);

    huffman_tree_t** ht = ht_create(elements, 512, root);
    return ht;
}

huffman_tree_t** read_huffman(huffman_tree_t** root, FILE* file) {
    /* Grava a lista de frequencia no arquivo para poder
     * recontruir a arvore na hora de decode
     */
    fread(elements, 512, sizeof(buffer_t), file);
    huffman_tree_t** ht = ht_create(elements, 512, root);
    return ht;
}

unsigned char* reverse_run_length(FILE* file, huffman_tree_t* root){
    
    unsigned char* vet = (unsigned char*) malloc(64*sizeof(unsigned char));
    
    int nbitsfreq;
    int vet_size = 0, i, j;
    int nbits, freq;
    
    while (vet_size < 64){
        ht_decode(root, &nbitsfreq, file);
        decode_nbits_freq(nbitsfreq, &nbits, &freq);
        nbits = nbits == 0 ? 8 : nbits;
        unsigned char value = read_bits(file, nbits);
        
#ifdef DEBUG_RUN_LENGTH
        static int w = 0;
        printf("%d-%d-%d ", freq, nbits, value);
        w++;
        if(w==3){
            printf("\n-----------\n");
            w = 0;
        }
#endif
        j = freq;

        for (i=vet_size; i<j+vet_size; i++) {
            vet[i] = value;
        }
        vet_size += j;
    }

    return vet;
}

#endif
