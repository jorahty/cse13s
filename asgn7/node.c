#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak) {
    // Allocate memory for a new node `n`
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }

    // Set n->oldspeak
    if (oldspeak) {
        n->oldspeak = (char *) malloc(strlen(oldspeak) + 1);
        if (n->oldspeak == NULL) {
            free(n);
            n = NULL;
            return NULL;
        }
        strcpy(n->oldspeak, oldspeak);
    } else {
        n->oldspeak = NULL;
    }

    // Set n->newspeak
    if (newspeak) {
        n->newspeak = (char *) malloc(strlen(newspeak) + 1);
        if (n->newspeak == NULL) {
            free(n);
            n = NULL;
            return NULL;
        }
        strcpy(n->newspeak, newspeak);
    } else {
        n->newspeak = NULL;
    }

    // Set the `next` and `previous` fields to null for now
    n->next = NULL;
    n->prev = NULL;

    // Return the new node `n`
    return n;
}

void node_delete(Node **n) {
    if (n && *n) {
        // Free memory allocated for oldspeak
        if ((*n)->oldspeak) {
            free((*n)->oldspeak);
            (*n)->oldspeak = NULL;
        }

        // Free memory allocated for newspeak
        if ((*n)->newspeak) {
            free((*n)->newspeak);
            (*n)->newspeak = NULL;
        }

        // Free the node
        free(*n);

        // Set pointer to null
        *n = NULL;
    }
    return;
}

// Used for fancy printing
static inline int maxlen(char *oldspeak, char *newspeak) {
    int a = oldspeak ? strlen(oldspeak) + 2 : 4;
    int b = newspeak ? strlen(newspeak) + 2 : 4;
    return a >= b ? a : b;
}

// Used for fancy printing
static inline void quote(char *word, char *quoted, int len) {
    quoted[0] = '"';
    for (int i = 0; i < len; i += 1) {
        quoted[i + 1] = word[i];
    }
    quoted[len + 1] = '"';
    quoted[len + 2] = '\0';
    return;
}

// Used for fancy printing
static inline int ndigits(uint64_t x) {
    int n = 0;
    while (x != 0) {
        x /= 16;
        n++;
    }
    return n;
}

void node_print(Node *n) {
    bool pretty = true;
    if (pretty == false) {

        // As instructed by PDF
        if (n->oldspeak && n->newspeak) {
            printf("%s -> %s\n", n->oldspeak, n->newspeak);
        } else if (n->oldspeak && !n->newspeak) {
            printf("%s\n", n->oldspeak);
        }
        return;
    }

    // Below is ugly code that prints pretty output
    int w = maxlen(n->oldspeak, n->newspeak);
    int s;
    if (n->prev) {
        fprintf(stderr,
            "\x1b[32m"
            "%p"
            "\x1b[0m",
            (void *) n->prev);
        s = ndigits((uint64_t) n->prev) + 4;
    } else {
        fprintf(stderr, "\x1b[31m"
                        "Null"
                        "\x1b[0m");
        s = 6;
    }
    if (n->oldspeak) {
        int len_oldspeak = strlen(n->oldspeak);
        char quoted_oldspeak[len_oldspeak + 3];
        quote(n->oldspeak, quoted_oldspeak, len_oldspeak);
        fprintf(stderr,
            " ← ⎡ "
            "\x1b[34m"
            "%-*s"
            "\x1b[0m"
            " ⎤ → ",
            w, quoted_oldspeak);
    } else {
        fprintf(stderr, " ← ⎡ "
                        "\x1b[31m");
        fprintf(stderr, "%-*s", w, "Null");
        fprintf(stderr, "\x1b[0m"
                        " ⎤ → ");
    }
    if (n->next) {
        fprintf(stderr,
            "\x1b[32m"
            "%p"
            "\x1b[0m"
            "\n",
            (void *) n->next);
    } else {
        fprintf(stderr, "\x1b[31m"
                        "Null"
                        "\x1b[0m"
                        "\n");
    }
    if (n->newspeak) {
        int len_newspeak = strlen(n->newspeak);
        char quoted_newspeak[len_newspeak + 3];
        quote(n->newspeak, quoted_newspeak, len_newspeak);
        fprintf(stderr,
            "%*c ⎣ "
            "\x1b[34m"
            "%-*s"
            "\x1b[0m"
            " ⎦\n",
            s, ' ', w, quoted_newspeak);
    } else {
        fprintf(stderr, "%*c ⎣ ", s, ' ');
        fprintf(stderr, "\x1b[31m");
        fprintf(stderr, "%-*s", w, "Null");
        fprintf(stderr, "\x1b[0m"
                        " ⎦\n");
    }
    return;
}
