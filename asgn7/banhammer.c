#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    LinkedList *ll = ll_create(true);
    ll_insert(ll, "Jon", "Snow");
    ll_insert(ll, "Hound", NULL);
    ll_insert(ll, "Lannister", "Stark");
    ll_insert(ll, NULL, NULL);
    ll_insert(ll, "Dorne", "Winterfell");

    printf("\n");
    ll_print(ll);
    printf("\n");

    node_print(ll_lookup(ll, "Jon"));

    printf("\n");
    ll_print(ll);
    printf("\n");

    LinkedList *ll2 = ll_create(false);

    printf("\n");
    ll_print(ll2);
    printf("\n");

    ll_delete(&ll2);
    ll_delete(&ll);

    return 0;
}
