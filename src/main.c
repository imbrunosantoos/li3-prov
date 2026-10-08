#include <stdio.h>
#include "deque.h"
#include "interpretador.h"
#include "vendedor.h"
#include "cliente.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos>\n", argv[0]);
        return 1;
    }

processar_vendedores ("dataset/vendedores.csv" , "resultados/vendeores_errors.csv");
processar_clientes ("dataset/clientes.csv" , "resultados/clientes_errors.csv");

    Deque *d = create();
    destroy(d);

    if (interpretar_comandos(argv[2]) == -1) {
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }

    return 0;
}
