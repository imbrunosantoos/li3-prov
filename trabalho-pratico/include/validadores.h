#ifndef  VALIDADORES_H
#define  VALIDADORES_H
#include <stdbool.h>
#include <stdint.h>
#include "produto.h"
#include "encomenda.h"


/**
 * @brief Valida um identificador, que tem de ser o prefixo seguido de um ou mais dígitos
 * @param id      Identificador a validar (ex.: P000007)
 * @param prefixo Letra maiúscula da entidade (C, V, P ou O)
 * @return true se for válido, false caso contrário (inclui id NULL)
 */
bool validar_id(const char *id, char prefixo);

/**
 * @brief Valida uma data no formato AAAA-MM-DD, com mês entre 1 e 12 e dia entre 1 e 31
 * não verifica o número de dias de cada mês
 * @param data Data a validar
 * @return true se for válida, false caso contrário (inclui data NULL)
 */
bool validar_data(const char *data );

/**
 * @brief Valida um texto, que não pode ser vazio nem conter ';'
 * @param str Texto a validar (ex.: um nome)
 * @return true se for válido, false caso contrário (inclui str NULL)
 */
bool validar_texto(const char *str);

/**
 * @brief Valida um texto como validar_texto, mas que também não pode conter espaços
 * @param str Texto a validar (ex.: uma região ou categoria)
 * @return true se for válido, false caso contrário (inclui str NULL)
 */
bool validar_sem_espacos(const char *str);

/**
 * @brief Valida um preço, com um ou mais dígitos e opcionalmente um ponto seguido de um ou dois dígitos
 * rejeita, por exemplo, -3.50, 3,50, 3.500, 1.2.3, 3. e .50
 * @param texto Preço a validar
 * @param cents Se não for NULL, recebe o valor em cêntimos (12.99 fica 1299)
 * @return true se for válido, false caso contrário
 */
bool  validar_preco (const char *texto, int64_t *cents);

/**
 * @brief Valida uma quantidade, que tem de ser um inteiro positivo sem zeros à esquerda
 * @param texto      Quantidade a validar
 * @param quantidade Se não for NULL, recebe o valor convertido
 * @return true se for válida, false caso contrário
 */
bool validar_quantidade (const char *texto, int *quantidade);

/**
 * @brief Valida o estado de um produto, que só pode ser "ativo" ou "descontinuado" (em minúsculas)
 * @param texto  Estado a validar
 * @param estado Se não for NULL, recebe o estado convertido
 * @return true se for válido, false caso contrário
 */
bool validar_estado_produto (const char *texto, EstadoProduto *estado);

/**
 * @brief Valida o estado de uma encomenda, que só pode ser "paga", "enviada", "entregue" ou "cancelada" (em minúsculas)
 * @param texto  Estado a validar
 * @param estado Se não for NULL, recebe o estado convertido
 * @return true se for válido, false caso contrário
 */
bool validar_estado_encomenda (const char *texto, EstadoEncomenda *estado);

/**
 * @brief Valida os campos de uma linha de clientes.csv
 * @param campos   Campos da linha, já separados
 * @param n_campos Número de campos recebidos (tem de ser pelo menos 4)
 * @return true se todos os campos forem válidos, false caso contrário
 */
bool validar_linha_cliente(const char  **campos, int n_campos);

/**
 * @brief Valida os campos de uma linha de vendedores.csv
 * @param campos   Campos da linha, já separados
 * @param n_campos Número de campos recebidos (tem de ser pelo menos 4)
 * @return true se todos os campos forem válidos, false caso contrário
 */
bool validar_linha_vendedor(const char  **campos, int n_campos);

/**
 * @brief Valida os campos de uma linha de produtos.csv
 * @param campos   Campos da linha, já separados
 * @param n_campos Número de campos recebidos (tem de ser pelo menos 6)
 * @return true se todos os campos forem válidos, false caso contrário
 */
bool validar_linha_produto(const char **campos, int n_campos);

/**
 * @brief Valida os campos de uma linha de encomendas.csv
 * @param campos   Campos da linha, já separados
 * @param n_campos Número de campos recebidos (tem de ser pelo menos 4)
 * @return true se todos os campos forem válidos, false caso contrário
 */
bool validar_linha_encomenda(const char **campos, int n_campos);


/**
 * @brief Valida os campos de uma linha de linhas_encomenda.csv
 * @param campos   Campos da linha, já separados
 * @param n_campos Número de campos recebidos (tem de ser pelo menos 4)
 * @return true se todos os campos forem válidos, false caso contrário
 */
bool validar_linha_linhas_encomenda (const char **campos, int n_campos);

#endif

