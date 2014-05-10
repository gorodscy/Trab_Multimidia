/*
 * TRABALHO 02
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


unsigned char * vectorization(unsigned char mat[8][8]) {
	int x = 0;
	unsigned char *vet;

	vet = (unsigned char*)malloc(64*sizeof(unsigned char));

	for(int k = 0; k < 8; k++) {
		for(int i = 0; i <= k; i++) {
			if(k%2 == 0) // subindo
				vet[x] = mat[k-i][i];
			else // descendo
				vet[x] = mat[i][k-i];
			x++;
		}
	}

	for(int k = 0; k < 8; k++) {
		for(int i = k+1; i < 8; i++) {
			if(k%2 == 0) // subindo
				vet[x] = mat[8-i+k][i];
			else // descendo
				vet[x] = mat[i][8-i+k];
			x++;
		}
	}	

	return vet;
}


void vectorization_colors(huffman_tree_t** ht, FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]) {
    
	unsigned char *vred, *vgreen, *vblue;
    
	vred = vectorization(red);
	vgreen = vectorization(green);
	vblue = vectorization(blue);
    
	// send the information to the run-length encoding
    run_length(vred, ht, file);
    run_length(vgreen, ht, file);
	run_length(vblue, ht, file);
    
}

// revert the vectorization
void revert_vectorization(huffman_tree_t* root, FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]) {

	int x = 0;
    unsigned char *vred, *vgreen, *vblue;
    
    vred = reverse_run_length(file, root);
    vgreen = reverse_run_length(file, root);
    vblue = reverse_run_length(file, root);

    for(int k = 0; k < 8; k++) {
		for(int i = 0; i <= k; i++) {
			if(k%2 == 0) { // subindo
				red[k-i][i] = vred[x];
                green[k-i][i] = vgreen[x];
                blue[k-i][i] = vblue[x];
            }
			else { // descendo
				red[i][k-i] = vred[x];
                green[i][k-i] = vgreen[x];
                blue[i][k-i] = vblue[x];
            }
			x++;
		}
	}

	for(int k = 0; k < 8; k++) {
		for(int i = k+1; i < 8; i++) {
			if(k%2 == 0) { // subindo
				red[8-i+k][i] = vred[x];
                green[8-i+k][i] = vgreen[x];
                blue[8-i+k][i] = vblue[x];
            }
			else { // descendo
				red[i][8-i+k] = vred[x];
                green[i][8-i+k] = vgreen[x];
                blue[i][8-i+k] = vblue[x];
            }
			x++;
		}
	}

	return;
}

#endif
