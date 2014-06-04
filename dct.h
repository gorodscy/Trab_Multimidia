/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * DCT e IDCT
 */

#ifndef DCT_H
#define DCT_H

/*#include "prepare_blocks.h"
#include "vectorization.h"*/
#include <math.h>
#include "quant.h"


#define sqrt2 1.41421356237
#define sqrt8 2.82842712475
#define PI 3.14159265
#define LIM 8


void normal_matrix(double mat[LIM][LIM]) {
	mat[0][0] = 0.3536;
    mat[0][1] = 0.3536;
    mat[0][2] = 0.3536;
    mat[0][3] = 0.3536;
    mat[0][4] = 0.3536;
    mat[0][5] = 0.3536;
    mat[0][6] = 0.3536;
    mat[0][7] = 0.3536;

    mat[1][0] = 0.4904;
    mat[1][1] = 0.4157;
    mat[1][2] = 0.2778;
    mat[1][3] = 0.0975;
    mat[1][4] = -0.0975;
    mat[1][5] = -0.2778;
    mat[1][6] = -0.4157;
    mat[1][7] = -0.4904;

    mat[2][0] = 0.4619;
    mat[2][1] = 0.1913;
    mat[2][2] = -0.1913;
    mat[2][3] = -0.4619;
    mat[2][4] = -0.4619;
    mat[2][5] = -0.1913;
    mat[2][6] = 0.1913;
    mat[2][7] = 0.4619;

    mat[3][0] = 0.4157;
    mat[3][1] = -0.0975;
    mat[3][2] = -0.4904;
    mat[3][3] = -0.2778;
    mat[3][4] = 0.2778;
    mat[3][5] = 0.4904;
    mat[3][6] = 0.0975;
    mat[3][7] = -0.4157;

    mat[4][0] = 0.3536;
    mat[4][1] = -0.3536;
    mat[4][2] = -0.3536;
    mat[4][3] = 0.3536;
    mat[4][4] = 0.3536;
    mat[4][5] = -0.3536;
    mat[4][6] = -0.3536;
    mat[4][7] = 0.3536;

    mat[5][0] = 0.2778;
    mat[5][1] = -0.4904;
    mat[5][2] = 0.0975;
    mat[5][3] = 0.4157;
    mat[5][4] = -0.4157;
    mat[5][5] = -0.0975;
    mat[5][6] = 0.4904;
    mat[5][7] = -0.2778;

    mat[6][0] = 0.1913;
    mat[6][1] = -0.4619;
    mat[6][2] = 0.4619;
    mat[6][3] = -0.1913;
    mat[6][4] = -0.1913;
    mat[6][5] = 0.4619;
    mat[6][6] = -0.4619;
    mat[6][7] = 0.1913;

    mat[7][0] = 0.0975;
    mat[7][1] = -0.2778;
    mat[7][2] = 0.4157;
    mat[7][3] = -0.4904;
    mat[7][4] = 0.4904;
    mat[7][5] = -0.4157;
    mat[7][6] = 0.2778;
    mat[7][7] = -0.0975;

}


void inverse_matrix(double mat[LIM][LIM]) {

	mat[0][0] = 0.353507;
    mat[0][1] = 0.490419;
    mat[0][2] = 0.461997;
    mat[0][3] = 0.415711;
    mat[0][4] = 0.353507;
    mat[0][5] = 0.277824;
    mat[0][6] = 0.191340;
    mat[0][7] = 0.097518;

    mat[1][0] = 0.353507;
    mat[1][1] = 0.415711;
    mat[1][2] = 0.191340;
    mat[1][3] = -0.097518;
    mat[1][4] = -0.353507;
    mat[1][5] = -0.490419;
    mat[1][6] = -0.461997;
    mat[1][7] = -0.277824;

    mat[2][0] = 0.353507;
    mat[2][1] = 0.277824;
    mat[2][2] = -0.191340;
    mat[2][3] = -0.490419;
    mat[2][4] = -0.353507;
    mat[2][5] = 0.097518;
    mat[2][6] = 0.461997;
    mat[2][7] = 0.415711;

    mat[3][0] = 0.353507;
    mat[3][1] = 0.097518;
    mat[3][2] = -0.461997;
    mat[3][3] = -0.277824;
    mat[3][4] = 0.353507;
    mat[3][5] = 0.415711;
    mat[3][6] = -0.191340;
    mat[3][7] = -0.490419;

    mat[4][0] = 0.353507;
    mat[4][1] = -0.097518;
    mat[4][2] = -0.461997;
    mat[4][3] = 0.277824;
    mat[4][4] = 0.353507;
    mat[4][5] = -0.415711;
    mat[4][6] = -0.191340;
    mat[4][7] = 0.490419;

    mat[5][0] = 0.353507;
    mat[5][1] = -0.277824;
    mat[5][2] = -0.191340;
    mat[5][3] = 0.490419;
    mat[5][4] = -0.353507;
    mat[5][5] = -0.097518;
    mat[5][6] = 0.461997;
    mat[5][7] = -0.415711;

    mat[6][0] = 0.353507;
    mat[6][1] = -0.415711;
    mat[6][2] = 0.191340;
    mat[6][3] = 0.097518;
    mat[6][4] = -0.353507;
    mat[6][5] = 0.490419;
    mat[6][6] = -0.461997;
    mat[6][7] = 0.277824;

    mat[7][0] = 0.353507;
    mat[7][1] = -0.490419;
    mat[7][2] = 0.461997;
    mat[7][3] = -0.415711;
    mat[7][4] = 0.353507;
    mat[7][5] = -0.277824;
    mat[7][6] = 0.191340;
    mat[7][7] = -0.097518;

}


