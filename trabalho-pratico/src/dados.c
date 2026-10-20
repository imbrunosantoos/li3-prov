#include "dados.h"
#include <stdlib.h>

struct dados
{
    GestorProdutos *produtos;
    GestorClientes *clientes;
    GestorVendedores *vendedores;
    GestorEncomendas *encomendas;
};

void dados_destruir(Dados *d)
{
    if (d != NULL)
    {
        gestor_produtos_destroy(d->produtos);
        gestor_clientes_destroy(d->clientes);
        gestor_vendedores_destroy(d->vendedores);
        gestor_encomendas_destroy(d->encomendas);
        free(d);
    }
}

Dados *dados_criar(void)
{
    Dados *d = calloc(1, sizeof(Dados));
    if (d == NULL)
        return NULL;

    d->produtos = gestor_produtos_create();
    if (d->produtos == NULL)
    {
        dados_destruir(d);
        return NULL;
    }

    d->clientes = gestor_clientes_create();
    if (d->clientes == NULL)
    {
        dados_destruir(d);
        return NULL;
    }

    d->vendedores = gestor_vendedores_create();
    if (d->vendedores == NULL)
    {
        dados_destruir(d);
        return NULL;
    }

    d->encomendas = gestor_encomendas_create();
    if (d->encomendas == NULL)
    {
        dados_destruir(d);
        return NULL;
    }

    return d;
}

const GestorProdutos *dados_get_produtos(const Dados *d)
{
    return d->produtos;
}

GestorProdutos *dados_get_produtos_mut(Dados *d)
{
    return d->produtos;
}

const GestorClientes *dados_get_clientes(const Dados *d)
{
    return d->clientes;
}
GestorClientes *dados_get_clientes_mut(Dados *d)
{
    return d->clientes;
}

const GestorVendedores *dados_get_vendedores(const Dados *d)
{
    return d->vendedores;
}
GestorVendedores *dados_get_vendedores_mut(Dados *d)
{
    return d->vendedores;
}

const GestorEncomendas *dados_get_encomendas(const Dados *d)
{
    return d->encomendas;
}
GestorEncomendas *dados_get_encomendas_mut(Dados *d)
{
    return d->encomendas;
}
