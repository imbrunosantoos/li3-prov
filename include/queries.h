#ifndef QUERIES_H
#define QUERIES_H
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief           Resume um produto (nome;categoria;preco_atual;estado;vendedor;unidades_vendidas;receita_gerada).
 * @param out       Ficheiro onde escrever o resultado.
 * @param args      id do produto.
 * @param n_args    Número de argumentos (sempre 1)
 * @param sep       ';' por omissão, '=' na variante S.
 */
void query1(FILE *out, char *const *args, int n_args, char sep);

/**
 * @brief           Faz um top N de produtos mais vendidos (por categoria opcionalmente).
 * @param out       Ficheiro onde escrever o resultado.
 * @param args      N , com categoria opcional.
 * @param n_args    args[0]: N (inteiro positivo); args[1]: categoria (opcional)
 * @param sep       ';' por omissão, '=' na variante S.
 */
void query2(FILE *out, char *const *args, int n_args, char sep);

/**
 * @brief           Mostra o detalhe de uma encomenda específica.
 * @param out       Ficheiro onde escrever o resultado.
 * @param args      id da encomenda.
 * @param n_args    1
 * @param sep       ';' por omissão, '=' na variante S.
 */
void query3(FILE *out, char *const *args, int n_args, char sep);

#endif