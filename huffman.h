/*
 * TRABALHO 01
 * Grupo 04:
 * Vanessa Apolinário de Lima
 * Caio Augusto da Silva Gomes
 * Fernando Cury Gorodscy
 * 
 * Biblioteca Código de Huffman
 */

#ifndef _MULTIMEDIA_HUFFMAN_H_
#define _MULTIMEDIA_HUFFMAN_H_

#include "open_image.h"

#define HUFFMAN_TYPE_NODE 0
#define HUFFMAN_TYPE_LEAF 1

typedef unsigned long long int buffer_element_t;
typedef buffer_element_t buffer_t[256];

typedef struct _huffman_tree_t {
	int count;									// how many ocurrences this node or leaf has.
	char type;									// is this a leaf or a node?
	struct _huffman_tree_t *parent;					// parent of this leaf/node.
	union {
		char value;								// value of the leaf.
		struct _huffman_tree_t *childs[2];			// node childs.
	} node;
} huffman_tree_t;

/**
 *	Create a Huffman Tree from the buffer.
 *	@var buffer The buffer with the count of all the bytes.
 *	@var root The root of the tree.
 *	@return Return an array of all the tree nodes.
 */
 // create with elements matrix at run_length.h
huffman_tree_t** ht_create(buffer_t buffer, huffman_tree_t **root);

/**
 *	Destroy a Huffman Tree.
 *	@var root The root of the tree.
 */
void ht_destroy(huffman_tree_t **symbols, huffman_tree_t *root);

/**
 *	Encode a byte, writing it to the specified stream.
 *	@var symbols Array of tree nodes (NOT THE ROOT NODE!).
 *	@var input Byte to be encoded.
 *	@var bs Bit stream where the encoded data will be written.
 *	@return How many bits were written (no flush is performed).
 */
unsigned short int ht_encode(huffman_tree_t **symbols, char input, int /*bitstream_t*/ *bs);

/**
 *	Decode a byte from the given stream.
 *	@var root Root of the tree.
 *	@var output The decoded byte.
 *	@var bs Bit stream where the encoded data relies.
 *	@return How many bits were read.
 */
unsigned short int ht_decode(huffman_tree_t *root, char output, int /*bitstream_t*/ *bs);

#endif
