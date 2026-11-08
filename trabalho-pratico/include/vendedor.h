#ifndef VENDEDOR_H
#define VENDEDOR_H


typedef struct vendedor Vendedor;
/**
 * @brief Cria um novo vendedor, copiando os campos recebidos
 * @param id        Identificador do vendedor
 * @param nome      Nome do vendedor
 * @param categoria Categoria de negócio do vendedor
 * @param data      Data de adesão, no formato AAAA-MM-DD
 * @return Apontador para o novo vendedor, a libertar com vendedor_destroy ou NULL se não houver memória
 */
Vendedor *vendedor_novo (const char *id, const char *nome, const char *categoria, const char *data);

/**
 * @brief Liberta o vendedor e todas as suas strings
 * @param vendedor_ptr O vendedor a libertar (se for NULL, não faz nada)
 */
void vendedor_destroy(void *vendedor_ptr);


/**
 * @brief Devolve o identificador do vendedor
 * @param v O vendedor
 * @return Identificador, ou NULL se v for NULL
 */
const char *get_vendedor_id(const Vendedor *c);

/**
 * @brief Devolve o nome do vendedor
 * @param v O vendedor
 * @return Nome, ou NULL se v for NULL
 */
const char *get_vendedor_nome(const Vendedor *c);


/**
 * @brief Devolve a categoria de negócio do vendedor
 * @param v O vendedor
 * @return Categoria, ou NULL se v for NULL
 */
const char *get_vendedor_categoria(const Vendedor *c);


/**
 * @brief Devolve a data de adesão do vendedor
 * @param v O vendedor
 * @return Data no formato AAAA-MM-DD, ou NULL se v for NULL
 */
const char *get_vendedor_data(const Vendedor *c);



#endif 