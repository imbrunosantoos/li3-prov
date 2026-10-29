// Testes unitários dos módulos 

#include <stdio.h>

#include "gestor_produtos.h"
#include "gestor_encomendas.h"
#include "gestor_linhas_encomenda.h"
#include "gestor_estatisticas.h"


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


// ---------- Gestor de linhas de encomenda

// Cria uma linha de teste -  só os ids importam nestes testes
static LinhaEncomenda *linha_teste(const char *id_encomenda, const char *id_produto) {
    return linha_encomenda_nova(id_encomenda, id_produto, 1, 1000);
}

// Caso normal: duas linhas da mesma encomenda ficam juntas, pela ordem de chegada
static void teste_gestor_linhas_normal(void) {
    GestorLinhaEncomenda *gl = gestor_linha_encomenda_create();
    LinhaEncomenda *l1 = linha_teste("O000001", "P000001");
    LinhaEncomenda *l2 = linha_teste("O000001", "P000002");

    VERIFICA(gestor_linha_encomenda_inserir(gl, l1));
    VERIFICA(gestor_linha_encomenda_inserir(gl, l2));
    VERIFICA(gestor_linha_encomenda_num_linhas(gl, "O000001") == 2);
    VERIFICA(gestor_linha_encomenda_get_linha(gl, "O000001", 0) == l1);
    VERIFICA(gestor_linha_encomenda_get_linha(gl, "O000001", 1) == l2);

    gestor_linha_encomenda_destroy(gl);
}

// Caso-limite: encomenda sem linhas tem 0 linhas e posição fora dos limites devolve NULL
static void teste_gestor_linhas_limite(void) {
    GestorLinhaEncomenda *gl = gestor_linha_encomenda_create();
    gestor_linha_encomenda_inserir(gl, linha_teste("O000001", "P000001"));

    VERIFICA(gestor_linha_encomenda_num_linhas(gl, "O000002") == 0);
    VERIFICA(gestor_linha_encomenda_get_linha(gl, "O000001", 1) == NULL);

    gestor_linha_encomenda_destroy(gl);
}

// Casos de erro- par (encomenda, produto) repetido e gestor NULL são recusados
static void teste_gestor_linhas_erro(void) {
    GestorLinhaEncomenda *gl = gestor_linha_encomenda_create();
    gestor_linha_encomenda_inserir(gl, linha_teste("O000001", "P000001"));

    VERIFICA(gestor_linha_encomenda_existe_par(gl, "O000001", "P000001"));
    VERIFICA(!gestor_linha_encomenda_inserir(gl, linha_teste("O000001", "P000001")));
    // a linha repetida não entrou
    VERIFICA(gestor_linha_encomenda_num_linhas(gl, "O000001") == 1);
    VERIFICA(!gestor_linha_encomenda_inserir(NULL, linha_teste("O000001", "P000002")));

    gestor_linha_encomenda_destroy(gl);
}

// ---------- Gestor de estatísticas

// Caso normal: duas linhas não canceladas do mesmo produto somam unidades e receita
static void teste_gestor_estatisticas_normal(void) {
    GestorEstatisticas *ge = gestor_estatisticas_create();
    // 2 x 10,00 € e 5 x 10,00 €
    LinhaEncomenda *l1 = linha_encomenda_nova("O000001", "P000001", 2, 1000);
    LinhaEncomenda *l2 = linha_encomenda_nova("O000002", "P000001", 5, 1000);

    VERIFICA(gestor_estatisticas_registrar_linha(ge, l1, ENCOMENDA_PAGA));
    VERIFICA(gestor_estatisticas_registrar_linha(ge, l2, ENCOMENDA_ENTREGUE));
    VERIFICA(gestor_estatisticas_get_unidades(ge, "P000001") == 7);
    VERIFICA(gestor_estatisticas_get_receita_cents(ge, "P000001") == 7000);

    // o gestor de estatísticas não fica com as linhas, por isso o teste destrói-as
    linha_encomenda_destroy(l1);
    linha_encomenda_destroy(l2);
    gestor_estatisticas_destroy(ge);
}

// Casos-limite: produto sem vendas dá 0; linha de encomenda cancelada é aceite mas não conta;
// receita acima do limite de um int (3 000 000 000 cêntimos) não transborda
static void teste_gestor_estatisticas_limite(void) {
    GestorEstatisticas *ge = gestor_estatisticas_create();
    LinhaEncomenda *cancelada = linha_encomenda_nova("O000001", "P000001", 4, 1000);
    LinhaEncomenda *grande = linha_encomenda_nova("O000002", "P000002", 1000, 3000000);

    VERIFICA(gestor_estatisticas_get_unidades(ge, "P000003") == 0);
    VERIFICA(gestor_estatisticas_get_receita_cents(ge, "P000003") == 0);
    VERIFICA(gestor_estatisticas_registrar_linha(ge, cancelada, ENCOMENDA_CANCELADA));
    VERIFICA(gestor_estatisticas_get_unidades(ge, "P000001") == 0);
    VERIFICA(gestor_estatisticas_registrar_linha(ge, grande, ENCOMENDA_PAGA));
    VERIFICA(gestor_estatisticas_get_receita_cents(ge, "P000002") == 3000000000);

    linha_encomenda_destroy(cancelada);
    linha_encomenda_destroy(grande);
    gestor_estatisticas_destroy(ge);
}

// Casos de erro: gestor ou linha NULL são recusados; os getters com NULL dão 0
static void teste_gestor_estatisticas_erro(void) {
    GestorEstatisticas *ge = gestor_estatisticas_create();
    LinhaEncomenda *l = linha_encomenda_nova("O000001", "P000001", 1, 1000);

    VERIFICA(!gestor_estatisticas_registrar_linha(NULL, l, ENCOMENDA_PAGA));
    VERIFICA(!gestor_estatisticas_registrar_linha(ge, NULL, ENCOMENDA_PAGA));
    VERIFICA(gestor_estatisticas_get_unidades(NULL, "P000001") == 0);
    VERIFICA(gestor_estatisticas_get_receita_cents(ge, NULL) == 0);
    // destruir NULL não pode rebentar
    gestor_estatisticas_destroy(NULL);

    linha_encomenda_destroy(l);
    gestor_estatisticas_destroy(ge);
}


int main(void) {
    teste_gestor_produtos_normal();
    teste_gestor_produtos_limite();
    teste_gestor_produtos_erro();
    teste_gestor_encomendas_normal();
    teste_gestor_encomendas_limite();
    teste_gestor_encomendas_erro();
    teste_gestor_linhas_normal();
    teste_gestor_linhas_limite();
    teste_gestor_linhas_erro();
    teste_gestor_estatisticas_normal();
    teste_gestor_estatisticas_limite();
    teste_gestor_estatisticas_erro();

    
    printf("Testes: %d, falhas: %d\n", total, falhas);

    if (falhas > 0) return 1;
    return 0;
}