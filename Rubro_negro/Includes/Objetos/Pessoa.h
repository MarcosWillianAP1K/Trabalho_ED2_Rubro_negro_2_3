#include "Data.h"
#include "CPF.h"

#pragma once

typedef struct PESSOA
{
    char *CPF;
    char *nome;
    char *CEP_natal;
    char *CEP_atual;
    DATA data_nascimento;

}PESSOA;



// PESSOA *alocar_pessoa();

PESSOA criar_pessoa(char *CPF, char *nome, char *CEP_natal, char *CEP_atual, DATA data_nascimento);

void imprimir_pessoa(PESSOA pessoa);

void liberar_pessoa(PESSOA *pessoa);

short int comparar_nome_pessoas(PESSOA pessoa1, PESSOA pessoa2);

short int comparar_CPF_pessoas(PESSOA pessoa1, PESSOA pessoa2);

