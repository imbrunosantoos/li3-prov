#ifndef PRODUTO_H
#define PRODUTO_H

// Necessário para o tipo int64_t inteiro com  64 bits que o guiao recomenda
#include <stdint.h>

typedef struct produto Produto;

typedef enum EstadoProduto {
    PRODUTO_ATIVO,          // produto está sendo vendido
    PRODUTO_DESCONTINUADO   //  produto deixou de ser vendido
} EstadoProduto;

/**
 * @brief                  cria um novo produto
 * @param id               Identificador do produto (ex:P000123)
 * @param nome             Nome do produto.
 * @param categoria        Categoria do produto
 * @param preco_atual_cents Preço atual em cêntimos
 * @param id_vendedor      Identificador do vendedor que publica o produto
 * @param estado           Estado do produto
 * @return                  Apontador para o novo produto
 */
Produto *produto_novo(const char *id, const char *nome, const char *categoria, int64_t preco_atual_cents, const char *id_vendedor, EstadoProduto estado);

/**
 * @brief Liberta o produto e todas as suas strings
 * @param p O produto a libertar(se for NULL, nao faz nada)
 */
void produto_destroy(Produto *p);

// ----Funçoes GETTERS- Só leem, não alteram nada


/**
 * @brief Devolve o identificador do produto
 * @param p O produto
 * @return Identificador
 */
const char *produto_get_id(const Produto *p); 

/**
 * @brief Devolve o nome do produto
 * @param p O produto
 * @return Nome
 */
const char *produto_get_nome(const Produto *p);

/**
 * @brief Devolve a categoria do produto
 * @param p O produto
 * @return Categoria, só de leitura 
 */
const char *produto_get_categoria(const Produto *p);

/**
 * @brief Devolve o preço atual do produto
 * @param p O produto
 * @return Preço em cêntimos
 */
int64_t produto_get_preco_atual_cents(const Produto *p);

/**
 * @brief Devolve o identificador do vendedor que publica o produto
 * @param p O produto
 * @return Identificador do vendedor, só de leitura (não alterar nem libertar)
 */
const char *produto_get_id_vendedor(const Produto *p);

/**
 * @brief Devolve o estado do produto
 * @param p O produto
 * @return PRODUTO_ATIVO ou PRODUTO_DESCONTINUADO
 */
EstadoProduto produto_get_estado_produto(const Produto *p);

#endif