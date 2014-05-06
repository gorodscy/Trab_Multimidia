/*
 * TRABALHO 02
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Vetorização
 */

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


void vectorization_colors(unsigned char blue[8][8], unsigned char green[8][8], unsigned char red[8][8]) {

	unsigned char *vblue, *vgreen, *vred;

	vblue = vectorization(blue);
	vgreen = vectorization(green);
	vred = vectorization(red);

	// send the information to the run-length encoding
	

}

// revert the vectorization
int** revert_vectorization(int *vet) {

	int **mat, x = 0;

	mat = (int**)malloc(8*sizeof(int*));
	for(int i = 0; i < 8; i++)
        mat[i] = (int*)malloc(8*sizeof(int));

    for(int k = 0; k < 8; k++) {
		for(int i = 0; i <= k; i++) {
			if(k%2 == 0) // subindo
				mat[k-i][i] = vet[x];
			else // descendo
				mat[i][k-i] = vet[x];
			x++;
		}
	}

	for(int k = 0; k < 8; k++) {
		for(int i = k+1; i < 8; i++) {
			if(k%2 == 0) // subindo
				mat[8-i+k][i] = vet[x];
			else // descendo
				mat[i][8-i+k] = vet[x];
			x++;
		}
	}


	return mat;
}
