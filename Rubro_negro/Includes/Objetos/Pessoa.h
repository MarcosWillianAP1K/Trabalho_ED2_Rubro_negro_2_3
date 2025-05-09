#include "Data.h"

#pragma once

typedef struct PESSOA
{
    char *CPF;
    char *nome;
    char *CEP_natal;
    char *CEP_atual;
    DATA *data_nascimento;

}PESSOA;



PESSOA *alocar_pessoa();

PESSOA *criar_pessoa(char *CPF, char *nome, char *CEP_natal, char *CEP_atual, char *data_nascimento);

void imprimir_pessoa(PESSOA *pessoa);

void liberar_pessoa(PESSOA **pessoa);

