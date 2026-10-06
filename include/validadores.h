#ifndef  VALIDADORES_H
#define  VALIDADORES_H
#include <stdbool.h>


bool validar_id(const char *id, char prefixo);
bool validar_data(const char *data );
bool validar_texto(const char *str);
bool validar_sem_espaco(const char *str);

bool validar_linha_cliente(const  **campos, int n_campos);
bool validar_linha_vendedor(const  **campos, int n_campos);

#endif