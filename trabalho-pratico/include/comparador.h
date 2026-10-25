#ifndef COMPARADOR_H
#define COMPARADOR_H

/**
 * @brief Compara dois ficheiros linha a linha
 * @param obtido   Caminho do ficheiro que o nosso programa gerou
 * @param esperado Caminho do ficheiro com o resultado certo
 * @return 0 se forem iguais, N > 0 se a linha N for a primeira diferente, -1 se não conseguir abrir um deles
 */
int comparar_ficheiros(const char *obtido, const char *esperado);

#endif