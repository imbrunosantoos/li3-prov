#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
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

    struct timespec inicio, fim;
    clock_gettime(CLOCK_REALTIME, &inicio);

    char caminho_vendedores[512];
    char caminho_erros_vendedores[512];

    char caminho_clientes[512];
    char caminho_erros_clientes[512];

    char caminho_produtos[512];
    char caminho_erros_produtos[512];

    char caminho_encomendas[512];
    char caminho_erros_encomendas[512];

    char caminho_linhas[512];
    char caminho_erros_linhas[512];

    snprintf(caminho_vendedores, sizeof(caminho_vendedores), "%s/vendedores.csv", argv[1]);
    snprintf(caminho_erros_vendedores, sizeof(caminho_erros_vendedores), "resultados/vendedores_errors.csv");

    snprintf(caminho_clientes, sizeof(caminho_clientes), "%s/clientes.csv", argv[1]);
    snprintf(caminho_erros_clientes, sizeof(caminho_erros_clientes), "resultados/clientes_errors.csv");

    snprintf(caminho_produtos, sizeof(caminho_produtos), "%s/produtos.csv", argv[1]);
    snprintf(caminho_erros_produtos, sizeof(caminho_erros_produtos), "resultados/produtos_errors.csv");

    snprintf(caminho_encomendas, sizeof(caminho_encomendas), "%s/encomendas.csv", argv[1]);
    snprintf(caminho_erros_encomendas, sizeof(caminho_erros_encomendas), "resultados/encomendas_errors.csv");

    snprintf(caminho_linhas, sizeof(caminho_linhas), "%s/linhas_encomenda.csv", argv[1]);
    snprintf(caminho_erros_linhas, sizeof(caminho_erros_linhas), "resultados/linhas_encomenda_errors.csv");

    Dados *d = dados_criar();

    if (d == NULL)
    {
        fprintf(stderr, "Erro: sem memoria para criar os dados\n");
        return 1;
    }

    carregar_vendedores(caminho_vendedores, caminho_erros_vendedores, dados_get_vendedores_mut(d));

    carregar_clientes(caminho_clientes, caminho_erros_clientes, dados_get_clientes_mut(d));

    carregar_produtos(caminho_produtos, caminho_erros_produtos, dados_get_produtos_mut(d), dados_get_vendedores_mut(d));

    carregar_encomendas(caminho_encomendas, caminho_erros_encomendas, dados_get_encomendas_mut(d), dados_get_clientes_mut(d));

    carregar_linhas(caminho_linhas, caminho_erros_linhas, dados_get_linhasencomendas_mut(d), dados_get_encomendas_mut(d), dados_get_produtos_mut(d), dados_get_estatisticas_mut(d));

    gestor_estatisticas_construir_ranking(dados_get_estatisticas_mut(d), dados_get_produtos(d));

    double tempo[4] = {0};
    if (interpretar_comandos(d, argv[2], tempo) == -1)
    {
        dados_destruir(d);
        fprintf(stderr, "erro ao processar comandos\n");
        return 1;
    }

    avaliar_resultados(argv[2], argv[3], tempo);

    dados_destruir(d);

    clock_gettime(CLOCK_REALTIME, &fim);
    double decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("Tempo Total: %.6f s\n", decorrido);

    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória utilizada: %.2f MB\n", r_usage.ru_maxrss / 1024.0);

    return 0;
}