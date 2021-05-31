#include "node.h"

#include <stdio.h>

int main(void) {

	Node *n = node_create("hello", "clyde");
	node_print(n);
	node_delete(&n);

    return 0;
}
