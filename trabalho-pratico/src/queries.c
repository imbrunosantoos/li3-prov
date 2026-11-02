#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queries.h"
#include "utils.h"

static const char *estado_para_texto(EstadoEncomenda estado)
{
    switch (estado)
    {
    case ENCOMENDA_PAGA:
        return "paga";
    case ENCOMENDA_CANCELADA:
        return "cancelada";
    case ENCOMENDA_ENVIADA:
        return "enviada";
    case ENCOMENDA_ENTREGUE:
        return "entregue";
    }
    return "";
}

static int comparar_linhas_por_produto(const void *a, const void *b)
{
    const LinhaEncomenda *la = *(const LinhaEncomenda *const *)a;
    const LinhaEncomenda *lb = *(const LinhaEncomenda *const *)b;
    return strcmp(linha_encomenda_get_id_produto(la), linha_encomenda_get_id_produto(lb));
}

/* Stub: escreve linha vazia até a Q1 estar implementada. */
void query1(const Dados *d, Output *o, char *const *args, int n_args)
{
    (void)args;
    (void)n_args;
    (void)d;
    output_fim_linha(o);
}

/* Stub: escreve linha vazia até a Q2 estar implementada. */
void query2(const Dados *d, Output *o, char *const *args, int n_args)
{
    (void)args;
    (void)n_args;
    (void)d;
    output_fim_linha(o);
}

/* Stub: escreve linha vazia até a Q3 estar implementada. */
void query3(const Dados *d, Output *o, char *const *args, int n_args)
{
    if (n_args < 1)
    {
        output_fim_linha(o);
        return;
    }

    const char *id_encomenda = args[0];

    const Encomenda *e = gestor_encomendas_procurar(dados_get_encomendas(d), id_encomenda);

    if (e == NULL)
    {
        output_fim_linha(o);
        return;
    }

    const Cliente *c = gestor_clientes_procurar(dados_get_clientes(d), encomenda_get_id_cliente(e));

    if (c == NULL)
    {
        output_fim_linha(o);
        return;
    }

    const char *nome_cliente = get_cliente_nome(c);

    int n = gestor_linha_encomenda_num_linhas(dados_get_linhasencomendas(d), id_encomenda);
    int64_t total = 0;

    const LinhaEncomenda **linhas = malloc(n * sizeof(const LinhaEncomenda *));

    for (int i = 0; i < n; i++)
    {
        const LinhaEncomenda *l = gestor_linha_encomenda_get_linha(dados_get_linhasencomendas(d), id_encomenda, i);
        total += linha_encomenda_subtotal_cents(l);
        linhas[i] = l;
    }

    qsort(linhas, n, sizeof(const LinhaEncomenda *), comparar_linhas_por_produto);

    char total_txt[32];
    utils_cents_para_string_em_euros(total, total_txt, sizeof(total_txt));

    const char *data = encomenda_get_data(e);

    const char *estado_e = estado_para_texto(encomenda_get_estado_encomenda(e));

    output_campo(o, nome_cliente);
    output_campo(o, data);
    output_campo(o, estado_e);
    output_campo(o, total_txt);
    output_fim_linha(o);

    for (int i = 0; i < n; i++)
    {
        const LinhaEncomenda *l = linhas[i];
        const char *id_produto = linha_encomenda_get_id_produto(l);

        const Produto *p = gestor_produtos_procurar(dados_get_produtos(d), id_produto);
        const char *nome_produto = (p != NULL) ? produto_get_nome(p) : "";

        char qtd_txt[16];
        snprintf(qtd_txt, sizeof(qtd_txt), "%d", linha_encomenda_get_quantidade(l));

        char preco_txt[32];
        utils_cents_para_string_em_euros(linha_encomenda_get_preco_unitario_cents(l), preco_txt, sizeof(preco_txt));

        char subtotal_txt[32];
        utils_cents_para_string_em_euros(linha_encomenda_subtotal_cents(l), subtotal_txt, sizeof(subtotal_txt));

        output_campo(o, id_produto);
        output_campo(o, nome_produto);
        output_campo(o, qtd_txt);
        output_campo(o, preco_txt);
        output_campo(o, subtotal_txt);
        output_fim_linha(o);
    }

    free(linhas);
}