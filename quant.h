/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Quantization
 */

#ifndef QUANT_H
#define QUANT_H

/*#include "prepare_blocks.h"
#include "vectorization.h"*/

#define LIM 8


void create_matrix(int mat[LIM][LIM]) {
	mat[0][0] = 16;
    mat[0][1] = 11;
    mat[0][2] = 10;
    mat[0][3] = 16;
    mat[0][4] = 24;
    mat[0][5] = 40;
    mat[0][6] = 51;
    mat[0][7] = 61;

    mat[1][0] = 12;
    mat[1][1] = 12;
    mat[1][2] = 14;
    mat[1][3] = 19;
    mat[1][4] = 26;
    mat[1][5] = 58;
    mat[1][6] = 60;
    mat[1][7] = 55;

    mat[2][0] = 14;
    mat[2][1] = 13;
    mat[2][2] = 16;
    mat[2][3] = 24;
    mat[2][4] = 40;
    mat[2][5] = 57;
    mat[2][6] = 69;
    mat[2][7] = 56;

    mat[3][0] = 14;
    mat[3][1] = 17;
    mat[3][2] = 22;
    mat[3][3] = 29;
    mat[3][4] = 51;
    mat[3][5] = 87;
    mat[3][6] = 80;
    mat[3][7] = 62;

    mat[4][0] = 18;
    mat[4][1] = 22;
    mat[4][2] = 37;
    mat[4][3] = 56;
    mat[4][4] = 68;
    mat[4][5] = 109;
    mat[4][6] = 103;
    mat[4][7] = 77;

    mat[5][0] = 24;
    mat[5][1] = 35;
    mat[5][2] = 55;
    mat[5][3] = 64;
    mat[5][4] = 81;
    mat[5][5] = 104;
    mat[5][6] = 113;
    mat[5][7] = 92;

    mat[6][0] = 49;
    mat[6][1] = 64;
    mat[6][2] = 78;
    mat[6][3] = 87;
    mat[6][4] = 103;
    mat[6][5] = 121;
    mat[6][6] = 120;
    mat[6][7] = 101;

    mat[7][0] = 72;
    mat[7][1] = 92;
    mat[7][2] = 95;
    mat[7][3] = 98;
    mat[7][4] = 112;
    mat[7][5] = 100;
    mat[7][6] = 103;
    mat[7][7] = 99;
}


void quantization(int mat[LIM][LIM], int quant[LIM][LIM]) {
	int i, j;

	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mat[i][j] = round((float)mat[i][j]/(float)quant[i][j]);
		}
	}

}

void dequantization(int mat[LIM][LIM], int quant[LIM][LIM]) {
	int i, j;

	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mat[i][j] = mat[i][j]*quant[i][j];
		}
	}

}



#endif