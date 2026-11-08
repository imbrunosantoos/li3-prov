#include "validadores.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool validar_id (const char *id, char prefixo) {
    // tem de ter o prefixo e pelo menos um dígito a seguir (strlen >= 2)
    if (!id || id[0] != prefixo || strlen(id) < 2 ) return false;
    // o cast para unsigned char é preciso porque isdigit não aceita valores negativos
    for (int i = 1 ; id[i] != '\0'; i++ ) {
        if (!isdigit((unsigned char)id[i])) return false;
    }    
    return true ;
}

bool validar_data (const char *data) {  
    // formato AAAA-MM-DD tem sempre 10 caracteres, com '-' nas posições 4 e 7
    if (!data || strlen(data) != 10 ) return false;
    if (data[4] != '-' || data[7] != '-'  ) return false;
   // todas as outras posições têm de ser dígitos
    for (int i = 0; i<10 ; i++){
        if ( i == 4 || i == 7 ) continue;
        if (!isdigit ( ( unsigned char )data[i])) return false;
    }
     // atoi pára no primeiro carácter que não é dígito, por isso lê só o campo que interessa
    int ano = atoi(data);
    int mes = atoi(data + 5 );
    int dia = atoi (data + 8);
    // o enunciado dispensa validar os dias de cada mês, por isso o dia vai só até 31
    if (ano<0) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    return true ;
}


bool validar_texto (const char *str){
    // o ';' é o separador do CSV, por isso não pode aparecer dentro de um campo
    if ( str == NULL || str [0] == '\0' ) return false;
    if (strchr(str, ';') != NULL) return false;
    return true;
}

bool validar_sem_espacos (const char *str){
    // como validar_texto, mas sem espaços, para a categoria poder ser argumento de um comando
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
           // só um ponto, e não pode ser o primeiro carácter (rejeita .50 e 1.2.3)
            pontos++;
            if (pontos > 1 || i == 0) return false;  
        } else if (!isdigit((unsigned char)texto[i])) {
           // rejeita sinais, vírgulas, espaços e letras
            return false;
        } else if (pontos == 1) {
           // dígitos depois do ponto
            casas_decimais++;
        }
        i++;
    }
    // texto[i - 1] é o último carácter: não pode ser o ponto (rejeita 3.)
    // no máximo duas casas decimais (rejeita 3.500)
    if ( i == 0 || texto[i-1] == '.' || casas_decimais > 2 ) return false;
    // converte para cêntimos, para guardar o preço como inteiro e evitar erros de float
    if (cents != NULL) {
        char *ponto = strchr (texto, '.');
        if (!ponto) {
            // sem ponto: 3 fica 300
            *cents = atoll(texto) * 100;
        } else if (casas_decimais == 1) {
           // uma casa: 3.5 fica 350 (o 5 vale 50 cêntimos)
            int64_t inteiros = atoll(texto);
            int64_t decimais = atoi(ponto + 1);
            *cents = inteiros * 100 + decimais * 10;
        } else {
           // duas casas: 3.50 fica 350
            int64_t inteiros = atoll(texto);
            int64_t decimais = atoi (ponto + 1 );
            *cents = inteiros * 100 + decimais ;
        }
    }
    return true;
}            

bool validar_quantidade (const char *texto, int *quantidade) {
    if (!texto || texto [0] == '\0') return false;
     // rejeita zeros à esquerda e também o próprio 0
    if (texto[0] == '0') return false;
    // só dígitos, o que rejeita -2, 1.5 e dois
    for (int i = 0; texto[i] != '\0'; i++){
        if (!isdigit((unsigned char)texto[i])) return false;
    }
    long val = atol(texto);
    if (val < 1) return false;
    // quantidade é opcional: quem só quer validar passa NULL
    if (quantidade != NULL) {
        *quantidade = (int)val;
    }
    return true;
}
// as funções validar_linha_* só verificam a sintaxe de cada campo
// se a referência existe (vendedor, cliente, ...) verifica-se no carregamento
bool validar_linha_produto (const char **campos, int n_campos) {
    if (n_campos < 6) return false;
    if (!validar_id(campos [0], 'P')) return false;
    if (!validar_texto(campos [1])) return false;
    if (!validar_sem_espacos(campos [2])) return false;
    if (!validar_preco(campos [3], NULL)) return false;
    if (!validar_id(campos [4], 'V')) return false;
    if (!validar_estado_produto(campos [5], NULL)) return false;
    return true;
}

bool validar_linha_encomenda (const char **campos, int n_campos) {
    if (n_campos < 4 ) return false;
    if (!validar_id(campos[0], 'O')) return false;
    if (!validar_id(campos[1], 'C')) return false;
    if (!validar_data(campos[2])) return false;
    if (!validar_estado_encomenda(campos[3], NULL)) return false;
    return true;
}    


bool validar_linha_linhas_encomenda (const char **campos, int n_campos){
    if (n_campos < 4) return false;
    if (!validar_id (campos [0], 'O')) return false;
    if (!validar_id (campos [1], 'P')) return false;
    if (!validar_quantidade (campos [2], NULL)) return false;
    if (!validar_preco(campos [3], NULL)) return false;
    return true;
}    




bool validar_estado_produto (const char *texto, EstadoProduto *estado) {
    if (!texto) return false;
     // strcmp exato: maiúsculas ou variantes são inválidas, como pede o enunciado
    if (strcmp(texto, "ativo") == 0) {
        if (estado) *estado = PRODUTO_ATIVO;
        return true;
    }
    if (strcmp(texto, "descontinuado") == 0) {
        if (estado) *estado = PRODUTO_DESCONTINUADO;
        return true;
    }
    return false;
}

bool validar_estado_encomenda(const char *texto, EstadoEncomenda *estado) {
    if (!texto) return false;
    // strcmp exato, o estado só é escrito no enum se o ponteiro não for NULL
    // uma encomenda cancelada é válida, só fica fora das estatísticas
    if (strcmp (texto, "paga") == 0) {
        if (estado) *estado = ENCOMENDA_PAGA;
        return true;
    }
    if (strcmp(texto, "enviada") == 0) {
        if (estado) *estado = ENCOMENDA_ENVIADA;
        return true;
    }
     if (strcmp(texto, "entregue") == 0) {
        if (estado) *estado = ENCOMENDA_ENTREGUE;
        return true;
    }   
    if (strcmp(texto, "cancelada") == 0) {
        if (estado) *estado = ENCOMENDA_CANCELADA;
        return true;
    }
    return false;
}    









// as funções validar_linha_* só verificam a sintaxe de cada campo
// se a referência existe (vendedor, cliente, ...) verifica-se no carregamento

bool validar_linha_cliente (const char  **campos, int n_campos) {
    if ( n_campos < 4 ) return false;
    if ( !validar_id (campos[0] , 'C' )) return false;
    if ( !validar_texto (campos[1])) return false;
    if ( !validar_sem_espacos (campos [2])) return false;
    if ( !validar_data (campos[3])) return false;
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
