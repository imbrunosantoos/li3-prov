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

char caminho_vendedores [512];
char caminho_erros_vendedores [512];
char caminho_clientes [512];
char caminho_erros_clientes [512];



snprintf (caminho_vendedores, sizeof(caminho_vendedores), "%s/vendedores.csv", argv[1]);
snprintf (caminho_erros_vendedores, sizeof(caminho_erros_vendedores), "vendedores_erros.csv");

snprintf (caminho_clientes, sizeof(caminho_clientes), "%s/clientes.csv", argv[1]);
snprintf (caminho_erros_clientes, sizeof(caminho_erros_clientes), "clientes_erros.csv");













processar_vendedores (caminho_vendedores , caminho_erros_vendedores);
processar_clientes (caminho_clientes , caminho_erros_clientes);

    Deque *d = create();
    destroy(d);

    if (interpretar_comandos(argv[2]) == -1) {
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }

    return 0;
}
