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

//devolve o estado do produto em texto
static const char *estado_produto_para_texto(EstadoProduto estado){
    if (estado == PRODUTO_ATIVO){
        return "ativo";
    }
    return "descontinuado";
}
//escreve euros no output
static void escrever_euros(Output *o, int64_t cents)
{
    char txt[32];
    utils_cents_para_string_em_euros(cents, txt, sizeof(txt));
    output_campo(o, txt);
}

//escreve o valor inteiro no output
static void escrever_inteiro(Output *o, int valor)
{
    char txt[16];
    snprintf(txt, sizeof(txt), "%d", valor);
    output_campo(o, txt);
}

//escreve a ficha de um produto, (unidade e a receita ja vem calculada do gestor de estatisticas)
void query1(const Dados *d, Output *o, char *const *args, int n_args)
{
    const Produto *p = NULL;
    if (n_args >= 1)
        p = gestor_produtos_procurar(dados_get_produtos(d), args[0]);

    if (p == NULL)
    {
        output_fim_linha(o);
        return;
    }

    const char *id = args[0];

    const Vendedor *v = gestor_vendedores_procurar(dados_get_vendedores(d), produto_get_id_vendedor(p));
    const char *nome_vendedor = "";
    if (v != NULL)
        nome_vendedor = get_vendedor_nome(v);

    const GestorEstatisticas *ge = dados_get_estatisticas(d);

    output_campo(o, produto_get_nome(p));
    output_campo(o, produto_get_categoria(p));
    escrever_euros(o, produto_get_preco_atual_cents(p));
    output_campo(o, estado_produto_para_texto(produto_get_estado_produto(p)));
    output_campo(o, nome_vendedor);
    escrever_inteiro(o, gestor_estatisticas_get_unidades(ge, id));
    escrever_euros(o, gestor_estatisticas_get_receita_cents(ge, id));
    output_fim_linha(o);
}

// sem filtro-todos os produtos servem, com filtro-só os dessa categoria
static bool pertence_categoria(const Produto *p, const char *categoria)
{
    if (categoria == NULL)
        return true;
    return strcmp(produto_get_categoria(p), categoria) == 0;
}

//top N produtos mais vendidos (opcionalmente só de uma categoria), lidos do ranking já ordenado na carga
void query2(const Dados *d, Output *o, char *const *args, int n_args)
{
    if (n_args < 1)
    {
        output_fim_linha(o);
        return;
    }

    int n = atoi(args[0]);

    // a categoria é opcional: sem ela entram todos os produtos
    const char *categoria = NULL;
    if (n_args >= 2)
        categoria = args[1];

    const GestorEstatisticas *ge = dados_get_estatisticas(d);
    int total = gestor_estatisticas_ranking_num(ge);
    int escritos = 0;

    //para quando acaba o ranking ou quando já escreveu n produtos
    for (int i = 0; i < total && escritos < n; i++)
    {
        const Produto *p = gestor_estatisticas_ranking_get(ge, i);

        // a ordem dentro de uma categoria é a mesma do ranking, por isso basta saltar as outras
        if (!pertence_categoria(p, categoria))
            continue;

        const char *id = produto_get_id(p);

        output_campo(o, produto_get_nome(p));
        output_campo(o, produto_get_categoria(p));
        escrever_inteiro(o, gestor_estatisticas_get_unidades(ge, id));
        escrever_euros(o, gestor_estatisticas_get_receita_cents(ge, id));
        output_fim_linha(o);
        escritos++;
    }

    // nenhum produto satisfez o pedido-linha vazia
    if (escritos == 0)
        output_fim_linha(o);
}

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