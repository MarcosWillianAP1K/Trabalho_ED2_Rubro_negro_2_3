#include "../../Includes/Interatividade/Func_interatividade.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===============DELETE_ALL===============

void delete_cidade_CEP(RUBRO_NEGRO **raiz_cidade)
{
    if (raiz_cidade != NULL && *raiz_cidade != NULL)
    {
        delete_cidade_CEP(&(*raiz_cidade)->esquerda);
        delete_cidade_CEP(&(*raiz_cidade)->direita);
        printf("Liberando arvore rubro-negra de cidades...\n");

        RUBRO_NEGRO *raiz_cep = (*raiz_cidade)->info.cidade.raiz_arvore_CEPs;
        (*raiz_cidade)->info.cidade.raiz_arvore_CEPs = NULL;

        printf("Liberando arvore rubro-negra de CEPs...\n");
        liberar_rubro_negro(&raiz_cep, liberar_dados_CEP);

        liberar_no_rubro_negro(raiz_cidade, liberar_dados_cidade);
    }
}

void delete_estado(LISTA_DUPLAMENTE **lista_estado)
{
    if (lista_estado != NULL && *lista_estado != NULL)
    {
        LISTA_DUPLAMENTE *aux = *lista_estado;
        LISTA_DUPLAMENTE *temp;

        while (aux != NULL)
        {
            printf("Liberando lista de estados...\n");
            temp = aux;
            aux = aux->prox;

            RUBRO_NEGRO *raiz_cidade = temp->estado.raiz_arvore_cidade;
            delete_cidade_CEP(&raiz_cidade);
            temp->estado.raiz_arvore_cidade = NULL;
            liberar_no_duplamente(&temp);
        }
    }
}

void delete_all(LISTA_DUPLAMENTE **lista_estado, RUBRO_NEGRO **raiz_pessoa)
{
    if (lista_estado != NULL && *lista_estado != NULL)
    {
        
        delete_estado(lista_estado);
        *lista_estado = NULL;
    }

    if (raiz_pessoa != NULL && *raiz_pessoa != NULL)
    {
        // Libera a árvore rubro-negra de pessoas
        liberar_rubro_negro(raiz_pessoa, liberar_dados_pessoa);
    }
}

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

short int verificar_se_existe_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep)
{
    short int retorno = 0;

    if (lista_estado != NULL && cep != NULL)
        retorno = percorrer_estado(lista_estado, cep);

    return retorno;
}

short int verificar_se_existe_pessoa_associada_a_um_CEP(RUBRO_NEGRO *raiz_pessoas, char *CEP)
{
    short int retorno = 0;

    if (raiz_pessoas != NULL && CEP != NULL)
    {
        short int valor_comparacao;

        valor_comparacao = comparar_CEPs(raiz_pessoas->info.pessoa.CEP_natal, CEP);

        if (valor_comparacao != 0)
            valor_comparacao = comparar_CEPs(raiz_pessoas->info.pessoa.CEP_atual, CEP);

        if (valor_comparacao != 0)
            retorno = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas->esquerda, CEP);

        if (valor_comparacao != 0 && retorno == 0)
            retorno = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas->direita, CEP);

        if (valor_comparacao == 0)
            retorno = 1;
    }

    return retorno;
}

//===============BUSCAS===============

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

//===============CADASTROS===============

RUBRO_NEGRO *cadastrar_pessoa(RUBRO_NEGRO **raiz, PESSOA info)
{
    RUBRO_NEGRO *retorno = NULL;

    DADOS aux;
    aux.pessoa = info;

    retorno = inserir_rubro_negro(raiz, aux, comparar_dados_CPF_pessoa);

    return retorno;
}

RUBRO_NEGRO *cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep)
{
    RUBRO_NEGRO *retorno = NULL;

    if (cep != NULL && cidade != NULL)
    {
        if (verificar_se_existe_CEP(lista_estado, cep) == 0)
        {
            DADOS aux;
            aux.CEP = cep;
            retorno = inserir_rubro_negro_void(&cidade->raiz_arvore_CEPs, aux, comparar_dados_CEP);
        }
    }

    return retorno;
}

RUBRO_NEGRO *cadastrar_cidade(ESTADO *estado, CIDADE info)
{
    RUBRO_NEGRO *retorno = NULL;

    if (estado != NULL)
    {
        DADOS aux;
        aux.cidade = info;

        retorno = inserir_rubro_negro_void(&estado->raiz_arvore_cidade, aux, comparar_dados_nome_cidade);
    }

    return retorno;
}

