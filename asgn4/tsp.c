#include <stdio.h>

#define BLOCK 4096

int main() {
    char buffer[BLOCK];
    
    while (fgets(buffer, BLOCK, stdin)) {
        fputs(buffer, stdout);
    }
    
    return 0;
}
