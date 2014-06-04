/*
 * TRABALHO 03
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 *
 * Huffman
 */

#ifndef _MULTIMEDIA_HUFFMAN_H_
#define _MULTIMEDIA_HUFFMAN_H_

#include "save_bits.h"

#define HUFFMAN_TYPE_NODE 0
#define HUFFMAN_TYPE_LEAF 1

typedef unsigned short int buffer_t;

typedef struct _huffman_tree_t {
	int count;								/* quantidade de occorencias do no */
	char type;								/* se e um no ou folha */
	struct _huffman_tree_t *parent;			/* pai do no ou folha */
	union {
		int value;							/* valor da folha */
		struct _huffman_tree_t *childs[2];	/* filhos do no */
	} node;
} huffman_tree_t;

int ht_qsort_compare(const void *a, const void *b) {
	huffman_tree_t *ha = *((huffman_tree_t**)a);
	huffman_tree_t *hb = *((huffman_tree_t**)b);
	return (int)(ha->count - hb->count);
}

void ht_qsort(huffman_tree_t* q[], int buffer_size) {
	qsort(q, buffer_size, sizeof(huffman_tree_t*), ht_qsort_compare);
}

huffman_tree_t** ht_create(buffer_t* buffer, int buffer_size, huffman_tree_t **root) {
	huffman_tree_t **symbols = (huffman_tree_t**)calloc(buffer_size, sizeof(huffman_tree_t*));
	huffman_tree_t **priorityQueue = (huffman_tree_t**)calloc(buffer_size, sizeof(huffman_tree_t*));

    int i;
	/* cria um simbolo para cada folha e o adiciona na fila de prioridades */
	for ( i = 0; i < buffer_size; i++ ) {
		huffman_tree_t *node = (huffman_tree_t*)malloc(sizeof(huffman_tree_t));
		node->count = buffer[i];
		node->type = HUFFMAN_TYPE_LEAF;
		node->node.value = i;
		priorityQueue[i] = node;
		symbols[i] = node;
	}

	/* ordena as folhas pela maior frequencia */
	ht_qsort(priorityQueue, buffer_size);

	int lastNodeIndex = buffer_size-1;

	/*
	 * 	Os valores menos frequentes sao os ultimos, e com isso eles se tornam filhos de um no,
	 *	ate que so reste uma folha, que e a raiz da arvore.
	 */
	while ( lastNodeIndex > 0 ) {
		/* pega os dois ultimos valores */
		huffman_tree_t *last = priorityQueue[lastNodeIndex];
		huffman_tree_t *almostLast = priorityQueue[lastNodeIndex - 1];
		lastNodeIndex -= 2;
		/* cria um novo no */
		huffman_tree_t *node = (huffman_tree_t*)malloc(sizeof(huffman_tree_t));
		node->count = last->count + almostLast->count;
		node->type = HUFFMAN_TYPE_NODE;
		node->node.childs[0] = almostLast;
		node->node.childs[1] = last;
		last->parent = almostLast->parent = node;
		/* insere o no na fila novamente */
		priorityQueue[++lastNodeIndex] = node;
        
        int i;
		/* ordena os nos novamente */
		for ( i = lastNodeIndex; i > 0 && priorityQueue[i]->count > priorityQueue[i - 1]->count; i-- ) {
			/* troca os nos */
			huffman_tree_t *temp;
			temp = priorityQueue[i];
			priorityQueue[i] = priorityQueue[i - 1];
			priorityQueue[i - 1] = temp;
		}
	}

	/* a arvore esta formada, sendo o no restante a raiz*/
	*root = priorityQueue[0];
	free(priorityQueue);

	return symbols;
}

void ht_destroy_rec(huffman_tree_t *root) {
	if ( root->type == HUFFMAN_TYPE_NODE ) {
		ht_destroy_rec(root->node.childs[0]);
		ht_destroy_rec(root->node.childs[1]);
	}
	free(root);
}

void ht_destroy(huffman_tree_t **symbols, huffman_tree_t *root) {
    ht_destroy_rec(root);
	free(symbols);
}

int bits_to_i(bool* bits, int buffer_size, int length){
    int i, byte = 0;
    /* escreve os bits na ordem certar */
	for ( i = length - 1; i >= 0; i-- ) {
        byte <<= (i==length-1)? 0 : 1; /* pula a primeira iteracao */
        byte |= bits[i];
	}
    return byte;
}

unsigned short int ht_encode(huffman_tree_t **symbols, int buffer_size, int input, int *bs) {
	unsigned short int length = 0;
	bool bits[buffer_size];

	huffman_tree_t *symbol;
	huffman_tree_t *parent;

	symbol = symbols[input];
	parent = symbol->parent;

	/* preenche os bits do codigo de huffman na ordem reversa */
	while ( parent ) {
		bits[length] = symbol == parent->node.childs[1];
		length++;
		symbol = parent;
		parent = symbol->parent;
	}
    *bs = bits_to_i(bits, buffer_size, length);

	return length;
}

unsigned short int ht_decode(huffman_tree_t *root, int* output, FILE *bs) {
	bool bit = 0;
	unsigned short int length = 0;

	/* faz a leitura desde o topo da arvore até encontrar uma folha */
	while ( root->type == HUFFMAN_TYPE_NODE ) {
		bit = read_bit(bs);
		/* decide para qual filho deve ir */
        root = bit ? root->node.childs[1] : root->node.childs[0];
        length++;
	}

	/* folha com o valor do codifo de huffman */
	*output = root->node.value;

	/* quantidade de bits */
	return length;
}

#endif
