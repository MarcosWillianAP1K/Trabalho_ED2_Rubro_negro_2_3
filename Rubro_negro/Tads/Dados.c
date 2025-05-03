#include "../Includes/Dados.h"
#include <stdio.h>

void imprimir_dados_cidade(DADOS *dado)
{
    imprimir_cidade(dado->cidade);
}

void imprimir_dados_pessoa (DADOS *dado)
{
    imprimir_pessoa(dado->pessoa);
}

void imprimir_dados_cep (DADOS *dado)
{
    imprimir_cep(dado->cep);
}




void liberar_dados(DADOS **dado)
{
    if(dado != NULL)
    {
        free(*dado);
        *dado = NULL;
    }
}


void liberar_dados_cidade(DADOS **dado)
{
    if(dado != NULL)
    {
        if((*dado)->cidade != NULL)
        {
           liberar_cidade(&((*dado)->cidade));
        }
        liberar_dados(dado);
    }
}

void liberar_dados_pessoa(DADOS **dado)
{
    if(dado != NULL)
    {
        if((*dado)->pessoa != NULL)
        {
            liberar_pessoa(&((*dado)->pessoa));
        }
        liberar_dados(dado);
    }
}

void liberar_dados_cep(DADOS **dado)
{
    if(dado != NULL)
    {
        if((*dado)->cep != NULL)
        {
            liberar_cep(&((*dado)->cep));
        }
        liberar_dados(dado);
    }
}