LISTA_DUPLAMENTE *cadastrar_estado(LISTA_DUPLAMENTE **lista_estado, ESTADO info)
{
    LISTA_DUPLAMENTE *retorno = NULL;

    retorno = inserir_ordernado_duplamente(lista_estado, info);

    return retorno;
}

//===============REMOÇÕES===============

RUBRO_NEGRO *remover_CEP(CIDADE *cidade, char *cep)
{
    RUBRO_NEGRO *retorno = NULL;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        retorno = remover_rubro_negro_void(&cidade->raiz_arvore_CEPs, aux, comparar_dados_CEP);
    }

    return retorno;
}

RUBRO_NEGRO *remover_pessoa(RUBRO_NEGRO **raiz, PESSOA info)
{
    RUBRO_NEGRO *retorno = NULL;

    DADOS aux;
    aux.pessoa = info;

    retorno = remover_rubro_negro(raiz, aux, comparar_dados_CPF_pessoa);

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

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, RUBRO_NEGRO *raiz_pessoa)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        RUBRO_NEGRO *no_cidade = procurar_cidade_por_CEP(lista, raiz_pessoa->info.pessoa.CEP_atual);

        DADOS aux;
        aux.CEP = raiz_pessoa->info.pessoa.CEP_natal;

        if (no_cidade != NULL && buscar_rubro_negro(no_cidade->info.cidade.raiz_arvore_CEPs, aux, comparar_dados_CEP) == NULL)
            quantidade++;

        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(lista, raiz_pessoa->esquerda);
        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(lista, raiz_pessoa->direita);
    }

    return quantidade;
}

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(RUBRO_NEGRO *raiz_pessoa, CIDADE cidade)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        DADOS cep_natal;
        cep_natal.CEP = raiz_pessoa->info.pessoa.CEP_natal;

        if (buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) != NULL)
        {
            if (comparar_CEPs(cep_natal.CEP, raiz_pessoa->info.pessoa.CEP_atual) != 0)
            {
                DADOS cep_atual;
                cep_atual.CEP = raiz_pessoa->info.pessoa.CEP_atual;

                if (buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) == NULL)
                    quantidade++;
            }
        }

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

        if (buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) != NULL)
        {
            if (comparar_CEPs(cep_atual.CEP, raiz_pessoa->info.pessoa.CEP_natal) != 0)
            {
                DADOS cep_natal;
                cep_natal.CEP = raiz_pessoa->info.pessoa.CEP_natal;

                if (buscar_rubro_negro(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) == NULL)
                    quantidade++;
            }
            
        }

        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->esquerda, cidade);
        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->direita, cidade);
    }

    return quantidade;
}

void mostrar_CEPs(RUBRO_NEGRO *raiz)
{
    if (raiz != NULL)
    {
        mostrar_CEPs(raiz->esquerda);
        imprimir_CEP(raiz->info.CEP);
        mostrar_CEPs(raiz->direita);
    }
}

void mostrar_cidades(RUBRO_NEGRO *raiz)
{
    if (raiz != NULL)
    {
        mostrar_cidades(raiz->esquerda);
        print_amarelo("\n\n=================CIDADE==================\n");
        imprimir_cidade(raiz->info.cidade);

        print_amarelo("\n\n=================CEPS==================\n");
        mostrar_CEPs(raiz->info.cidade.raiz_arvore_CEPs);
        printf("\n\n");
        mostrar_cidades(raiz->direita);
    }
}

void mostrar_estados(LISTA_DUPLAMENTE *lista)
{
    while (lista != NULL)
    {
        print_amarelo("\n==================ESTADO==================\n");
        imprimir_estado(lista->estado);
        printf("\n\n");
        mostrar_cidades(lista->estado.raiz_arvore_cidade);
        lista = lista->prox;
    }
}

void mostrar_pessoas(RUBRO_NEGRO *raiz)
{
    if (raiz != NULL)
    {
        mostrar_pessoas(raiz->esquerda);
        imprimir_pessoa(raiz->info.pessoa);
        printf("\n");
        mostrar_pessoas(raiz->direita);
    }
}

void mostrar_tudo(LISTA_DUPLAMENTE *lista, RUBRO_NEGRO *raiz_pessoa)
{
    if (lista != NULL)
    {
        mostrar_estados(lista);
    }

    printf("\n\n");

    if (raiz_pessoa != NULL)
    {
        print_amarelo("\n=================PESSOAS==================\n\n");
        mostrar_pessoas(raiz_pessoa);
        printf("\n\n");
    }
}
