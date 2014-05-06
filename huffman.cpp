#include "huffman.h"

int ht_qsort_compare(const void *a, const void *b) {
	huffman_tree_t *ha = *((huffman_tree_t**)a);
	huffman_tree_t *hb = *((huffman_tree_t**)b);
	return (int)(ha->count - hb->count);
}

void ht_qsort(huffman_tree_t* q[]) {
	qsort(q, 256, sizeof(huffman_tree_t*), ht_qsort_compare);
}

huffman_tree_t** ht_create(buffer_t buffer, huffman_tree_t **root) {
	huffman_tree_t **symbols = (huffman_tree_t**)calloc(256, sizeof(huffman_tree_t*));
	huffman_tree_t **priorityQueue = (huffman_tree_t**)calloc(256, sizeof(huffman_tree_t*));

	// create a leaf for each symbol and add it to the priority queue.
	for ( int i = 0; i < 256; i++ ) {
		huffman_tree_t *node = (huffman_tree_t*)malloc(sizeof(huffman_tree_t));
		node->count = buffer[i];
		node->type = HUFFMAN_TYPE_LEAF;
		node->node.value = i;
		priorityQueue[i] = node;
		symbols[i] = node;
	}

	// sort the queue starting with the highest frequencies (count field, actually).
	ht_qsort(priorityQueue);

	uint8_t lastNodeIndex = 255;
	/*
	 * 	The least frequent symbols are the last ones.
	 *	Let's replace them with a node, so that they become childs of the node.
	 *	Repeat until only one node is left. This last node is the root of our tree.
	 */
	while ( lastNodeIndex > 0 ) {
		// take two nodes.
		huffman_tree_t *last = priorityQueue[lastNodeIndex];
		huffman_tree_t *almostLast = priorityQueue[lastNodeIndex - 1];
		lastNodeIndex -= 2;
		// make a new node.
		huffman_tree_t *node = (huffman_tree_t*)malloc(sizeof(huffman_tree_t));
		node->count = last->count + almostLast->count;
		node->type = HUFFMAN_TYPE_NODE;
		node->node.childs[0] = almostLast;
		node->node.childs[1] = last;
		last->parent = almostLast->parent = node;
		// insert the new node at the end of the queue.
		priorityQueue[++lastNodeIndex] = node;
		// sort the nodes.
		for ( int i = lastNodeIndex; i > 0 && priorityQueue[i]->count > priorityQueue[i - 1]->count; i-- ) {
			// swap nodes.
			huffman_tree_t *temp;
			temp = priorityQueue[i];
			priorityQueue[i] = priorityQueue[i - 1];
			priorityQueue[i - 1] = temp;
		}
	}

	// believe it or not, we have our tree!
	*root = priorityQueue[0];
	MM_FREE(priorityQueue);
	return symbols;
}

void ht_destroy_rec(huffman_tree_t *root) {
	if ( root->type == HUFFMAN_TYPE_NODE ) {
		ht_destroy_rec(root->node.childs[0]);
		ht_destroy_rec(root->node.childs[1]);
	}
	MM_FREE(root);
}

void ht_destroy(huffman_tree_t **symbols, huffman_tree_t *root) {
    ht_destroy_rec(root);
	MM_FREE(symbols);
}

uint16_t ht_encode(huffman_tree_t **symbols, uint8_t input, bitstream_t *bs) {
	uint16_t length = 0;
	bool bits[256];

	huffman_tree_t *symbol;
	huffman_tree_t *parent;

	symbol = symbols[input];
	parent = symbol->parent;

	// this will fill the bits buffer at the reverse order.
	while ( parent ) {
		bits[length] = symbol == parent->node.childs[1];
		length++;
		symbol = parent;
		parent = symbol->parent;
	}

	// write data at the right order.
	for ( int16_t i = (int16_t)length - 1; i >= 0; i-- ) {
		bs_write(bs, bits[i]);
	}

	return length;
}

uint16_t ht_decode(huffman_tree_t *root, uint8_t &output, bitstream_t *bs) {
	bool bit = 0;
	uint16_t length = 0;

	// while we are working on a leaf...
	while ( root->type == HUFFMAN_TYPE_NODE ) {
		if ( !bs_read(bs, bit) ) {
			// corrupted data!
			return 0;
		}
		// which child should we take a look?
        root = bit ? root->node.childs[1] : root->node.childs[0];
        length++;
	}

	// root variable contains our data!
	output = root->node.value;

	// how many bits we consumed?
	return length;
}
