#ifndef OUTPUT_H
#define OUTPUT_H

typedef struct output Output;

/**
 * @brief           Abre o ficheiro de resultados de um comando (resultados/commandN_output.txt)
 * @param n_comando Número do comando (linha do input.txt, começa em 1)
 * @param sep       Separador entre campos (';' normal ou '=' na variante S)
 * @return          Novo Output (a libertar com output_fechar), ou NULL se não conseguir abrir o ficheiro
 */
Output *output_abrir(int n_comando, char sep);

/**
 * @brief       Escreve o campo dado dentro do ficheiro correspondente com o separador antes exceto no caso do primeiro campo
 * @param o     Output onde escrever (criado com output_abrir)
 * @param campo  O que se tem que escrever
 */
void output_campo(Output *o, const char *campo);

/**
 * @brief   No fim de cada linha introduz "\n" para formatar
 * @param o Output onde escrever (criado com output_abrir)
 */
void output_fim_linha(Output *o);

/**
 * @brief   Fecha o ficheiro correspondente e liberta a memória e se receber NULL não faz nada
 * @param o Output a fechar
 */
void output_fechar(Output *o);

#endif