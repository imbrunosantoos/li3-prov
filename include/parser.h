#ifndef PARSER_H
#define PARSER_H

int separar_campos(char *linha, char **campos, int max);
int ler_csv(const char *caminho);

#endif