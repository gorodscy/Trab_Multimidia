/*
 * TRABALHO 01
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 *
 * Gravação de Bits
 */

#ifndef _SAVE_BITS_h
#define _SAVE_BITS_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAKE_N_BITS_FROM(b, p, n) ((b) >> (p)) & ((1 << (n)) - 1)

int nbits_freq(int nbits, int freq) {
    int result = 0x00;
    
    nbits = nbits == 8 ? 0 : nbits;
    
    if (freq > 64 || nbits > 7) {
        printf("Tamanho de frequência inválida\n");
        return 0;
    }
    freq = freq-1; // Ajusta pra frequencia 1 ser o valor zero. Economizando 1 bit.
    
    result = nbits;
    result = result << 6;
    result |= freq;

    return result;
}

void decode_nbits_freq(int code, int* nbits, int* freq) {
    *freq = TAKE_N_BITS_FROM(code, 0, 6);
    *freq = *freq + 1;
    *nbits = TAKE_N_BITS_FROM(code, 6, 3);
    *nbits = *nbits ? *nbits : 8;
}

// Salva o tamanho da imagem no arquivo compactado
void setSize(FILE* file, int width, int height){
    rewind(file);
    fwrite(&width, 4, 1, file);
    fwrite(&height, 4, 1, file);
}

// Le o tamanho da imagem no arquivo compactado
void getSize(FILE* file, int* width, int* height){
    rewind(file);
    fread(width, 4, 1, file);
    fread(height, 4, 1, file);
#ifdef DEBUG4
    printf("w: %d\n", *width);
    printf("h: %d\n", *height);
#endif
}

// Pega o tamanho em bits do "byte"
int bit_size_of(int byte){
    
    int i;
    for (i=8; i>0; i--) {
        if (TAKE_N_BITS_FROM(byte, i-1, 1)) {
            return i;
        }
    }
    return 1;
}

// Insere os bits dentro do byte para ser salvo no arquivo
int write_bit(FILE* file, bool bit){
    static unsigned char byte = 0x00;//0b00000000;
    static int pos=0;
    
    byte <<= 1;
    byte |= bit;
#ifdef DEBUG
    printf("%d", bit);
#endif

    if (pos == 7) {
#ifdef DEBUG3
        printf("%X ", byte);
#endif
        pos = 0;
        fwrite(&byte, 1, 1, file);
        byte = 0x00;//0b00000000;
    }
    else {
        pos++;
    }
    return pos;
}

void write_bit_flush(FILE* file) {
    while (write_bit(file, 0)) {
    }
}

// Insere os bits dentro do byte até completar 8 bits e o escreve no arquivo
void write_byte(FILE* file, int byte, unsigned int size){
    int i;
    bool bit;
    
    for (i=1; i<=size; i++) {
        bit = TAKE_N_BITS_FROM(byte, size-i, 1);
        write_bit(file, bit);
    }
#ifdef DEBUG
    printf(" ");
#endif
}

//Escreve os valores das matrizes de cores no arquivo compactado
void grava_bits(FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]){
    
    unsigned int i, j, k, a;
    
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
#ifdef DEBUG
            printf("R:%d G:%d B:%d - ", red[i][j], green[i][j], blue[i][j]);
#endif
            
            unsigned int size = bit_size_of(red[i][j]);
            write_byte(file, size-1, 3); // - Escreve ultimos 3 bits no arquivo
            write_byte(file, red[i][j], size); // - Escreve ultimos size bits de red[i][j]
            
            size = bit_size_of(green[i][j]);
            write_byte(file, size-1, 3); // - Escreve ultimos 3 bits no arquivo
            write_byte(file, green[i][j], size); // - Escreve ultimos size bits de green[i][j]
            
            size = bit_size_of(blue[i][j]);
            write_byte(file, size-1, 3); // - Escreve ultimos 3 bits no arquivo
            write_byte(file, blue[i][j], size); // - Escreve ultimos size bits de blue[i][j]
        }
    }
}

// Le cada bit do arquivo compactado
bool read_bit(FILE* file){
    static int pos=7;
    static unsigned char byte;
    bool bit;
    
    if (pos < 7) {
        pos++;
    }
    else {
        pos = 0;
        fread(&byte, 1, 1, file);
    }
    bit = TAKE_N_BITS_FROM(byte, 7, 1);
    byte <<= 1;

    return bit;
}

// Separa os valores, gerando os bytes de cores
unsigned char read_bits(FILE* file, int qtt){
    int i;
    unsigned char byte = 0x00;//0b00000000;
    
    for (i=0; i<qtt; i++) {
        byte <<= i?1:0;
        byte |= read_bit(file);
    }
    return byte;
}

// Le as matrizes 8x8 do arquivo compactado
void read_matrix(FILE* file, unsigned char red[8][8], unsigned char green[8][8], unsigned char blue[8][8]){
    
    unsigned int i, j, p=0;
    int size, byte;
    
    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            
            size = read_bits(file, 3);
            red[i][j] = read_bits(file, size+1);
            
            size = read_bits(file, 3);
            green[i][j] = read_bits(file, size+1);
            
            size = read_bits(file, 3);
            blue[i][j] = read_bits(file, size+1);
            
#ifdef DEBUG2
            printf("R:%d G:%d B:%d - ", red[i][j], green[i][j], blue[i][j]);
#endif
            
        }
    }
}

#endif
