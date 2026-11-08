#ifndef CARREGAMENTO_H
#define CARREGAMENTO_H

#include "gestor_clientes.h"
#include "gestor_vendedores.h"
#include "gestor_produtos.h"
#include "gestor_encomendas.h"
#include "gestor_linhas_encomenda.h"
#include "gestor_estatisticas.h"

/**
 * @brief Carrega os clientes de um CSV, as linhas inválidas vão para o ficheiro de erros
 * @param entrada Caminho do clientes.csv
 * @param erros   Caminho do ficheiro de erros a criar (com o cabeçalho original)
 * @param gc      Gestor onde inserir os clientes válidos
 * @return 0 se correu bem, -1 se não conseguiu abrir algum ficheiro
 */

int carregar_clientes(const char *entrada, const char *erros, GestorClientes *gc);

/**
 * @brief Carrega os vendedores de um CSV, as linhas inválidas vão para o ficheiro de erros
 * @param entrada Caminho do vendedores.csv
 * @param erros   Caminho do ficheiro de erros a criar (com o cabeçalho original)
 * @param gv      Gestor onde inserir os vendedores válidos
 * @return 0 se correu bem, -1 se não conseguiu abrir algum ficheiro
 */

int carregar_vendedores(const char *entrada, const char *erros, GestorVendedores *gv);

/**
 * @brief Carrega os produtos de um CSV, é inválido o produto cujo vendedor não existe
 * @param entrada Caminho do produtos.csv
 * @param erros   Caminho do ficheiro de erros a criar (com o cabeçalho original)
 * @param gp      Gestor onde inserir os produtos válidos
 * @param gv      Gestor de vendedores, só para consulta
 * @return 0 se correu bem, -1 se não conseguiu abrir algum ficheiro
 */

int carregar_produtos(const char *entrada, const char *erros, GestorProdutos *gp, GestorVendedores *gv);

/**
 * @brief Carrega as encomendas de um CSV, é inválida a encomenda cujo cliente não existe
 * @param entrada Caminho do encomendas.csv
 * @param erros   Caminho do ficheiro de erros a criar (com o cabeçalho original)
 * @param ge      Gestor onde inserir as encomendas válidas
 * @param gc      Gestor de clientes, só para consulta
 * @return 0 se correu bem, -1 se não conseguiu abrir algum ficheiro
 */

int carregar_encomendas(const char *entrada, const char *erros, GestorEncomendas *ge, GestorClientes *gc);

/**
 * @brief Carrega as linhas de encomenda de um CSV
 * é inválida a linha cuja encomenda ou produto não existe, ou cujo par (encomenda, produto) já existe
 * @param entrada Caminho do linhas_encomenda.csv
 * @param erros   Caminho do ficheiro de erros a criar (com o cabeçalho original)
 * @param gl      Gestor onde inserir as linhas válidas
 * @param ge      Gestor de encomendas, só para consulta
 * @param gp      Gestor de produtos, só para consulta
 * @param gs      Gestor de estatísticas, atualizado a cada linha válida
 * @return 0 se correu bem, -1 se não conseguiu abrir algum ficheiro
 */


int carregar_linhas(const char *entrada, const char *erros, GestorLinhaEncomenda *gl, GestorEncomendas *ge, GestorProdutos *gp, GestorEstatisticas *gs);

#endif
