#include "huffman.h"
#include "node.h"
#include "pq.h"

Node *build_tree(uint64_t hist[static ALPHABET]) {

	// Initialize a priority queue
	PriorityQueue *q = pq_create(ALPHABET);
	pq_print(q);

	// Enqueue a node for every symbol in the histogram
	for (int i = 0; i < ALPHABET; i++) {
		if (hist[i] > 0) {
			enqueue(q, node_create(i, hist[i]));
		}
	}
	pq_print(q);


	return node_create('a', 3234553);
}

void build_codes(Node *root, Code table[static ALPHABET]);

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);
