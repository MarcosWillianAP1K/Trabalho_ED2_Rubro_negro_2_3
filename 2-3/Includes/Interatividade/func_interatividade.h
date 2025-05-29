#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/2-3.h"


#pragma once

//Liberar memoria
void delete_all(LISTA_DUPLAMENTE **lista_estado, AVR_23 **raiz_pessoa);

//Verificações
short int verificar_se_existe_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

short int verificar_se_existe_pessoa_associada_a_um_CEP(AVR_23 *pessoas, char *CEP);


//Cadastrar 
LISTA_DUPLAMENTE *cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info);

short int cadastrar_cidade(ESTADO *estado, CIDADE info);

short int cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep);

short int cadastrar_pessoa(AVR_23 **raiz, PESSOA info);

//Remover
short int remover_CEP(CIDADE *cidade, char *cep, char **cep_removido);

short int remover_pessoa(AVR_23 **raiz, PESSOA info, PESSOA *pessoa_removida);

//Consultas

LISTA_DUPLAMENTE *procurar_estado_mais_populoso(LISTA_DUPLAMENTE *lista_estado);

CIDADE *procurar_capital_de_um_estado(ESTADO estado);

CIDADE *procurar_cidade_mais_populosa_sem_capital(AVR_23 *raiz_cidade, char *nome_capital);

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, AVR_23 *raiz_pessoa);

CIDADE *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(AVR_23 *raiz_pessoa, CIDADE cidade);

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(AVR_23 *raiz_pessoa, CIDADE cidade);


//Imprimir tudo
void mostrar_tudo(LISTA_DUPLAMENTE *lista, AVR_23 *raiz_pessoa);
