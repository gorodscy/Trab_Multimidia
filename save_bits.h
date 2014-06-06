/*
 * TRABALHO 03
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

#define TAKE_N_BITS_FROM(b, p, n) ((b) >> (p)) & ((1 << (n)) - 1)

int nbits_freq(int nbits, int freq) {
    int result = 0;
    
    nbits = nbits == 32 ? 0 : nbits;
    
    if (freq > 64 || nbits > 31) {
        printf("Tamanho de frequência inválida\n");
        return 0;
    }
    freq = freq-1; /* Ajusta pra frequencia 1 ser o valor zero. Economizando 1 bit. */
    
    result = nbits;
    result = result << 6;
    result |= freq;

    return result;
}

void decode_nbits_freq(int code, int* nbits, int* freq) {
    *freq = TAKE_N_BITS_FROM(code, 0, 6);
    *freq = *freq + 1;
    *nbits = TAKE_N_BITS_FROM(code, 6, 5); 
    /* *nbits = TAKE_N_BITS_FROM(code, 6, 3);
    *nbits = *nbits ? *nbits : 8; */
    *nbits = *nbits ? *nbits : 32;
}

/*
 * Salva o tamanho da imagem no arquivo compactado
 */
void setSize(FILE* file, int width, int height){
    rewind(file);
    fwrite(&width, 4, 1, file);
    fwrite(&height, 4, 1, file);
}

/*
 * Le o tamanho da imagem no arquivo compactado
 */
void getSize(FILE* file, int* width, int* height){
    rewind(file);
    fread(width, 4, 1, file);
    fread(height, 4, 1, file);
#ifdef DEBUG4
    printf("w: %d\n", *width);
    printf("h: %d\n", *height);
#endif
}

/*
 * Pega o tamanho em bits do "byte"
 */
int bit_size_of(int byte){
    
    int i;
    for (i=32; i>0; i--) {
        if (TAKE_N_BITS_FROM(byte, i-1, 1)) {
            return i;
        }
    }
    return 1;
}

/*
 * Insere os bits dentro do byte para ser salvo no arquivo
 */
int write_bit(FILE* file, bool bit){
    static unsigned char byte = 0x00;
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
        byte = 0x00;
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

/*
 * Insere os bits dentro do byte até completar 8 bits e o escreve no arquivo
 */
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



/*
 * Le cada bit do arquivo compactado
 */
bool read_bit(FILE* file){
    static int pos=7;
    static int byte;
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

/*
 * Separa os valores, gerando os bytes de cores
 */
unsigned char read_bits(FILE* file, int qtt){
    int i;
    unsigned char byte = 0x00;
    
    for (i=0; i<qtt; i++) {
        byte <<= i?1:0;
        byte |= read_bit(file);
    }
    return byte;
}

/*
 * Separa os valores, gerando os bytes de cores
 */
int read_bits2(FILE* file, int qtt){
    int i;
    int byte = 0;
    
    for (i=0; i<qtt; i++) {
        byte <<= i?1:0;
        byte |= read_bit(file);
    }
    return byte;
}



#endif
