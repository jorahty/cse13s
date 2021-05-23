#include "huffman.h"

#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdio.h>

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Initialize a priority queue
    PriorityQueue *q = pq_create(ALPHABET);

    // Enqueue a node for every symbol in the histogram
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }

    // Print priority queue (temporary)
    // fprintf(stderr, "\nPriority Queue:\n");
    // pq_print(q);
    // Rearranging the prioty queue into a Huffman tree
    // While there are two or more nodes in the queue ...
    while (pq_size(q) >= 2) {
        // Dequeue two nodes
        Node *l;
        Node *r;
        dequeue(q, &l);
        dequeue(q, &r);
        // Put the joined nodes back in the queue
        enqueue(q, node_join(l, r));
        // pq_print(q);
    }
    // fprintf(stderr, "\n");

    // Now there must be only 1 node in the queue
    // This node is the root of the Huffman tree
    Node *root;
    dequeue(q, &root);

    // Delete the priority queue
    pq_delete(&q);

    // Return the root (which contains all the data for the entire Huffman tree
    return root;
}

static void traverse(Node *n, Code table[static ALPHABET], Code c) {
    // If this node is a leaf ...
    if (!n->left && !n->right) {
        if (n->symbol < 32) {
            // fprintf(stderr, "Found a leaf: ' ' %lu\n", n->frequency);
        } else {
            // fprintf(stderr, "Found a leaf: '%c' %lu\n", n->symbol, n->frequency);
        }
        // Then c is the code for this node's symbol
        table[n->symbol] = c;
        // fprintf(stderr, "Done with leaf so going back up ...\n");
        return;

        // Otherwise, this node is an interior node
    } else {
        // fprintf(stderr, "Found an interior node: '%c' %lu\n", n->symbol, n->frequency);
        uint8_t trash; // We don't care about the popped bits
        // Search to the left
        // fprintf(stderr, "Searching to the left ...\n");
        code_push_bit(&c, 0);
        traverse(n->left, table, c);
        code_pop_bit(&c, &trash);
        // Search to the right
        // fprintf(stderr, "Searching to the right ...\n");
        code_push_bit(&c, 1);
        traverse(n->right, table, c);
        code_pop_bit(&c, &trash);
    }

    // fprintf(stderr, "Left and right child searched so going back up ...\n");
    return;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    // Create a place to store codes
    Code c = code_init();
    // Traverse tree to build code table
    // fprintf(stderr, "Traversing Huffman tree to build code table ...\n");
    traverse(root, table, c);
    // fprintf(stderr, "\n");
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    // Create a stack to temporarily store nodes
    // Nodes in stack s will be rearanged into a Huffman tree
    Stack *s = stack_create(nbytes);
    // For each byte of the tree ...
    for (uint16_t i = 0; i < nbytes; i++) {
        // Print the stack (temporary)
        // stack_print(s);
        // If byte is 'L' then ...
        if (tree[i] == 'L') {
            // Create a node with the symbol immediately after the 'L'
            Node *n = node_create(tree[i + 1], 1);
            // And add it to the stack
            stack_push(s, n);
            // Increment i to skip over symbol
            i++;
            // Else then byte is 'I'
        } else {
            // An 'I' will always has at least two bytes that came before it
            // So we can remove two nodes from the stack
            Node *left;
            Node *right;
            stack_pop(s, &left);
            stack_pop(s, &right);
            // Join them together
            Node *p = node_join(left, right);
            // And put the new parent node p back onto the stack
            stack_push(s, p);
        }
    }
    // At this point there should be one node in stack s
    // This node is the root of the Huffman tree, and the root contains the entire tree
    // Pop the root from stack s
    Node *root;
    stack_pop(s, &root);
    // At this point we can delete s
    stack_delete(&s);
    // Return the root node of the Huffman tree
    return root;
}

void delete_tree(Node **root) {
    // If this node is a leaf ...
    // (If this node has no children ... )
    // fprintf(stderr, "Checking if node is a leaf ...\n");
    if (!(*root)->left && !(*root)->right) {
        // fprintf(stderr, "Node is a leaf\n");
        // Delete node
        // fprintf(stderr, "Node to delete:\n");
        // node_print(*root);
        // fprintf(stderr, "Deleteing node ...\n");
        node_delete(root);
        // And go back up tree to continue searching
        // fprintf(stderr, "Going back up ...\n");
        return;
        // Otherwise, this node is an interior node
    } else {
        // fprintf(stderr, "Node is not a leaf\n");
        // Search to the left
        // fprintf(stderr, "Searching to the left\n");
        delete_tree(&((*root)->left));
        // Search to the right
        // fprintf(stderr, "Searching to the right\n");
        delete_tree(&((*root)->right));
        // Delete node
        // fprintf(stderr, "Node to delete:\n");
        // node_print(*root);
        // fprintf(stderr, "Deleteing node ...\n");
        node_delete(root);
    }
    // When both left and righ children have been searched,
    // Go back up tree to continue searching
    // fprintf(stderr, "Going back up ...\n");
    return;
}
