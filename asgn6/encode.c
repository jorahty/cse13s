#include "node.h"
#include "pq.h"

#include <stdio.h>

int main(void) {
	PriorityQueue *pq = pq_create(8);
	pq_print(pq);

	enqueue(pq, node_create('a', 323));
	enqueue(pq, node_create('b', 32));
	enqueue(pq, node_create('c', 3));
	pq_print(pq);

	Node *trash;
	dequeue(pq, &trash);
	dequeue(pq, &trash);
	dequeue(pq, &trash);
	pq_print(pq);

	enqueue(pq, node_create('a', 323));
	enqueue(pq, node_create('b', 32));
	enqueue(pq, node_create('c', 3));
	pq_print(pq);

	enqueue(pq, node_create('d', 42));
	pq_print(pq);

	enqueue(pq, node_create('e', 69));
	pq_print(pq);

	enqueue(pq, node_create('f', 420));
	pq_print(pq);

	enqueue(pq, node_create('g', 12));
	pq_print(pq);

	enqueue(pq, node_create('h', 7));
	pq_print(pq);

    return 0;
}
