#include <stdio.h>
#include <stdlib.h>
#include "dct.h"

#define LIM 8

int main(void) {

	unsigned char mat[LIM][LIM];
	int out[LIM][LIM];
	//int end[LIM][LIM];
	int i, j, a = 1;
/*
	mat = (unsigned char**)malloc(LIM*sizeof(unsigned char*));

    for(i = 0; i < LIM; i++)
        mat[i] = (unsigned char*)malloc(LIM*sizeof(unsigned char));
*/

    mat[0][0] = 154;
    mat[0][1] = 123;
    mat[0][2] = 123;
    mat[0][3] = 123;
    mat[0][4] = 123;
    mat[0][5] = 123;
    mat[0][6] = 123;
    mat[0][7] = 136;

    mat[1][0] = 192;
    mat[1][1] = 180;
    mat[1][2] = 136;
    mat[1][3] = 154;
    mat[1][4] = 154;
    mat[1][5] = 154;
    mat[1][6] = 136;
    mat[1][7] = 110;

    mat[2][0] = 254;
    mat[2][1] = 198;
    mat[2][2] = 154;
    mat[2][3] = 154;
    mat[2][4] = 180;
    mat[2][5] = 154;
    mat[2][6] = 123;
    mat[2][7] = 123;

    mat[3][0] = 239;
    mat[3][1] = 180;
    mat[3][2] = 136;
    mat[3][3] = 180;
    mat[3][4] = 180;
    mat[3][5] = 166;
    mat[3][6] = 123;
    mat[3][7] = 123;

    mat[4][0] = 180;
    mat[4][1] = 154;
    mat[4][2] = 136;
    mat[4][3] = 167;
    mat[4][4] = 166;
    mat[4][5] = 149;
    mat[4][6] = 136;
    mat[4][7] = 136;

    mat[5][0] = 128;
    mat[5][1] = 136;
    mat[5][2] = 123;
    mat[5][3] = 136;
    mat[5][4] = 154;
    mat[5][5] = 180;
    mat[5][6] = 198;
    mat[5][7] = 154;

    mat[6][0] = 123;
    mat[6][1] = 105;
    mat[6][2] = 110;
    mat[6][3] = 149;
    mat[6][4] = 136;
    mat[6][5] = 136;
    mat[6][6] = 180;
    mat[6][7] = 166;

    mat[7][0] = 110;
    mat[7][1] = 136;
    mat[7][2] = 123;
    mat[7][3] = 123;
    mat[7][4] = 123;
    mat[7][5] = 136;
    mat[7][6] = 154;
    mat[7][7] = 136;

/*
	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			mat[j][i] = (unsigned char) 255;
			a++;
		}
	}

	//dct(mat, out);
	//mat[0][0] = 0;

	//idct(out, end);

	for(i = 0; i < LIM; i++) {
		for(j = 0; j < LIM; j++) {
			printf("%d ", end[i][j]);
		}
		printf("\n");
	}	

*/
	dct2(mat, out);
	idct2(out,mat);


}