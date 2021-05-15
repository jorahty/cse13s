#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
	// Allocate memory for the node using malloc
	Node *n = (Node *) malloc(sizeof(Node));
	if (n) { // As long as n exists ... 
		// Set left and right children to NULL
		// Because a node should not have children when it is first created
		n->left = NULL;
		n->right = NULL;
		// Set symbol and frequency
		n->symbol = symbol;
		n->frequency = frequency;
	}
	return n;
}

void node_delete(Node **n) {
	if (n && *n) { // If n and *n are not NULL ...
		// Then ...
		// If the left child is not NUll ...	
		if (&((*n)->left)) {
			// Free the left child
        	free(&((*n)->left));
		}
		// If the right child is not NUll ...	
		if (&((*n)->right)) {
			// Free the right child
        	free(&((*n)->right));
		}
		// Finally, free *n and n (in that order)
        free(*n);
        free(n);
		// And set them to NULL
        *n = NULL;
        n = NULL;
	}
	return; // Should return NULL if malloc was unsuccessful
}

Node *node_join(Node *left, Node *right) {
	// Create a new parent node with the given nodes as its children
	Node *n = (Node *) malloc(sizeof(Node)); // Allocate memory for the parent node
	if (n) { // If malloc was successful and n is not NULL ...
		// Set left and right children
		n->left = left;
		n->right = right;
		// Set symbol
		n->symbol = '$';
		// Set frequency as the sum of the children's frequencies
		n->frequency = left->frequency + right->frequency;
	}
	return n; // Should return NULL if malloc was unsuccessful
}

void node_print(Node *n) {
	if (n) { // If n exists and is not NULL ...
		if (n->left || n->right) { // If n has children ...
			printf("Interior Node:   '%c'    %lu\n", n->symbol, n->frequency);
			printf("Left Child:      '%c'    %lu\n", n->left->symbol, n->left->frequency);
			printf("Right Child:     '%c'    %lu\n", n->right->symbol, n->right->frequency);
		} else { // If n does not have children ... 
			printf("Leaf Node:       '%c'    %lu\n", n->symbol, n->frequency);
			printf("Left Child:      None\n");
			printf("Right Child:     None\n");
		}
	}
	return;
}
