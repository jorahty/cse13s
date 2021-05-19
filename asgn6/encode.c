#include "node.h"
#include "pq.h"

#include <stdio.h>

int main(void) {

    PriorityQueue *pq = pq_create(8);

    Node *a = node_create('a', 234);
    Node *Y = node_create('Y', 7);
    Node *A = node_create('A', 43);
    Node *o = node_create('o', 114);

    Node *parent = node_join(o, a);

    enqueue(pq, a);
    enqueue(pq, Y);
    enqueue(pq, A);
    enqueue(pq, o);
    enqueue(pq, parent);

    pq_print(pq);

    Node *trash;
    dequeue(pq, &trash);
    dequeue(pq, &trash);
    dequeue(pq, &trash);
    dequeue(pq, &trash);

    pq_print(pq);

    enqueue(pq, Y);

    pq_print(pq);

    enqueue(pq, a);
    enqueue(pq, Y);
    enqueue(pq, A);
    enqueue(pq, o);
    enqueue(pq, parent);

    pq_print(pq);

    node_delete(&a);
    node_delete(&a);
    node_delete(&Y);
    node_delete(&A);
    node_delete(&o);
    node_delete(&parent);
    pq_delete(&pq);
    pq_delete(&pq);

    return 0;
}
