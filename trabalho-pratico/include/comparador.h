#ifndef COMPARADOR_H
#define COMPARADOR_H

/**
 * @brief Compara dois ficheiros linha a linha
 * @param obtido   Caminho do ficheiro que o nosso programa gerou
 * @param esperado Caminho do ficheiro com o resultado certo
 * @return 0 se forem iguais, N > 0 se a linha N for a primeira diferente, -1 se não conseguir abrir um deles
 */
int comparar_ficheiros(const char *obtido, const char *esperado);

/**
 * @brief Compara os resultados obtidos com os esperados e mostra quantos acertou por query
 * @param caminho_input Ficheiro onde estão os comandos que as queries executaram
 * @param pasta_esperados Onde estão os resultados esperados
 */
void avaliar_resultados(const char *caminho_input, const char *pasta_esperados);

#endif