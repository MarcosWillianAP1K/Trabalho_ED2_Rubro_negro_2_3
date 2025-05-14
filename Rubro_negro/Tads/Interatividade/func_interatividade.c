#include "../../Includes/Interatividade/Func_interatividade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===============VERIFICAÇÕES===============

short int pecorrer_cidade(RUBRO_NEGRO *raiz_cidade, char *cep)
{
    short int retorno = 0;

    if (raiz_cidade)
    {
        DADOS aux;
        aux.CEP = cep;

        if (buscar_rubro_negro(raiz_cidade->info.cidade.raiz_arvore_CEPs, aux, comparar_dados_CEP) == NULL)
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

short int percorrer_estado(LISTA_DUPLAMENTE *raiz_estado, char *cep)
{
    short int retorno = 0;

    if (raiz_estado != NULL)
    {
        retorno = pecorrer_cidade(raiz_estado->estado.raiz_arvore_cidade, cep);

        if (retorno == 0)
            retorno = percorrer_estado(raiz_estado->prox, cep);
    }

    return retorno;
}

short int verificar_se_ja_existe_CEP(LISTA_DUPLAMENTE *raiz_estado, char *cep)
{
    short int retorno = 0;

    if (raiz_estado != NULL && cep != NULL)
        retorno = percorrer_estado(raiz_estado, cep);

    return retorno;
}

//===============CADASTROS===============

short int cadastrar_estado(LISTA_DUPLAMENTE **raiz_estado, ESTADO info)
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

short int cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE cidade, char *cep, short int (*comparar)(DADOS , DADOS ))
{
    short int retorno = 0;

    if (cep != NULL)
    {

        if (verificar_se_ja_existe_CEP(lista_estado, cep) == 0)
        {
            DADOS aux;
            aux.CEP = cep;

            retorno = inserir_rubro_negro_void(&cidade.raiz_arvore_CEPs, aux, comparar);
        }
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

//===============REMOÇÕES===============

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep, short int (*comparar)(DADOS, DADOS))
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

//===============MOSTRAR e PROCURAR===============

LISTA_DUPLAMENTE *procurar_estado_mais_populoso(LISTA_DUPLAMENTE *lista_estado)
{
    LISTA_DUPLAMENTE *retorno = NULL;

    if (lista_estado != NULL)
    {
        retorno = lista_estado;
        lista_estado = lista_estado->prox;

        while (lista_estado != NULL)
        {
            if (lista_estado->estado.quantidade_populacao > retorno->estado.quantidade_populacao)
                retorno = lista_estado;

            lista_estado = lista_estado->prox;
        }
    }

    return retorno;
}

RUBRO_NEGRO *procurar_capital_de_um_estado(ESTADO estado)
{
    RUBRO_NEGRO *retorno = NULL;

    if (estado.raiz_arvore_cidade != NULL)
    {
        DADOS aux;
        aux.cidade = criar_cidade(estado.nome_capital, 0, NULL);

        retorno = buscar_rubro_negro(estado.raiz_arvore_cidade, aux, comparar_dados_nome_cidade);
    }

    return retorno;
}

RUBRO_NEGRO *procurar_cidade_mais_populosa_sem_capital(RUBRO_NEGRO *raiz_cidade, char *nome_capital)
{
    RUBRO_NEGRO *retorno = NULL;

    if (raiz_cidade != NULL)
    {
        retorno = procurar_cidade_mais_populosa_sem_capital(raiz_cidade->esquerda, nome_capital);

        if (retorno == NULL && strcmp(raiz_cidade->info.cidade.nome, nome_capital) != 0)
            retorno = raiz_cidade;

        if (retorno != NULL && strcmp(raiz_cidade->info.cidade.nome, nome_capital) != 0 && raiz_cidade->info.cidade.quantidade_populacao > retorno->info.cidade.quantidade_populacao)
            retorno = raiz_cidade;

        RUBRO_NEGRO *aux = procurar_cidade_mais_populosa_sem_capital(raiz_cidade->direita, nome_capital);

        if (aux != NULL && aux->info.cidade.quantidade_populacao > retorno->info.cidade.quantidade_populacao)
            retorno = aux;
    }

    return retorno;
}

int quant_de_pessoas_que_nao_mora_na_cidade_natal(RUBRO_NEGRO *raiz_pessoa)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        if (comparar_CEPs(raiz_pessoa->info.pessoa.CEP_atual, raiz_pessoa->info.pessoa.CEP_natal) == 0)
            quantidade++;

        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(raiz_pessoa->esquerda);
        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(raiz_pessoa->direita);
    }

    return quantidade;
}

RUBRO_NEGRO *procurar_cidade_por_CEP_pecorrer_cidade(RUBRO_NEGRO *raiz_cidade, DADOS cep)
{
    RUBRO_NEGRO *retorno = NULL;

    if (raiz_cidade != NULL)
    {
        if (buscar_rubro_negro(raiz_cidade->info.cidade.raiz_arvore_CEPs, cep, comparar_dados_CEP) != NULL)
            retorno = raiz_cidade;

        if (retorno == NULL)
            retorno = procurar_cidade_por_CEP_pecorrer_cidade(raiz_cidade->esquerda, cep);

        if (retorno == NULL)
            retorno = procurar_cidade_por_CEP_pecorrer_cidade(raiz_cidade->direita, cep);
    }

    return retorno;
}

RUBRO_NEGRO *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep)
{
    RUBRO_NEGRO *no_cidade = NULL;

    if (lista_estado != NULL && cep != NULL)
    {
        LISTA_DUPLAMENTE *aux = lista_estado;
        DADOS cep_dados;
        cep_dados.CEP = cep;

        while (aux != NULL && no_cidade == NULL)
        {
            no_cidade = procurar_cidade_por_CEP_pecorrer_cidade(aux->estado.raiz_arvore_cidade, cep_dados);

            aux = aux->prox;
        }
    }

    return no_cidade;
}

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(RUBRO_NEGRO *raiz_pessoa, CIDADE cidade)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        DADOS cep_natal;
        cep_natal.CEP = raiz_pessoa->info.pessoa.CEP_natal;

        if (comparar_CEPs(cep_natal.CEP, raiz_pessoa->info.pessoa.CEP_atual) != 0 && buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) != NULL)
            quantidade++;

        quantidade += quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(raiz_pessoa->esquerda, cidade);
        quantidade += quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(raiz_pessoa->direita, cidade);
    }

    return quantidade;
}

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(RUBRO_NEGRO *raiz_pessoa, CIDADE cidade)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        DADOS cep_atual;
        cep_atual.CEP = raiz_pessoa->info.pessoa.CEP_atual;

        if (comparar_CEPs(cep_atual.CEP, raiz_pessoa->info.pessoa.CEP_natal) != 0 && buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) != NULL)
            quantidade++;

        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->esquerda, cidade);
        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->direita, cidade);
    }

    return quantidade;
}
