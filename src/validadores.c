#include "validadores.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool validar_id (const char *id, char prefixo) {
    if (!id || id[0] != prefixo || strlen(id) < 2 ) return false;
    for (int i = 1 ; id[i] != '\0'; i++ ) {
        if (!isdigit((unsigned char)id[i])) return false;
    }    
    return true ;
}

bool validar_data (const char *data) {  
    if (!data || strlen(data) != 10 ) return false;
    if (data[4] != '-' || data[7] != '-'  ) return false;
    for (int i = 0; i<10 ; i++){
        if ( i == 4 || i == 7 ) continue;
        if (!isdigit ( ( unsigned char )data[i])) return false;
    }
    int ano = atoi(data);
    int mes = atoi(data + 5 );
    int dia = atoi (data + 8);

    if (ano<0) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    return true ;
}


bool validar_texto (const char *str){
    if ( str == NULL || str [0] == '\0' ) return false;
    if (strchr(str, ';') != NULL) return false;
    return true;
}

bool validar_sem_espacos (const char *str){
    if ( str == NULL || str [0] == '\0') return false ;
    if ( strchr (str, ';') != NULL || strchr (str, ' ') != NULL ) return false;
    return true;
}        
 

bool validar_preco (const char *texto, int64_t *cents) {
    if (!texto || texto [0] == '\0') return false;
    int i = 0;
    int pontos = 0;
    int casas_decimais = 0;
    while (texto [i] != '\0') {
        if (texto[i] == '.') {
            pontos++;
            if (pontos > 1 || i == 0) return false;  
        } else if (!isdigit((unsigned char)texto[i])) {
            return false;
        } else if (pontos == 1) {
            casas_decimais++;
        }
        i++;
    }
    if ( i == 0 || texto [i - 1 ] == '.' || casas_decimais > 2) return false;
    if (cents != NULL) {
        char *ponto = strchr (texto, '.');
        if (!ponto) {
            *cents = atoll(texto) * 100;
        } else if (casas_decimais == 1) {
            int64_t inteiros = atoll(texto);
            int64_t decimais = atoi(ponto + 1);
            *cents = inteiros * 100 + decimais * 10;
        } else {
            int64_t inteiros = atoll(texto);
            int64_t decimais = atoi (ponto + 1 );
            *cents = inteiros * 100 + decimais ;
        }
    }
    return true;
}            

bool validar_quantidade (const char *texto, int *quantidade) {
    if (!texto || texto [0] == '\0') return false;
    if (texto[0] == '0') return false;
    for (int i = 0; texto[i] != '\0'; i++){
        if (!isdigit((unsigned char)texto[i])) return false;
    }
    long val = atol(texto);
    if (val < 1) return false;

    if (quantidade != NULL) {
        *quantidade = (int)val;
    }
    return true;
}

bool validar_estado_produto (const char *texto, EstadoProduto *estado) {
    if (!texto) return false;
    if (strcmp(texto, "ativo") == 0) {
        if (estado) *estado = ESTADO_PROD_ATIVO;
        return true;
    }
    if (strcmp(texto, "descontinuado") == 0) {
        if (estado) *estado = ESTADO_PROD_DESCONTINUADO;
        return true;
    }
    return false;
}

bool validar_estado_encomenda(const char *texto, EstadoEncomenda *estado) {
    if (!texto) return false;

    if (strcmp (texto, "paga") == 0) {
        if (estado) *estado = ESTADO_ENC_PAGA;
        return true;
    }
    if (strcmp(texto, "enviada") == 0) {
        if (estado) *estado = ESTADO_ENC_ENVIADA;
        return true;
    }
     if (strcmp(texto, "entregue") == 0) {
        if (estado) *estado = ESTADO_ENC_ENTREGUE;
        return true;
    }   
    if (strcmp(texto, "cancelada") == 0) {
        if (estado) *estado = ESTADO_ENC_CANCELADA;
        return true;
    }
    return false;
}    










bool validar_linha_cliente (const char  **campos, int n_campos) {
    if ( n_campos < 4 ) return false;
    if ( !validar_id (campos[0] , 'C' )) return false;
    if ( !validar_texto (campos[1])) return false;
    if ( !validar_texto (campos [2])) return false;
    if ( !validar_sem_espacos (campos[3])) return false;
    return true;
}

bool validar_linha_vendedor (const char  **campos, int n_campos) {
     if ( n_campos < 4 ) return false;
     if ( !validar_id (campos[0], 'V' )) return false;
     if ( !validar_texto (campos[1])) return false;
     if ( !validar_sem_espacos(campos[2])) return false;
     if ( !validar_data (campos[3])) return false;
     return true;
}
