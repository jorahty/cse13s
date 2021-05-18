#include "node.h"
#include "pq.h"

#include <stdio.h>

int main(void) {

	// Create two nodes L and R
    Node *L = node_create('a', 13);
    Node *R = node_create('f', 5);

	// Join the two nodes into P
    Node *P = node_join(L, R);

	// Create a Priority Queue
	PriorityQueue *Q = pq_create(10);
	pq_print(Q);

	// Try insterting L
	enqueue(Q, L);
	pq_print(Q);

	// Try insterting R
	enqueue(Q, R);
	pq_print(Q);

	// Try insterting P
	enqueue(Q, P);
	pq_print(Q);


	// Delete Nodes
    node_delete(&L);
    node_delete(&R);
    node_delete(&P);
	
	// Delete Priority Queue
	pq_delete(&Q);

    return 0;
}
