#include "../Objetos/Cidade.h"
#include "../Objetos/Pessoa.h"
#include "../Objetos/CEP.h"


#pragma once

typedef union DADOS
{
    CIDADE cidade;
    PESSOA pessoa;
    char *CEP;
}DADOS;


void imprimir_dados_cidade(DADOS dado);

void imprimir_dados_pessoa (DADOS dado);

void imprimir_dados_CEP (DADOS dado);

// DADOS *alocar_dados();

// void liberar_dados(DADOS *dado);


void liberar_dados_cidade(DADOS *dado);

void liberar_dados_pessoa(DADOS *dado);

void liberar_dados_CEP(DADOS *dado);



short int comparar_dados_nome_cidade(DADOS dado1, DADOS dado2);

short int comparar_dados_nome_pessoa(DADOS dado1, DADOS dado2);

short int comparar_dados_CPF_pessoa(DADOS dado1, DADOS dado2);

short int comparar_dados_CEP(DADOS dado1, DADOS dado2);