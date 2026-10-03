#include "deque.h"
#include <stdio.h>

int main(int argc, char **argv) {
    
    if (argc != 3) {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos>\n", argv[0]);
        return 1;
    }

    Deque *d = create();
    destroy(d);
    return 0;
}