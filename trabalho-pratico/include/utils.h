#ifndef UTILS_H
#define UTILS_H
#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief           Converter cêntimos em texto (1299->"12.99")
 * @param precoc    Preço em cêntimos
 * @param buf       Onde o texto vai ser escrito
 * @param tam       Tamanho do buffer
 * @return          Devolve true se o preço cabe dentro do buffer, false se não
 */
bool utils_cents_para_string_em_euros(int64_t precoc, char *buf, size_t tam);

#endif