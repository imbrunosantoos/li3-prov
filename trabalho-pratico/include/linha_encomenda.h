#ifndef LINHA_ENCOMENDA_H
#define LINHA_ENCOMENDA_H

// Necessário para o tipo int64_t inteiro com  64 bits que o guiao recomenda
#include <stdint.h>


typedef struct linhaEncomenda LinhaEncomenda;

/**
 * @brief Cria uma nova linha de encomenda
 * @param id_encomenda         Identificador da encomenda a que a linha pertence 
 * @param id_produto           Identificador do produto da linha 
 * @param quantidade           Número de unidades do produto 
 * @param preco_unitario_cents Preço pago por unidade no momento da compra, em cêntimos(pd ser diferente do preço atual do produto)
 * @return Apontador para a nova linha, a libertar com linha_encomenda_destroy ou NULL se não houver memoria
 */


LinhaEncomenda *linha_encomenda_nova(const char *id_encomenda, const char *id_produto, int quantidade, int64_t preco_unitario_cents);


/**
 * @brief Liberta a linha de encomenda e todas as suas strings
 * @param le A linha a libertar (se for NULL, não faz nada)
 */

void linha_encomenda_destroy(LinhaEncomenda *le);

/**
 * @brief Calcula o subtotal da linha de encomenda(quantidade * preço unitário)
 * @param le A linha de encomenda
 * @return Subtotal em cêntimos
 */

int64_t linha_encomenda_subtotal_cents(const LinhaEncomenda *le);

// ------Funcoes GETTERS

/**
 * @brief Devolve o identificador da encomenda a que a linha pertence
 * @param le A linha de encomenda
 * @return Identificador da encomenda
 */


const char *linha_encomenda_get_id_encomenda(const LinhaEncomenda *le);

/**
 * @brief Devolve o identificador do produto da linha de encomenda
 * @param le A linha de encomenda
 * @return Identificador do produto
 */

const char *linha_encomenda_get_id_produto(const LinhaEncomenda *le);

/**
 * @brief Devolve a quantidade de unidades da linha de encomenda
 * @param le A linha de encomenda
 * @return Quantidade (inteiro positivo)
 */

int linha_encomenda_get_quantidade(const LinhaEncomenda *le);

/**
 * @brief Devolve o preço unitário pago no momento da compra
 * @param le A linha de encomenda
 * @return Preço unitário em cêntimos
 */

int64_t linha_encomenda_get_preco_unitario_cents(const LinhaEncomenda *le);




#endif