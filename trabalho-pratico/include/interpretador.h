#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H
#include "dados.h"

/**
 * @brief               Função que interpreta os comandos das queries.
 * @param d             As estruturas de Dados para as queries
 * @param caminho_input O caminho para o input.txt
 * @return              -1 se der erro, 0 se funcionar.
 */
int interpretar_comandos(const Dados *d, const char *caminho_input);

#endif