#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    BloomFilter *bf = bf_create(50);
    bf_insert(bf, "Tyrion");
    bf_insert(bf, "Cercei");
    bf_insert(bf, "Jaime");
    bf_insert(bf, "Joffrey");
    fprintf(stderr, "%s\n", bf_probe(bf, "Tyrion") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Tywin") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Arya") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Jaime") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Cercei") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Sansa") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Stark") ? "true" : "false");
    fprintf(stderr, "%s\n", bf_probe(bf, "Joffrey") ? "true" : "false");

    bf_print(bf);
    fprintf(stderr, "Size: %d\n", bf_size(bf));
    fprintf(stderr, "Count: %d\n", bf_count(bf));

    bf_delete(&bf);

    return 0;
}
