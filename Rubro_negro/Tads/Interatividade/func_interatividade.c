#include "../../Includes/Interatividade/Func_interatividade.h"
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
short int cadastrar_estado(LISTA_DUPLAMENTE **raiz, ESTADO info)
=======
//===============VERIFICAÇÕES===============

short int pecorrer_cidade(RUBRO_NEGRO *raiz_cidade, DADOS *cep)
>>>>>>> 7ad178b32996585c6472c5d4d21bd51464867347
{
    short int retorno = 0;

    if(raiz_cidade)
    {
        if(buscar_rubro_negro(raiz_cidade->info.cidade.raiz_arvore_CEPs, cep, comparar_dados_CEP) == NULL)
        {
            retorno = pecorrer_cidade(raiz_cidade->esquerda, cep);

            if (retorno == 0)
                retorno = pecorrer_cidade(raiz_cidade->direita, cep);
        }
        else
            retorno = 1;
    }

    return retorno;  
}

short int percorrer_estado(LISTA_DUPLAMENTE *raiz_estado, DADOS *cep)
{
    short int retorno = 0;

    if(raiz_estado != NULL)
    {
        retorno = pecorrer_cidade(raiz_estado->estado.raiz_arvore_cidade, cep);

        if (retorno == 0)
            retorno = percorrer_estado(raiz_estado->prox, cep);
    }

    return retorno;  
}

short int verificar_se_ja_existe_CEP(LISTA_DUPLAMENTE *raiz_estado, DADOS *cep)
{
    short int retorno = 0;

    if (raiz_estado != NULL)
    {
        retorno = percorrer_estado(raiz_estado, cep);
    }

    return retorno;
}

//===============CADASTROS===============

short int cadastrar_estado(LISTA_DUPLAMENTE **raiz_estado, ESTADO *info)
{
    return inserir_ordernado_duplamente(raiz_estado, info);
}

short int cadastrar_cidade(ESTADO *estado, CIDADE info, short int (*comparar)(DADOS, DADOS))
{
    short int retorno = 0;

    if (estado != NULL)
    {
        DADOS aux;
        aux.cidade = info;

        retorno = inserir_rubro_negro_void(&estado->raiz_arvore_cidade, aux, comparar);
    }

    return retorno;
}

<<<<<<< HEAD
short int cadastrar_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS, DADOS))
=======
short int cadastrar_CEP(LISTA_DUPLAMENTE *raiz_estado, CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *))
>>>>>>> 7ad178b32996585c6472c5d4d21bd51464867347
{
    short int retorno = 0;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

<<<<<<< HEAD
        retorno = inserir_rubro_negro_void(&cidade->raiz_arvore_CEPs, aux, comparar);
=======
        if (verificar_se_ja_existe_CEP(raiz_estado, &aux) == 0)
        {
            retorno = inserir_rubro_negro_void(&cidade->raiz_arvore_CEPs, &aux, comparar);
        }
>>>>>>> 7ad178b32996585c6472c5d4d21bd51464867347
    }

    return retorno;
}

short int cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA info, short int (*comparar)(DADOS, DADOS))
{
    short int retorno = 0;

    DADOS aux;
    aux.pessoa = info;

    retorno = inserir_rubro_negro(raiz, aux, comparar);

    return retorno;
}

<<<<<<< HEAD
RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS, DADOS))
=======

//===============REMOÇÕES===============

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *))
>>>>>>> 7ad178b32996585c6472c5d4d21bd51464867347
{
    RUBRO_NEGRO *retorno = NULL;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        retorno = remover_rubro_negro_void(&cidade->raiz_arvore_CEPs, aux, comparar);
    }

    return retorno;
}

RUBRO_NEGRO *remover_pessoa(RUBRO_NEGRO **raiz, PESSOA info, short int (*comparar)(DADOS, DADOS))
{
    RUBRO_NEGRO *retorno = NULL;

    DADOS aux;
    aux.pessoa = info;

    retorno = remover_rubro_negro(raiz, aux, comparar);

    return retorno;
}
