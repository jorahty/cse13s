#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\x1b[0m"
#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE  "\x1b[34m"

// Number of seeks
// and number of links travered
// are initially zero
uint64_t seeks = 0;
uint64_t links = 0;

// Taken from assignment PDF
struct LinkedList {
    uint32_t length; // Number of nodes in linked list (not including sentinel nodes)
    Node *head; // Head sentinel node
    Node *tail; // Tail sentinel node
    bool mtf; // Bool for whethor move-to-front is enabled
};

LinkedList *ll_create(bool mtf) {
    // Allocate memory for a new linked list
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll == NULL) {
        return NULL; // Return null if malloc failed
    }

    // Initialize length of linked list to zero
    ll->length = 0;

    // Create head and tail sentinel nodes
    char h[] = "HEAD";
    char t[] = "TAIL";
    ll->head = node_create(h, NULL);
    ll->tail = node_create(t, NULL);

    // Link the head and tail together
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->head->prev = NULL;
    ll->tail->next = NULL;

    // Set move-to-front status boolean
    ll->mtf = mtf;

    // Return the newly created linked list
    return ll;
}

void ll_delete(LinkedList **ll) {
    // Free the memory allocated for the linked list
    // if it exists and is not aliready null
    if (ll && *ll) {
        // Free every node in the linked list
        while ((*ll)->head != NULL) {
            // First, save the head node
            Node *n = (*ll)->head;
            // Shift the head over
            (*ll)->head = (*ll)->head->next;
            // Delete the old head node that you saved
            node_delete(&n);
            // Repeat until the head becomes null,
            // meaning we have reached the far end of the linked list
        }

        // Free the rest of the linked list
        free(*ll);

        // Set the pointer to the linked list to null
        *ll = NULL;
    }
    return;
}

uint32_t ll_length(LinkedList *ll) {
    // Return the linked list's `length` property,
    // which is the number of nodes in `ll` (not including the sentinel nodes)
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    Node *n = ll->head; // Starting at the node after the head,
    while (true) { // Traverse the linked list until
        n = n->next;
        // either the end of the linked list is reached,
        if (n == ll->tail) {
            return NULL;
        }
        // or the matching key (oldspeak) is found
        if ((n->oldspeak && oldspeak && strcmp(n->oldspeak, oldspeak) == 0)
            || (!n->oldspeak && !oldspeak)) {
            // Move found node `n` to front if `mtf` is enabled
            if (ll->mtf) {
                // Bridge over `n`
                n->prev->next = n->next;
                n->next->prev = n->prev;
                // Re-insert `n` after head of linked list
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next = n;
                n->next->prev = n;
            }
            return n;
        }
    }
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // Do not insert if `ll` already contains a node with matching `oldspeak`
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }

    // Create a new node with given `oldspeak` and `newspeak`
    Node *n = node_create(oldspeak, newspeak);
    if (n == NULL) {
        return; // Exit if malloc failed
    }

    // Link new node n into `ll`
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next = n;
    n->next->prev = n;
    ll->length += 1;
    return;
}

static void print_word(Node *n, char *word) {
    // Get width `w`
    int a = n->oldspeak ? strlen(n->oldspeak) + 2 : 4;
    int b = n->newspeak ? strlen(n->newspeak) + 2 : 4;
    int w = a >= b ? a : b;

    // If word is not null,
    if (word) {
        // Get word with quotes `q`
        int len = strlen(word);
        char q[len + 3];
        q[0] = '"';
        q[len + 1] = '"';
        q[len + 2] = '\0';
        for (int i = 0; i < len; i += 1) {
            q[i + 1] = word[i];
        }

        // Print word with quotes
        fprintf(stderr, BLUE "%-*s" RESET, w, q);
    }

    else {
        // Else word is null so print "Null"
        fprintf(stderr, RED "%-*s" RESET, w, "Null");
    }

    return;
}

void ll_print(LinkedList *ll) {
    // Print "Null" if `ll` is null
    if (!ll) {
        fprintf(stderr, RED "Null" RESET "\n");
        return;
    }
    // Print properties of `ll`
    fprintf(stderr, "Length: " BLUE "%d" RESET ", Move-to-front: %s, Contents:\n", ll->length,
        ll->mtf ? GREEN "On" RESET : RED "Off" RESET);

    // Print top row of contents
    Node *n = ll->head;
    fprintf(stderr, "       ⎡ ");
    print_word(n, n->oldspeak);
    while (true) {
        n = n->next;
        if (n == NULL) {
            fprintf(stderr, " ⎤ → " RED "Null" RESET "\n");
            break;
        }
        fprintf(stderr, " ⎤ → ⎡ ");
        print_word(n, n->oldspeak);
    }

    // Print bottom row of contents
    n = ll->head;
    fprintf(stderr, RED "Null" RESET " ← ⎣ ");
    print_word(n, n->newspeak);
    while (true) {
        n = n->next;
        if (n == NULL) {
            fprintf(stderr, " ⎦\n");
            break;
        }
        fprintf(stderr, " ⎦ ← ⎣ ");
        print_word(n, n->newspeak);
    }

    return;
}
