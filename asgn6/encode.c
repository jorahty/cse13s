#include "node.h"
#include "pq.h"

#include <stdio.h>

int main(void) {

    Node *L = node_create('a', 3);
    Node *R = node_create('f', 5);

    Node *P = node_join(L, R);

    Node *d = node_create('d', 4);
    Node *e = node_create('e', 5);

	PriorityQueue *Q = pq_create(10);
	enqueue(Q, L);
	enqueue(Q, R);
	enqueue(Q, P);
	enqueue(Q, d);
	enqueue(Q, e);
	printf("\n");
	pq_print(Q);
	printf("\n");

    node_delete(&L);
    node_delete(&R);
    node_delete(&P);

    return 0;
}
