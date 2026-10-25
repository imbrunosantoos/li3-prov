#include <stdio.h>
#include "comparador.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos> <pasta_resultados_esperados>\n", argv[0]);
        return 1;
    }
    avaliar_resultados(argv[2], argv[3]);
    return 0;
}