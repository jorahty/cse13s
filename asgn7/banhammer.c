#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    HashTable *ht = ht_create(7, true);

    ht_insert(ht, "Stark", "Lannister");
    ht_insert(ht, "Arya", "Hound");
    ht_insert(ht, "Mountain", "King");
    ht_insert(ht, "Landing", "Winterfell");
    ht_insert(ht, "Dorne", NULL);
    ht_insert(ht, "White", "Walker");
    ht_insert(ht, "Wall", "Night");
    ht_insert(ht, "Watch", "Red");
    ht_insert(ht, "Women", "Bastard");
    ht_insert(ht, "Tyrion", "Jaime");
    ht_insert(ht, "Cercei", "Sansa");
    ht_insert(ht, "Tywin", "Shae");
    ht_insert(ht, "Robb", "Bran");
    ht_insert(ht, "Queen", "Tyrell");

    ht_print(ht);
    fprintf(stderr, "Size: %d\n", ht_size(ht));
    fprintf(stderr, "Count: %d\n", ht_count(ht));

    ht_lookup(ht, "Stark");
    ht_lookup(ht, "Stark");
    ht_lookup(ht, "Dorne");
    ht_lookup(ht, "Wall");

    ht_print(ht);
    fprintf(stderr, "Size: %d\n", ht_size(ht));
    fprintf(stderr, "Count: %d\n", ht_count(ht));

    ht_delete(&ht);

    return 0;
}
