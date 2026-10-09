#include <stdio.h>
#include "deque.h"
#include "interpretador.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos>\n", argv[0]);
        return 1;
    }

    if (interpretar_comandos(argv[2]) == -1) {
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }

    return 0;
}