void multiply_matrix(double mat1[LIM][LIM], double mat2[LIM][LIM], double result[LIM][LIM]) {
	int i, j, k;
	double sum;

	for(i = 0; i < LIM; i++) {
  		for(j = 0; j < LIM; j++) {
  			sum = 0.0;
  			for(k = 0; k < LIM; k++) {
  				sum += mat1[i][k]*mat2[k][j]; 
  			}
  			result[i][j] = sum;
  		}
  	}

}

void multiply_matrix2(double mat1[LIM][LIM], double mat2[LIM][LIM], int result[LIM][LIM]) {
	int i, j, k;
	double sum;

	for(i = 0; i < LIM; i++) {
  		for(j = 0; j < LIM; j++) {
  			sum = 0.0;
  			for(k = 0; k < LIM; k++) {
  				sum += mat1[i][k]* mat2[k][j]; 
  			}
  			result[i][j] = (int) sum;
  		}
  	}

}

void dct(unsigned char mat[LIM][LIM], int mdct[LIM][LIM]) {
	double t[LIM][LIM], ti[LIM][LIM], tmp[LIM][LIM], tmp2[LIM][LIM], mat2[LIM][LIM];
	normal_matrix(t);
	inverse_matrix(ti);

	int i, j;
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mat2[i][j] = ((double)mat[i][j]) - 128.0;
		}
	}

	multiply_matrix(t, mat2, tmp);
	multiply_matrix(tmp, ti, tmp2);

	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mdct[i][j] = (int) tmp2[i][j];
		}
	}

	int q[LIM][LIM];
	create_matrix(q);
	quantization(mdct, q);

	/*
	printf("\n\n");
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d\t", mdct[i][j]);
		}
		printf("\n");
	}
	*/	
}

void idct(int mat[LIM][LIM], unsigned char midct[LIM][LIM]) {
	double t[LIM][LIM], ti[LIM][LIM], tmp[LIM][LIM], tmp2[LIM][LIM], mat2[LIM][LIM];
	normal_matrix(t);
	inverse_matrix(ti);

	int q[LIM][LIM];
	create_matrix(q);
	dequantization(mat, q);

	int i, j;
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mat2[i][j] = ((double)mat[i][j]);
		}
	}	

	multiply_matrix(ti, mat2, tmp);
	multiply_matrix(tmp, t, tmp2);

	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			midct[i][j] = (unsigned char)tmp2[i][j] + 128;
		}
	}	

	/*
	printf("\n\n");
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d\t", midct[i][j]);
		}
		printf("\n");
	}
	*/	
}

/*
void dct(unsigned char mat[LIM][LIM], int mdct[LIM][LIM]) {
	int i, j, a, b;
	double tmp;

	for(i = 0; i < LIM; i ++) {
		for(j = 0; j < LIM; j++) {
			tmp = 0.25;
			if(i == 0)
				tmp = tmp * (1.0/sqrt2);

			if(j == 0)
				tmp = tmp * (1.0/sqrt2);		

			double value = 0;
			for(a = 0; a < LIM; a++) {
				for(b = 0; b < LIM; b++) {
					value += (mat[a][b] - 128) * cos( ( (2*a+1)*i*PI )/16.0 ) * cos( ( (2*b+1)*j*PI )/16.0 );
				}
			}
			mdct[i][j] = (tmp * value);
		}
	}

	int q[LIM][LIM];
	create_matrix(q);
	quantization(mdct, q);
	
	printf("\n\n");
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d\t", mdct[i][j]);
		}
		printf("\n");
	}
	
}

void idct(int mat[LIM][LIM], unsigned char midct[LIM][LIM]) {
	int i, j, a, b;
	double t;

	int q[LIM][LIM];
	create_matrix(q);
	dequantization(mat, q);

	for(i = 0; i < LIM; i ++) {
		for(j = 0; j < LIM; j++) {
			t = 0.25;

			double value = 0;
			for(a = 0; a < LIM; a++) {
				double tmp = 1;
				for(b = 0; b < LIM; b++) {
					if(b == 0)
						tmp = (1.0/sqrt2);

					if(a == 0)
						tmp = tmp * (1.0/sqrt2);
					
					value += (mat[a][b]) * cos( ( (2*i+1)*a*PI )/16.0 ) * cos( ( (2*j+1)*b*PI )/16.0 ) * tmp;
					//value += (mat[a][b]) * cos( ( (2*a+1)*i*PI )/16.0 ) * cos( ( (2*b+1)*j*PI )/16.0 ) * tmp;
				}
			}
			midct[i][j] = (unsigned char) (round(t * value) + 128);
		}
	}

	printf("\n\n\n");
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d\t", midct[i][j]);
		}
		printf("\n");
	}
}
*/


void dct_colors(huffman_tree_t** ht, FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]) {

	int dred[LIM][LIM], dgreen[LIM][LIM], dblue[LIM][LIM];
	dct(red, dred);

	int i, j;
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d ", dred[i][j]);
		}
		printf("\n");
	}

	dct(green, dgreen);
	dct(blue, dblue);

	vectorization_colors(ht, file, dred, dgreen, dblue);
}


void idct_colors(huffman_tree_t* root, FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]) {
	int mred[LIM][LIM], mgreen[LIM][LIM], mblue[LIM][LIM];

	revert_vectorization(root, file, mred, mgreen, mblue);

	int i, j;
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d ", mred[i][j]);
		}
		printf("\n");
	}

	idct(mred, red);
	idct(mgreen, green);
	idct(mblue, blue);

}


#endif