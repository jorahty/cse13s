#include "node.h"

#include <stdio.h>

int main(void) {
    printf("Creating node L with symbol 'a' and frequency 8 ...\n");
    Node *L = node_create('a', 8);
    printf("Printing node L ...\n");
    node_print(L);
    printf("Creating node R with symbol 'f' and frequency 4 ...\n");
    Node *R = node_create('f', 4);
    printf("Printing node R ...\n");
    node_print(R);
    printf("Joining nodes L and R into new node P ...\n");
    Node *P = node_join(L, R);
    printf("Printing node P ...\n");
    node_print(P);
    printf("Deleting nodes L, R, and P ...\n");
    node_delete(&L);
    node_delete(&R);
    node_delete(&P);
    return 0;
}
