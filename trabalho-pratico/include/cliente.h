#ifndef CLIENTE_H
#define CLIENTE_H


typedef struct cliente Cliente;
/**
 * @brief Cria um novo cliente, copiando os campos recebidos
 * @param id     Identificador do cliente
 * @param nome   Nome do cliente
 * @param regiao Região do cliente
 * @param data   Data de registo, no formato AAAA-MM-DD
 * @return Apontador para o novo cliente, a libertar com cliente_destroy ou NULL se não houver memória
 */
Cliente *cliente_novo(const char *id, const char *nome, const char *regiao, const char *data);

/**
 * @brief Liberta o cliente e todas as suas strings
 * @param cliente_ptr O cliente a libertar (se for NULL, não faz nada)
 */

void cliente_destroy(void *cliente_ptr);

/**
 * @brief Devolve o identificador do cliente
 * @param c O cliente
 * @return Identificador, ou NULL se c for NULL
 */
const char *get_cliente_id(const Cliente *c);

/**
 * @brief Devolve o nome do cliente
 * @param c O cliente
 * @return Nome, ou NULL se c for NULL
 */
const char *get_cliente_nome(const Cliente *c);

/**
 * @brief Devolve a região do cliente
 * @param c O cliente
 * @return Região, ou NULL se c for NULL
 */
const char *get_cliente_regiao(const Cliente *c);

/**
 * @brief Devolve a data de registo do cliente
 * @param c O cliente
 * @return Data no formato AAAA-MM-DD, ou NULL se c for NULL
 */
const char *get_cliente_data(const Cliente *c);



#endif
