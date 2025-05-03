

#pragma once

typedef struct CEP
{
    char *cep;
}CEP;


CEP *alocar_cep();

CEP *criar_cep(char *cep);

void imprimir_cep(CEP *cep);

void liberar_cep(CEP **cep);


