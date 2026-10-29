#include <stdio.h>
#include "comparador.h"
#include "interpretador.h"
#include "carregamento.h"
#include "dados.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "uso: %s <pasta_dataset> <ficheiro_comandos> <pasta_resultados_esperados>\n", argv[0]);
        return 1;
    }

    char caminho_vendedores[512];
    char caminho_erros_vendedores[512];
    char caminho_clientes[512];
    char caminho_erros_clientes[512];

    snprintf(caminho_vendedores, sizeof(caminho_vendedores), "%s/vendedores.csv", argv[1]);
    snprintf(caminho_erros_vendedores, sizeof(caminho_erros_vendedores), "resultados/vendedores_errors.csv");

    snprintf(caminho_clientes, sizeof(caminho_clientes), "%s/clientes.csv", argv[1]);
    snprintf(caminho_erros_clientes, sizeof(caminho_erros_clientes), "resultados/clientes_errors.csv");

    Dados *d = dados_criar();

    if (d == NULL)
    {
        fprintf(stderr, "Erro: sem memoria para criar os dados\n");
        return 1;
    }

    carregar_vendedores(caminho_vendedores, caminho_erros_vendedores, dados_get_vendedores_mut(d));
    carregar_clientes(caminho_clientes, caminho_erros_clientes, dados_get_clientes_mut(d));

    if (interpretar_comandos(d, argv[2]) == -1)
    {
        dados_destruir(d);
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }

    avaliar_resultados(argv[2], argv[3]);

    dados_destruir(d);

    return 0;
}