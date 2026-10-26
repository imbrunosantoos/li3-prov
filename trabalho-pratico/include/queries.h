#ifndef QUERIES_H
#define QUERIES_H
#include <stdlib.h>
#include <stdio.h>
#include "dados.h"
#include "output.h"

/**
 * @brief           Resume um produto (nome;categoria;preco_atual;estado;vendedor;unidades_vendidas;receita_gerada).
 * @param d         Estrutura de dados dos gestores.
 * @param o         Onde a query escreve o resultado (o separador já vem definido)
 * @param args      args[0]: id do produto
 * @param n_args    Número de argumentos (sempre 1)
 */
void query1(const Dados *d, Output *o, char *const *args, int n_args);

/**
 * @brief           Faz um top N de produtos mais vendidos (por categoria opcionalmente).
 * @param d         Estrutura de dados dos gestores.
 * @param o         Onde a query escreve o resultado (o separador já vem definido)
 * @param args      N , com categoria opcional.
 * @param n_args    args[0]: N (inteiro positivo); args[1]: categoria (opcional)
 */
void query2(const Dados *d, Output *o, char *const *args, int n_args);

/**
 * @brief           Mostra o detalhe de uma encomenda específica.
 * @param d         Estrutura de dados dos gestores.
 * @param o         Onde a query escreve o resultado (o separador já vem definido)
 * @param args      id da encomenda.
 * @param n_args    1
 */
void query3(const Dados *d, Output *o, char *const *args, int n_args);

#endif