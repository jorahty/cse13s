#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    HashTable *ht = ht_create(8, true);
    ht_insert(ht, "Bro", "Mama");
    ht_insert(ht, "Arya", "Sansa");
    ht_insert(ht, "Okay", "Then");
    ht_insert(ht, "bruh", "moment");
    ht_insert(ht, "yes", "sit");
    ht_insert(ht, "sure", "fine");
    ht_insert(ht, "hello", "alright");
    ht_print(ht);

    ht_delete(&ht);

    return 0;
}
