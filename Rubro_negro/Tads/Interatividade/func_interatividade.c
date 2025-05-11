#include "../../Includes/Interatividade/func_interatividade.h"
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
        DADOS *aux = alocar_dados();
        aux->cidade = info;

        retorno = inserir_rubro_negro_void(&estado->raiz_arvore_cidade, aux, comparar);

        if (retorno == 0)
        {
            //Não libera o cidade
            liberar_dados(&aux);
        }
    }

    return retorno;

}

short int cadastrar_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS *, DADOS *))
{
    short int retorno = 0;

    if (cidade != NULL && cep != NULL)
    {
        DADOS *aux = alocar_dados(cep);
        aux->CEP = cep;

        retorno = inserir_rubro_negro_void(&cidade->raiz_arvore_CEPs, aux, comparar);

        if (retorno == 0)
        {
            //Não libera o char
            liberar_dados(&aux);
        }
    }

    return retorno;
}


short int cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA *info, short int (*comparar)(DADOS *, DADOS *))
{
    return inserir_rubro_negro(raiz, info, comparar);
}