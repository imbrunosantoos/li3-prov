#ifndef ENCOMENDA_H
#define ENCOMENDA_H

typedef struct encomenda Encomenda;

typedef enum EstadoEncomenda{
    ENCOMENDA_PAGA,
    ENCOMENDA_ENVIADA,
    ENCOMENDA_ENTREGUE,
    ENCOMENDA_CANCELADA
}EstadoEncomenda;


/**
 * @brief Cria uma nova encomenda
 * @param id         Identificador da encomenda 
 * @param id_cliente Identificador do cliente que fez a encomenda 
 * @param data       Data da encomenda, no formato AAAA-MM-DD
 * @param estado     Estado da encomenda
 * @return Apontador para a nova encomenda, a libertar com encomenda_destroy ou NULL se não houver memória
 */
Encomenda *encomenda_nova(const char *id, const char *id_cliente, const char *data, EstadoEncomenda estado);

/**
 * @brief Liberta a encomenda e todas as suas strings
 * @param e A encomenda a libertar (se for NULL, não faz nada)
 */

void encomenda_destroy(Encomenda *e);

//-----Funçoes Getters

/**
 * @brief Devolve o identificador da encomenda
 * @param e A encomenda
 * @return Identificador
 */

const char *encomenda_get_id(const Encomenda *e);

/**
 * @brief Devolve o identificador do cliente que fez a encomenda
 * @param e A encomenda
 * @return Identificador do cliente
 */

const char *encomenda_get_id_cliente(const Encomenda *e);

/**
 * @brief Devolve a data da encomenda
 * @param e A encomenda
 * @return Data no formato AAAA-MM-DD
 */


const char *encomenda_get_data(const Encomenda *e);

/**
 * @brief Devolve o estado da encomenda
 * @param e A encomenda
 * @return ENCOMENDA_PAGA, ENCOMENDA_ENVIADA, ENCOMENDA_ENTREGUE ou ENCOMENDA_CANCELADA
 */

EstadoEncomenda encomenda_get_estado_encomenda(const Encomenda *e);


#endif
