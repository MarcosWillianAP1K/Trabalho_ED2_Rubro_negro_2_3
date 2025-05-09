#include "../../Includes/Estruturas/Dados.h"
#include <stdio.h>
#include <stdlib.h>

void imprimir_dados_cidade(DADOS *dado)
{
    imprimir_cidade(dado->cidade);
}

void imprimir_dados_pessoa (DADOS *dado)
{
    imprimir_pessoa(dado->pessoa);
}

void imprimir_dados_CEP (DADOS *dado)
{
    imprimir_CEP(dado->CEP);
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

void liberar_dados_CEP(DADOS **dado)
{
    if(dado != NULL)
    {
        if((*dado)->CEP != NULL)
        {
            liberar_CEP(&((*dado)->CEP));
        }
        liberar_dados(dado);
    }
}