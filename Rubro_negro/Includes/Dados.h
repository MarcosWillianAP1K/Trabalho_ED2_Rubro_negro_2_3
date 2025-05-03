#include "Pessoa.h"
#include "CEP.h"
#include "Cidade.h"


#pragma once

typedef union DADOS
{
    CIDADE *cidade;
    PESSOA *pessoa;
    CEP *cep;
}DADOS;


void imprimir_dados_cidade(DADOS *dado);

void imprimir_dados_pessoa (DADOS *dado);

void imprimir_dados_cep (DADOS *dado);


void liberar_dados(DADOS **dado);


void liberar_dados_cidade(DADOS **dado);

void liberar_dados_pessoa(DADOS **dado);

void liberar_dados_cep(DADOS **dado);