#include "huffman.h"

#include "node.h"
#include "pq.h"

#include <stdio.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Initialize a priority queue
    PriorityQueue *q = pq_create(ALPHABET);

    // Enqueue a node for every symbol in the histogram
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
			Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }

    // Print priority queue (temporary)
    printf("\nPriority Queue:\n");
    pq_print(q);
    // Rearranging the prioty queue into a Huffman tree
    // While there are two or more nodes in the queue ...
    while (pq_size(q) >= 2) {
        // Dequeue two nodes
        Node *l;
        Node *r;
        dequeue(q, &l);
        dequeue(q, &r);
        // Put the joined nodes back in the queue
        enqueue(q, node_join(l, r));
        pq_print(q);
    }
    printf("\n");

    // Now there must be only 1 node in the queue
    // This node is the root of the Huffman tree
    Node *root;
    dequeue(q, &root);
	
	// Delete the priority queue
	pq_delete(&q);

	// Return the root (which contains all the data for the entire Huffman tree
    return root;
}

static void traverse(Node *n, Code table[static ALPHABET], Code c) {
    // If this node is a leaf ...
    if (!n->left && !n->right) {
        if (n->symbol < 32) {
            printf("Found a leaf: ' ' %lu\n", n->frequency);
        } else {
            printf("Found a leaf: '%c' %lu\n", n->symbol, n->frequency);
        }
        // Then c is the code for this node's symbol
        table[n->symbol] = c;
        printf("Done with leaf so going back up ...\n");
        return;

        // Otherwise, this node is an interior node
    } else {
        printf("Found an interior node: '%c' %lu\n", n->symbol, n->frequency);
        uint8_t trash; // We don't care about the popped bits
        // Search to the left
        printf("Searching to the left ...\n");
        code_push_bit(&c, 0);
        traverse(n->left, table, c);
        code_pop_bit(&c, &trash);
        // Search to the right
        printf("Searching to the right ...\n");
        code_push_bit(&c, 1);
        traverse(n->right, table, c);
        code_pop_bit(&c, &trash);
    }

    printf("Left and right child searched so going back up ...\n");
    return;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    printf("Traversal:\n");
    traverse(root, table, c);
    printf("\n");
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root) {
    // If this node is a leaf ...
    // (If this node has no children ... )
	printf("Checking if node is a leaf ...\n");
    if (!(*root)->left && !(*root)->right) {
		printf("Node is a leaf\n");
		// Delete node
		printf("Node to delete:\n");
		node_print(*root);
		printf("Deleteing node ...\n");
		node_delete(root);
		// And go back up tree to continue searching
		printf("Going back up ...\n");
        return;
    // Otherwise, this node is an interior node
    } else {
		printf("Node is not a leaf\n");
        // Search to the left
		printf("Searching to the left\n");
        delete_tree(&((*root)->left));
        // Search to the right
		printf("Searching to the right\n");
        delete_tree(&((*root)->right));
		// Delete node
		printf("Node to delete:\n");
		node_print(*root);
		printf("Deleteing node ...\n");
		node_delete(root);
    }
	// When both left and righ children have been searched,
	// Go back up tree to continue searching
	printf("Going back up ...\n");
    return;
}
