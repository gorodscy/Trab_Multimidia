/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Preparação da Imagem
 */

/* Evita includes multiplos e repetidos */
#ifndef OPEN_IMAGE_H
#define OPEN_IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "save_bits.h"
#include "prepare_blocks.h"
#include "huffman.h"


#pragma pack(push,2)
struct bitmap {
    int larg;
    int alt;
    short int planos_cor; /* Planos de cor(sempre 1) */
    short int bpp; /* Bits por pixel */
};
#pragma pack(pop)

/* Estrutura para leitura das cores,
 * Sendo usada para os blocos de 8 e para a imagem completa
 */
struct colors {
    int larg;
    int alt;
	unsigned char **red;
	unsigned char **green;
	unsigned char **blue;
};

/*
 * Abre a imagem e realiza a leitura do cabeçalho e dos pixels
 */
struct colors open_image(char *file) {
    int i, j;
    short int planos_cor, bpp;
	FILE* img;
    struct colors color;

    /* Abre arquivo no modo binario */
    img = fopen(file, "r+b");

    /* check if the image is open */
    if(img == NULL) {
    	printf("Invalid image file path.\n");
        color.larg = -1;
    	return color;
    }

    /* Pula a parte padrão do cabeçalho BMP */
    fseek(img, 18, SEEK_SET);

    /* Le a altura e largura da imagem */
    fread(&(color.larg), sizeof(int), 1, img);
    fread(&(color.alt), sizeof(int), 1, img);

    /* Verifica se a imagem tem tamanhos divisíveis por 8 pixels */
    if( color.larg % 8 != 0 && color.alt % 8 != 0 ) {
    	printf("The size of the image is not a multiple of 8.\n");
    	color.larg = -1;
        return color;
    }

    /* Le a quantidade de planos e de bits por pixel */
    fread(&(planos_cor), sizeof(short int), 1, img);
    fread(&(bpp), sizeof(short int), 1, img);

    /* Verifica se a imagem possui 24 bits por pixel (1 byte por cor) */
    if(bpp != 24) {
    	printf("The number of bits per colour is different then 24.\n");
    	color.larg = -1;
        return color;
    }

    /* Pula o restante padrão do cabeçalho
     * 24 - current
     * 54 - SET
     */
    fseek(img, 24, SEEK_CUR);

    /* Armazena espaço na memória para as matrizes */
    color.blue = (unsigned char**)malloc(color.larg*sizeof(unsigned char*));
    color.green = (unsigned char**)malloc(color.larg*sizeof(unsigned char*));
    color.red = (unsigned char**)malloc(color.larg*sizeof(unsigned char*));

    for(i = 0; i < color.larg; i++) {
        color.blue[i] = (unsigned char*)malloc(color.alt*sizeof(unsigned char));
        color.green[i] = (unsigned char*)malloc(color.alt*sizeof(unsigned char));
        color.red[i] = (unsigned char*)malloc(color.alt*sizeof(unsigned char));
    }

    /* Realiza a leitura das cores e aloca na struct */
    for(i = 0; i < color.larg; i++) {
    	for(j = 0; j < color.alt; j++) {
		    fread(&(color.blue[i][j]), sizeof(unsigned char), 1, img);
		    fread(&(color.green[i][j]), sizeof(unsigned char), 1, img);
		    fread(&(color.red[i][j]), sizeof(unsigned char), 1, img);
		}
	} 
    
	return color;
}

/*
 * Uncompress the image, creating a BMP file
 */
void uncompress_image(char *out, char *in, struct colors c) {
     /* Abre os arquivos que será descomprimido e do arquivo de saída */
     FILE *f1, *f2;
     f1 = fopen(out, "wb+");
     f2 = fopen(in, "r+b");

     /* Cria variáveis para realizar leitura e armazenamento */
     int w, h, size, i, j;
     short int b;
     unsigned char a;

     /* Insere o começo padrão do BMP header */
     a = 0x42;
     fwrite(&a, sizeof(unsigned char), 1, f1);
     a = 0x4D;
     fwrite(&a, sizeof(unsigned char), 1, f1);
     
     /* Le o tamanho da imagem do arquivo comprimido */
     getSize(f2, &w, &h);
     size = 54 + (w*h*3);
     /* Insere o tamanho em bytes no arquivo BMP */
     fwrite(&size, sizeof(int), 1, f1);
     
     a = 0x00;
     for(i = 0; i < 4; i++) 
     	fwrite(&a, sizeof(unsigned char), 1, f1);
   	
     /* Insere o tamanho do cabeçalho no arquivo BMP */
     size = 54;
     fwrite(&size, sizeof(int), 1, f1);
     
     /* Escreve o tamanho do DIB header */
     size = 40;
     fwrite(&size, sizeof(int), 1, f1);
     
     /* Escreve a altura e a largura no arquivo BMP */
     fwrite(&w, sizeof(int), 1, f1);
     fwrite(&h, sizeof(int), 1, f1);
     
     /* DIB Header padrão */
     b = 1;
     fwrite(&b, sizeof(short int), 1, f1);
     b = 24;
     fwrite(&b, sizeof(short int), 1, f1);
     size = 0;
     fwrite(&size, sizeof(int), 1, f1);

     /* Tamanho dos pixel em si */
     size = w*h*3;
     fwrite(&size, sizeof(int), 1, f1);

     size = 0;
     for(i = 0; i < 4; i++)
     	fwrite(&size, sizeof(int), 1, f1);
     
     /* Escreve os valores das cores de cada pixel */
     for(i = 0; i < w; i++) {
        for(j = 0; j < h; j++) {
            fwrite(&(c.blue[i][j]), sizeof(unsigned char), 1, f1);
            fwrite(&(c.green[i][j]), sizeof(unsigned char), 1, f1);
            fwrite(&(c.red[i][j]), sizeof(unsigned char), 1, f1);
        }
     }
     /* Fecha os arquivos da imagem comprimida e do arquivo BMP */
     fclose(f1);
     fclose(f2);

     /* Libera a mamória usada no método get_blocks */
     free(c.blue);
     free(c.green);
     free(c.red);
}


#endif /* OPEN_IMAGE_H */
