/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Vetorização
 */

#ifndef _MULTIMEDIA_VECTORIZATION_H_
#define _MULTIMEDIA_VECTORIZATION_H_

#include "open_image.h"
#include "run_length.h"
#include "prepare_blocks.h" 
/*#include "dct.h"*/

void print_vector(int* vet) {
    printf("Printing vector: ");
    int i;
    for (i=0; i<64; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

int * vectorization(int mat[8][8]) {
	int x = 0, k, i;
	int *vet;

	vet = (int*)malloc(64*sizeof(int));

	 for(k = 0; k < 8; k++) {
	 	for(i = 0; i <= k; i++) {
	 		if(k%2 == 0) /* subindo */
	 			vet[x] = mat[k-i][i];
	 		else /* descendo */
	 			vet[x] = mat[i][k-i];
	 		x++;
	 	}
	 }
   
    for(k = 0; k < 8; k++) {
        for(i = k+1; i < 8; i++) {
            if(k%2 == 0) /* subindo */
                vet[x] = mat[8-i+k][i];
            else /* descendo */
                vet[x] = mat[i][8-i+k];
            x++;
        }
    }

	return vet;
}


void vectorization_colors(huffman_tree_t** ht, FILE* file, int red[8][8], int green[8][8], int blue[8][8]) {
    
	int *vred, *vgreen, *vblue;
    
	vred = vectorization(red);
	vgreen = vectorization(green);
	vblue = vectorization(blue);
#ifdef DEBUG_VECTOR
    file && ht ? print_vector(vred) : 0;
#endif
	/* Envia informações para o run-length encoding */
    run_length(vred, ht, file);
    run_length(vgreen, ht, file);
	run_length(vblue, ht, file);
    
}

void revert_vector(int* vet, int mat[8][8]) {
    int x = 0, k, i;

    for(k = 0; k < 8; k++) {
        for(i = 0; i <= k; i++) {
	 		if(k%2 == 0) { /* subindo */
	 			mat[k-i][i] = vet[x];
            }
	 		else { /* descendo */
	 			mat[i][k-i] = vet[x];
            }
	 		x++;
	 	}
    }
    for(k = 0; k < 8; k++) {
        for(i = k+1; i < 8; i++) {
	 		if(k%2 == 0) { /* subindo */
	 			mat[8-i+k][i] = vet[x];
            }
	 		else { /* descendo */
	 			mat[i][8-i+k] = vet[x];
            }
	 		x++;
	 	}
    }
}


void revert_vectorization(huffman_tree_t* root, FILE* file, int red[8][8], int green[8][8], int blue[8][8]) {

    int *vred, *vgreen, *vblue;
    
    vred = reverse_run_length(file, root);
    vgreen = reverse_run_length(file, root);
    vblue = reverse_run_length(file, root);
#ifdef DEBUG_VECTOR
    print_vector(vred);
#endif
    revert_vector(vred, red);
    revert_vector(vgreen, green);
    revert_vector(vblue, blue);

}

#endif
