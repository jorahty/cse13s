#include "node.h"

#include <stdio.h>

int main(void) {

    Node *a = node_create(NULL, NULL);
    printf("\n");
    node_print(a);
    printf("\n");

    a->oldspeak = "Tyrion";
    printf("\n");
    node_print(a);
    printf("\n");

    a->newspeak = "Aria";
    printf("\n");
    node_print(a);
    printf("\n");

    a->oldspeak = NULL;
    printf("\n");
    node_print(a);
    printf("\n");

    a->next = a;
    printf("\n");
    node_print(a);
    printf("\n");

    a->prev = a;
    printf("\n");
    node_print(a);
    printf("\n");

    a->next = NULL;
    printf("\n");
    node_print(a);
    printf("\n");

    a->oldspeak = "Stark";
    a->newspeak = "Lannister";
    Node *b = node_create(NULL, NULL);
    a->prev = b;
    printf("\n");
    node_print(a);
    printf("\n");

    node_delete(&a);
    node_delete(&b);

    return 0;
}
