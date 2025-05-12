#include "../../Includes/Interatividade/Func_interatividade.h"
#include <stdio.h>
#include <stdlib.h>

short int cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO *info)
{
    return inserir_ordernado_duplamente(raiz, info);
}

short int cadastrar_cidade(ESTADO *estado, CIDADE *info, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (estado != NULL)
    {
        DADOS aux;
        aux.cidade = *info;

        retorno = inserir_rubro_negro_void(&estado->raiz_arvore_cidade, &aux, comparar);
    }

    return retorno;
}

short int cadastrar_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        retorno = inserir_rubro_negro_void(&cidade->raiz_arvore_CEPs, &aux, comparar);
    }

    return retorno;
}

short int cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA *info, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (raiz != NULL && info != NULL)
    {
        DADOS aux;
        aux.pessoa = *info;

        retorno = inserir_rubro_negro(raiz, &aux, comparar);
    }

    return retorno;
}

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *))
{
    RUBRO_NEGRO *retorno = NULL;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        retorno = remover_rubro_negro_void(&cidade->raiz_arvore_CEPs, &aux, comparar);
    }

    return retorno;
}

RUBRO_NEGRO *remover_pessoa(RUBRO_NEGRO **raiz, PESSOA *info, short int (*comparar)(DADOS *, DADOS *))
{
    RUBRO_NEGRO *retorno = NULL;

    if (info != NULL)
    {
        DADOS aux;
        aux.pessoa = *info;

        retorno = remover_rubro_negro(raiz, &aux, comparar);
    }

    return retorno;
}
