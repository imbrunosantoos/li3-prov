// Testes unitários dos módulos 

#include <stdio.h>

#include "gestor_produtos.h"
#include "gestor_encomendas.h"

static int total = 0;
static int falhas = 0;

// Guião 9 - conta o teste e, se a condição for falsa, conta uma falha e mostra a condição e a linha
#define VERIFICA(cond) do {                                   \
    total++;                                                  \
    if (!(cond)) {                                            \
        falhas++;                                             \
        printf("FALHA: %s (linha %d)\n", #cond, __LINE__);    \
    }                                                         \
} while (0)

// ---------- Gestor de produtos


// Cria um produto de teste; só o id importa nestes testes
static Produto *produto_teste(const char *id) {
    return produto_novo(id, "Caneca", "Casa", 1000, "V000001", PRODUTO_ATIVO);
}

// Caso normal: procurar pelo id devolve o mesmo produto que foi inserido
static void teste_gestor_produtos_normal(void) {
    GestorProdutos *ge = gestor_produtos_create();
    Produto *p = produto_teste("P000001");

    VERIFICA(gestor_produtos_inserir(ge, p));
    VERIFICA(gestor_produtos_procurar(ge, "P000001") == p);

    gestor_produtos_destroy(ge);
}

// Caso-limite: procurar num gestor vazio devolve NULL
static void teste_gestor_produtos_limite(void) {
    GestorProdutos *ge = gestor_produtos_create();

    VERIFICA(gestor_produtos_procurar(ge, "P000001") == NULL);

    gestor_produtos_destroy(ge);
}

// Casos de erro: id repetido e gestor NULL são recusados
static void teste_gestor_produtos_erro(void) {
    GestorProdutos *ge = gestor_produtos_create();
    Produto *original = produto_teste("P000001");
    gestor_produtos_inserir(ge, original);

    VERIFICA(!gestor_produtos_inserir(ge, produto_teste("P000001")));
    // o produto original não foi substituído pelo repetido
    VERIFICA(gestor_produtos_procurar(ge, "P000001") == original);
    VERIFICA(!gestor_produtos_inserir(NULL, produto_teste("P000002")));

    gestor_produtos_destroy(ge);
}

// -------   Gestor de encomendas

// Cria uma encomenda de teste só o id importa nestes testes
static Encomenda *encomenda_teste(const char *id) {
    return encomenda_nova(id, "C000001", "2026-01-01", ENCOMENDA_PAGA);
}

// Caso normal- procurar pelo id devolve a mesma encomenda que foi inserida
static void teste_gestor_encomendas_normal(void) {
    GestorEncomendas *ge = gestor_encomendas_create();
    Encomenda *e = encomenda_teste("O000001");

    VERIFICA(gestor_encomendas_inserir(ge, e));
    VERIFICA(gestor_encomendas_procurar(ge, "O000001") == e);

    gestor_encomendas_destroy(ge);
}

// Caso limite - procurar num gestor vazio devolve NULL
static void teste_gestor_encomendas_limite(void) {
    GestorEncomendas *ge = gestor_encomendas_create();

    VERIFICA(gestor_encomendas_procurar(ge, "O000001") == NULL);

    gestor_encomendas_destroy(ge);
}

// Casos de erro - id repetido e gestor NULL são recusados
static void teste_gestor_encomendas_erro(void) {
    GestorEncomendas *ge = gestor_encomendas_create();
    Encomenda *original = encomenda_teste("O000001");
    gestor_encomendas_inserir(ge, original);

    VERIFICA(!gestor_encomendas_inserir(ge, encomenda_teste("O000001")));

    // a encomenda original não foi substituída pela repetida
    VERIFICA(gestor_encomendas_procurar(ge, "O000001") == original);
    VERIFICA(!gestor_encomendas_inserir(NULL, encomenda_teste("O000002")));

    gestor_encomendas_destroy(ge);
}


int main(void) {
    teste_gestor_produtos_normal();
    teste_gestor_produtos_limite();
    teste_gestor_produtos_erro();
    teste_gestor_encomendas_normal();
    teste_gestor_encomendas_limite();
    teste_gestor_encomendas_erro();

    printf("Testes: %d, falhas: %d\n", total, falhas);

    if (falhas > 0) return 1;
    return 0;
}