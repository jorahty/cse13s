#include "node.h"

#include <stdio.h>

int main(void) {
	printf("Create and print a node ...\n");
	Node *l = node_create('a', 8);
	node_print(l);
	printf("Create and print another node ...\n");
	Node *r = node_create('f', 4);
	node_print(r);
	printf("Join nodes into one and print ...\n");
	Node *p = node_join(l, r);
	node_print(p);
	return 0;
}
