/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 *
 * Main
 */

#include <stdio.h>
#include <stdlib.h>
#include "prepare_blocks.h"

int main(int argc, char** argv)
{	

	if(argc < 4) {
		printf("Missing parameters for the function:\n");
		printf("	To compress:\n");
		printf("		./main 0 input_image.BMP compressed_image.bin\n");
		printf("\n 		 					or\n");
		printf("	To uncompress:\n");
		printf("		./main 1 compressed_image.bin output_image.BMP\n");
		return 0;
	}

	/* Comprime a imagem
	 * primeira imagem - imagem normal em BMP
	 * segunda imagem - imagem comprimida
	 */
	if(atoi(argv[1]) == 0) {
    	send_blocks(open_image(argv[2]), fopen(argv[3],"wb+"));
    }
    else if(atoi(argv[1]) == 1) {
	    /* Realiza a leitura do arquivo comprimido */
	    struct colors img = get_blocks(fopen(argv[2], "rb+"));
	    /* remonta o arquivo BMP */
	    uncompress_image(argv[3], argv[2], img);
	}

    return 0;
}
