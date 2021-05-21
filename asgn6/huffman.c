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

	// Rearranging the prioty into a Huffman tree
	// There are two or more nodes in the queue ...
	while (pq_size(q) >= 2) {
		// Dequeue two nodes
		Node *l;
		Node *r;
		dequeue(q, &l);
		dequeue(q, &r);
		// Put the joined nodes back in the queue
		enqueue(q, node_join(l, r));
	}

	// Now there must be only 1 node in the queue
	// This node is the root of the Huffman tree
	Node *root;
	dequeue(q, &root);
	return root;
}

void build_codes(Node *root, Code table[static ALPHABET]);

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);
