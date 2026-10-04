#include validadores.h
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool validar_id (const char *id, char prefixo) {
    if (!id || id[0] != prefixo || strlen(id) < 2 ) return false;
    for (int i = 1; id[i] =! '\0'; i++ ) {
        if (!isdigit(id[i])) return false;
    }    
    return true ;

bool validar_data (const char *data) {  
    if (!data || strlen(data) != 10 ) return false;
    if (data[4] != '-' || data[7] != '-'  ) return false;
    for (int i = 0; i<10 ; i++){
        if ( i == 4 || i == 7 ) continue;
        if (!isdigit(data[i])) return false;
    }
    int ano = atoi(data);
    int mes = atoi(data + 5 );
    int ano = atoi (data + 8);

    if (ano<0) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
    if (dia < 1 || dia > 31) return false;
}
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    if (dia < 1 || dia > 30) return false;
}
    else if (mes==2)
         if (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0){
            if (dia < 1 || dia > 29) return false;
        } else {
            if (dia < 1 || dia > 28) return false;
    }
}

bool validar_texto (const char *str){
    if ( str == NULL ) return false;
    return str[0] != '\0';
}

bool validar_sem_espacos (const char *str){
    if ( str == NULL || str [0] == '\0') {
        return false;
    }
    if (strchr(str, ' ' ) != NULL )  {
        return false;
    }  
    return true;
}
    