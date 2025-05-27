#include "../Estruturas/Lista_duplamente.h"
#include "../Estruturas/Rubro_negro.h"


#pragma once

void delete_all(LISTA_DUPLAMENTE **lista_estado, RUBRO_NEGRO **raiz_pessoa);

short int verificar_se_existe_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

short int verificar_se_existe_pessoa_associada_a_um_CEP(RUBRO_NEGRO *pessoas, char *CEP);

LISTA_DUPLAMENTE *cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info);

RUBRO_NEGRO *cadastrar_cidade(ESTADO *estado, CIDADE info);

RUBRO_NEGRO *cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep);

RUBRO_NEGRO *cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA info);

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep);

RUBRO_NEGRO *remover_pessoa(RUBRO_NEGRO **raiz, PESSOA info);

LISTA_DUPLAMENTE *procurar_estado_mais_populoso(LISTA_DUPLAMENTE *lista_estado);

RUBRO_NEGRO *procurar_capital_de_um_estado(ESTADO estado);

RUBRO_NEGRO *procurar_cidade_mais_populosa_sem_capital(RUBRO_NEGRO *raiz_cidade, char *nome_capital);

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, RUBRO_NEGRO *raiz_pessoa);

RUBRO_NEGRO *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep);

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(RUBRO_NEGRO *raiz_pessoa, CIDADE cidade);

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(RUBRO_NEGRO *raiz_pessoa, CIDADE cidade);

void mostrar_tudo(LISTA_DUPLAMENTE *lista, RUBRO_NEGRO *raiz_pessoa);
