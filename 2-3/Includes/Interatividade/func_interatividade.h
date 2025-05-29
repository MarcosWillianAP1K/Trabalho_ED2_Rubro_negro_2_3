#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/2-3.h"


#pragma once

void delete_all(LISTA_DUPLAMENTE **lista_estado, Arv23 **raiz_pessoa);

short int verificar_se_existe_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

short int verificar_se_existe_pessoa_associada_a_um_CEP(Arv23 *pessoas, char *CEP);

LISTA_DUPLAMENTE *cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info);

short int cadastrar_cidade(ESTADO *estado, CIDADE info);

short int cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep);

short int cadastrar_pessoa(Arv23 **raiz, PESSOA info);

short int remover_CEP(CIDADE *cidade, char *cep, char *cep_removido);

short int remover_pessoa(Arv23 **raiz, PESSOA info, PESSOA *pessoa_removida);

LISTA_DUPLAMENTE *procurar_estado_mais_populoso(LISTA_DUPLAMENTE *lista_estado);

CIDADE *procurar_capital_de_um_estado(ESTADO estado);

CIDADE *procurar_cidade_mais_populosa_sem_capital(Arv23 *raiz_cidade, char *nome_capital);

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, Arv23 *raiz_pessoa);

CIDADE *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(Arv23 *raiz_pessoa, CIDADE cidade);

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(Arv23 *raiz_pessoa, CIDADE cidade);

void mostrar_tudo(LISTA_DUPLAMENTE *lista, Arv23 *raiz_pessoa);
