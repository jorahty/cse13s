#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
	// Allocate memory for a new node `n`
	Node *n = (Node *) malloc(sizeof(Node));

	// Allocate memory for the new node's oldspeak and newspeak fields
	n->oldspeak = (char *) malloc(strlen(oldspeak) + 1); // Add 1 for the null terminator
	n->newspeak = (char *) malloc(strlen(newspeak) + 1); // Same goes for newspeak

	// Copy the oldspeak and newspeak strings from the given paramters
	strcpy(n->oldspeak, oldspeak);
	strcpy(n->newspeak, newspeak);

	// Set the `next` and `previous` fields to null for now
	n->next = NULL;
	n->prev = NULL;

	// Return the new node `n`
	return n;
}

void node_delete(Node **n) {
	// If `n` and `*n` are not already null ...
	if (n && *n) {
		// Free memory allocated for oldspeak and newspeak
		free((*n)->oldspeak);
		free((*n)->newspeak);

		// Free the node
		free(*n);

		// Set pointer to null 
		*n = NULL;
	}
	return;
}

void node_print(Node *n) {
	fprintf(stderr, "→ ⎡ \"%s\" ⎤ →\n", n->oldspeak);
	fprintf(stderr, "← ⎣ \"%s\" ⎦ ←\n", n->newspeak);
	return;
}
