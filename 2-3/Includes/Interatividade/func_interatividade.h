#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/2-3.h"


#pragma once

void delete_all(LISTA_DUPLAMENTE **lista_estado, Arv23 **raiz_pessoa);

short int verificar_se_existe_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

short int verificar_se_existe_pessoa_associada_a_um_CEP(Arv23 *pessoas, char *CEP);

LISTA_DUPLAMENTE *cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info);

Arv23 *cadastrar_cidade(ESTADO *estado, CIDADE info);

Arv23 *cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep);

Arv23 *cadastrar_pessoa(Arv23 **raiz, PESSOA info);

Arv23 *remover_CEP(CIDADE *cidade, char *cep);

Arv23 *remover_pessoa(Arv23 **raiz, PESSOA info);

LISTA_DUPLAMENTE *procurar_estado_mais_populoso(LISTA_DUPLAMENTE *lista_estado);

Arv23 *procurar_capital_de_um_estado(ESTADO estado);

Arv23 *procurar_cidade_mais_populosa_sem_capital(Arv23 *raiz_cidade, char *nome_capital);

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, Arv23 *raiz_pessoa);

Arv23 *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(Arv23 *raiz_pessoa, CIDADE cidade);

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(Arv23 *raiz_pessoa, CIDADE cidade);

void mostrar_tudo(LISTA_DUPLAMENTE *lista, Arv23 *raiz_pessoa);
