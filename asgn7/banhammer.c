#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    LinkedList *ll = ll_create(true);

	ll_insert(ll, "Stark", "Lannister");
	ll_insert(ll, "King", NULL);
	ll_insert(ll, "Winterfell", NULL);
	ll_insert(ll, "Sam", "Gilly");

	printf("\n");
    ll_print(ll);
	printf("\n");

	ll_delete(&ll);

    return 0;
}
