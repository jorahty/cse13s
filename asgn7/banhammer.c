#include "bv.h"
#include "ll.h"
#include "node.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {

    BitVector *bv = bv_create(16);
    bv_set_bit(bv, 8);
    bv_set_bit(bv, 6);
    bv_set_bit(bv, 11);
    bv_set_bit(bv, 6);
    bv_clr_bit(bv, 8);
    bv_clr_bit(bv, 0);

    printf("bit at %d: %d\n", 5, bv_get_bit(bv, 5));

    bv_print(bv);
    printf("Length: %d\n", bv_length(bv));

    bv_delete(&bv);

    return 0;
}
