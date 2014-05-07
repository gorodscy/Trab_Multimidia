/*
 * TRABALHO 01
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 *
 * Preparação dos blocos
 */

// Evita includes multiplos e repetidos
#ifndef _prepare_blocks_h
#define _prepare_blocks_h

#include <stdio.h>
#include <stdlib.h>
#include "save_bits.h"
#include "open_image.h"
#include "vectorization.h"

// Comprime a imagem e salva no arquivo
void send_blocks(struct colors color, FILE* file){
    // Verifica se a imagem é válida
    if(color.larg != -1) {    
        // Cria as matrizes de 8 temporárias
        unsigned char red[8][8];
        unsigned char green[8][8];
        unsigned char blue[8][8];
        
        int i, j, offsetLARG, offsetALT;
        int x=0, y=0;
        
        setSize(file, color.larg, color.alt);
        
        // Separa a imagem em blocos de 8x8 bits para cada cor
        for(offsetLARG=0; offsetLARG<color.larg; offsetLARG+=8)
        {
            for(offsetALT=0; offsetALT<color.alt; offsetALT+=8)
            {
                for (i=offsetLARG; i<offsetLARG+8; i++)
                {
                    for (j=offsetALT; j<offsetALT+8; j++)
                    {
                        blue[i%8][j%8] = color.blue[i][j];
                        green[i%8][j%8] = color.green[i][j];
                        red[i%8][j%8] = color.red[i][j];
                    }
                }

                vectorization_colors(blue, green, red);
            }
        }
        huffman_tree_t root;
        huffman_tree_t** ht = call_huffman(&root);
        // Libera a mamória da struct (que foi criada ao abrir a imagem)
        free(color.red);
        free(color.blue);
        free(color.green);
    }
    fclose(file);
}

// Le a imagem compactada e cria a estrutura da mesma
struct colors get_blocks(FILE* file){
    // Cria as matrizes de 8 temporárias
    unsigned char red[8][8];
    unsigned char green[8][8];
    unsigned char blue[8][8];
    
    struct colors result;
    
    int i, j, offsetLARG, offsetALT;
    int width=0, height=0;
    
    // Le o valor da altura e largura da imagem comprimida
    getSize(file, &width, &height);
    result.larg = width;
    result.alt = height;

    // Aloca memória 
    result.red = (unsigned char **) malloc(width*sizeof(unsigned char*));
    result.green = (unsigned char **) malloc(width*sizeof(unsigned char*));
    result.blue = (unsigned char **) malloc(width*sizeof(unsigned char*));
    
    for(i = 0; i < width; i++) {
        result.red[i] = (unsigned char*)malloc(height*sizeof(unsigned char));
        result.green[i] = (unsigned char*)malloc(height*sizeof(unsigned char));
        result.blue[i] = (unsigned char*)malloc(height*sizeof(unsigned char));
    }
    
    // Le os valores de cores da imagem, criando a estrutura original da imagem
    for(offsetLARG=0; offsetLARG<width; offsetLARG+=8)
    {
        for(offsetALT=0; offsetALT<height; offsetALT+=8)
        {
            // MUDAR!!! **************
            read_matrix(file, red, green, blue);
            
            for (i=offsetLARG; i<offsetLARG+8; i++)
            {
                for (j=offsetALT; j<offsetALT+8; j++)
                {
                    result.red[i][j] = red[i%8][j%8];
                    result.green[i][j] = green[i%8][j%8];
                    result.blue[i][j] = blue[i%8][j%8];
                }
            }
        }
    }
    fclose(file);
    
    return result;
}

#endif
