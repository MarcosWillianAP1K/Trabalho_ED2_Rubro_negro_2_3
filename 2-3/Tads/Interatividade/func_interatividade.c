#include "../../Includes/Interatividade/Func_interatividade.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===============DELETE_ALL===============

void delete_cidade_CEP(AVR_23 **raiz_cidade)
{
    if (raiz_cidade != NULL && *raiz_cidade != NULL)
    {
        delete_cidade_CEP(&(*raiz_cidade)->esq);
        delete_cidade_CEP(&(*raiz_cidade)->cen);
        printf("Liberando arvore rubro-negra de cidades...\n");

        AVR_23 *raiz_cep = (*raiz_cidade)->info1.cidade.raiz_arvore_CEPs;
        (*raiz_cidade)->info1.cidade.raiz_arvore_CEPs = NULL;

        printf("Liberando arvore rubro-negra de CEPs...\n");
        liberar_23(&raiz_cep, liberar_dados_CEP);

        if ((*raiz_cidade)->nInfo == 2)
        {
            raiz_cep = (*raiz_cidade)->info2.cidade.raiz_arvore_CEPs;
            (*raiz_cidade)->info2.cidade.raiz_arvore_CEPs = NULL;

            printf("Liberando arvore rubro-negra de CEPs...\n");
            liberar_23(&raiz_cep, liberar_dados_CEP);

            delete_cidade_CEP(&(*raiz_cidade)->dir);
        }

        liberar_no_23(raiz_cidade, liberar_dados_cidade);
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

            AVR_23 *raiz_cidade = temp->estado.raiz_arvore_cidade;
            delete_cidade_CEP(&raiz_cidade);
            temp->estado.raiz_arvore_cidade = NULL;
            liberar_no_duplamente(&temp);
        }
    }
}

void delete_all(LISTA_DUPLAMENTE **lista_estado, AVR_23 **raiz_pessoa)
{
    if (lista_estado != NULL && *lista_estado != NULL)
    {

        delete_estado(lista_estado);
        *lista_estado = NULL;
    }

    if (raiz_pessoa != NULL && *raiz_pessoa != NULL)
    {
        // Libera a árvore 2-3 de pessoas
        liberar_23(raiz_pessoa, liberar_dados_pessoa);
    }
}

//===============VERIFICAÇÕES===============

short int pecorrer_cidade(AVR_23 *raiz_cidade, char *cep)
{
    short int retorno = 0;

    if (raiz_cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        if (buscar_23(raiz_cidade->info1.cidade.raiz_arvore_CEPs, aux, comparar_dados_CEP) != NULL)
        {
            retorno = 1; // CEP encontrado
        }

        if (retorno == 0 && raiz_cidade->nInfo == 2 && buscar_23(raiz_cidade->info2.cidade.raiz_arvore_CEPs, aux, comparar_dados_CEP) != NULL)
        {
            retorno = 1; // CEP encontrado na segunda informação
        }

        if (retorno == 0)
            retorno = pecorrer_cidade(raiz_cidade->esq, cep);

        if (retorno == 0)
            retorno = pecorrer_cidade(raiz_cidade->cen, cep);

        if (retorno == 0 && raiz_cidade->nInfo == 2)
            retorno = pecorrer_cidade(raiz_cidade->dir, cep);
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

short int verificar_se_existe_pessoa_associada_a_um_CEP(AVR_23 *raiz_pessoas, char *CEP)
{
    short int retorno = 0;

    if (raiz_pessoas != NULL && CEP != NULL)
    {
        short int valor_comparacao;

        valor_comparacao = comparar_CEPs(raiz_pessoas->info1.pessoa.CEP_natal, CEP);

        if (valor_comparacao != 0 && raiz_pessoas->nInfo == 2)
            valor_comparacao = comparar_CEPs(raiz_pessoas->info2.pessoa.CEP_natal, CEP);

        if (valor_comparacao == 0)
            retorno = 1;

        if (retorno == 0)
            retorno = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas->esq, CEP);

        if (retorno == 0)
            retorno = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas->cen, CEP);

        if (retorno == 0 && raiz_pessoas->nInfo == 2)
            retorno = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas->dir, CEP);
    }

    return retorno;
}

//===============BUSCAS===============

CIDADE *procurar_cidade_por_CEP_pecorrer_cidade(AVR_23 *raiz_cidade, DADOS cep)
{
    CIDADE *cidade = NULL;

    if (raiz_cidade != NULL)
    {
        DADOS *procurar_dado = NULL;

        procurar_dado = buscar_23(raiz_cidade->info1.cidade.raiz_arvore_CEPs, cep, comparar_dados_CEP);

        if (procurar_dado != NULL)
            cidade = &(raiz_cidade->info1.cidade);
        else if (raiz_cidade->nInfo == 2)
        {
            procurar_dado = buscar_23(raiz_cidade->info2.cidade.raiz_arvore_CEPs, cep, comparar_dados_CEP);

            if (procurar_dado != NULL)
                cidade = &(raiz_cidade->info2.cidade);
        }

        if (cidade == NULL)
        {
            cidade = procurar_cidade_por_CEP_pecorrer_cidade(raiz_cidade->esq, cep);

            if (cidade == NULL)
                cidade = procurar_cidade_por_CEP_pecorrer_cidade(raiz_cidade->cen, cep);

            if (cidade == NULL && raiz_cidade->nInfo == 2)
                cidade = procurar_cidade_por_CEP_pecorrer_cidade(raiz_cidade->dir, cep);
        }
    }

    return cidade;
}

CIDADE *procurar_cidade_por_CEP(LISTA_DUPLAMENTE *lista_estado, char *cep)
{
    CIDADE *cidade = NULL;

    if (lista_estado != NULL && cep != NULL)
    {
        LISTA_DUPLAMENTE *aux = lista_estado;
        DADOS cep_dados;
        cep_dados.CEP = cep;

        while (aux != NULL && cidade == NULL)
        {
            cidade = procurar_cidade_por_CEP_pecorrer_cidade(aux->estado.raiz_arvore_cidade, cep_dados);

            aux = aux->prox;
        }
    }

    return cidade;
}

//===============CADASTROS===============

short int cadastrar_pessoa(AVR_23 **raiz, PESSOA info)
{
    short int retorno = 0;

    DADOS aux;
    aux.pessoa = info;

    retorno = inserir_23(raiz, aux, comparar_dados_CPF_pessoa);

    return retorno;
}

short int cadastrar_CEP(LISTA_DUPLAMENTE *lista_estado, CIDADE *cidade, char *cep)
{
    short int retorno = 0;

    if (cep != NULL && cidade != NULL)
    {
        if (verificar_se_existe_CEP(lista_estado, cep) == 0)
        {
            DADOS aux;
            aux.CEP = cep;
            retorno = inserir_23_void(&cidade->raiz_arvore_CEPs, aux, comparar_dados_CEP);
        }
    }

    return retorno;
}

short int cadastrar_cidade(ESTADO *estado, CIDADE info)
{
    short int retorno = 0;

    if (estado != NULL)
    {
        DADOS aux;
        aux.cidade = info;

        retorno = inserir_23_void(&estado->raiz_arvore_cidade, aux, comparar_dados_nome_cidade);
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

short int remover_CEP(CIDADE *cidade, char *cep, char *cep_removido)
{
    short int retorno = 0;

    if (cidade != NULL && cep != NULL)
    {
        DADOS aux;
        aux.CEP = cep;

        DADOS dado_removido;

        retorno = remover_23_void(&cidade->raiz_arvore_CEPs, aux, &dado_removido, comparar_dados_CEP);

        if (retorno == 1)
        {
            if (cep_removido != NULL)
            {
                cep_removido = dado_removido.CEP;
            }
        }
    }

    return retorno;
}

short int remover_pessoa(AVR_23 **raiz, PESSOA info, PESSOA *pessoa_removida)
{
    short int retorno = 0;

    DADOS aux;
    aux.pessoa = info;

    DADOS dado_removido;

    retorno = remover_23(raiz, aux, &dado_removido, comparar_dados_CPF_pessoa);

    if (retorno == 1)
    {
        if (pessoa_removida != NULL)
        {
            *pessoa_removida = dado_removido.pessoa;
        }
    }

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

CIDADE *procurar_capital_de_um_estado(ESTADO estado)
{
    CIDADE *retorno = NULL;

    if (estado.raiz_arvore_cidade != NULL)
    {
        DADOS aux;
        aux.cidade = criar_cidade(estado.nome_capital, 0, NULL);

        DADOS *dado_retornado = buscar_23(estado.raiz_arvore_cidade, aux, comparar_dados_nome_cidade);

        if (dado_retornado != NULL)
        {
            retorno = &(dado_retornado->cidade);
        }
    }

    return retorno;
}

CIDADE *procurar_cidade_mais_populosa_sem_capital(AVR_23 *raiz_cidade, char *nome_capital)
{
    CIDADE *retorno = NULL;

    if (raiz_cidade != NULL)
    {
        retorno = procurar_cidade_mais_populosa_sem_capital(raiz_cidade->esq, nome_capital);

        if (retorno == NULL && strcmp(raiz_cidade->info1.cidade.nome, nome_capital) != 0)
            retorno = &raiz_cidade->info1.cidade;

        if (retorno != NULL && strcmp(raiz_cidade->info1.cidade.nome, nome_capital) != 0 && raiz_cidade->info1.cidade.quantidade_populacao > retorno->quantidade_populacao)
            retorno = &raiz_cidade->info1.cidade;

        if (retorno != NULL && raiz_cidade->nInfo == 2 && strcmp(raiz_cidade->info2.cidade.nome, nome_capital) != 0 && raiz_cidade->info2.cidade.quantidade_populacao > retorno->quantidade_populacao)
            retorno = &raiz_cidade->info2.cidade;

        CIDADE *aux = procurar_cidade_mais_populosa_sem_capital(raiz_cidade->cen, nome_capital);

        if (aux != NULL && aux->quantidade_populacao > retorno->quantidade_populacao)
            retorno = aux;

        if (raiz_cidade->nInfo == 2)
        {
            aux = procurar_cidade_mais_populosa_sem_capital(raiz_cidade->dir, nome_capital);

            if (aux != NULL && aux->quantidade_populacao > retorno->quantidade_populacao)
                retorno = aux;
        }
    }

    return retorno;
}

int quant_de_pessoas_que_nao_mora_na_cidade_natal(LISTA_DUPLAMENTE *lista, AVR_23 *raiz_pessoa)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        CIDADE *cidade = procurar_cidade_por_CEP(lista, raiz_pessoa->info1.pessoa.CEP_atual);

        DADOS aux;
        aux.CEP = raiz_pessoa->info1.pessoa.CEP_natal;

        if (cidade != NULL && buscar_23(cidade->raiz_arvore_CEPs, aux, comparar_dados_CEP) == NULL)
            quantidade++;

        if (raiz_pessoa->nInfo == 2)
        {
            cidade = procurar_cidade_por_CEP(lista, raiz_pessoa->info2.pessoa.CEP_atual);

            aux.CEP = raiz_pessoa->info2.pessoa.CEP_natal;

            if (cidade != NULL && buscar_23(cidade->raiz_arvore_CEPs, aux, comparar_dados_CEP) == NULL)
                quantidade++;
        }

        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(lista, raiz_pessoa->esq);
        quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(lista, raiz_pessoa->cen);

        if (raiz_pessoa->nInfo == 2)
            quantidade += quant_de_pessoas_que_nao_mora_na_cidade_natal(lista, raiz_pessoa->dir);
    }

    return quantidade;
}

int quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(AVR_23 *raiz_pessoa, CIDADE cidade)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        DADOS cep_natal;
        cep_natal.CEP = raiz_pessoa->info1.pessoa.CEP_natal;

        if (buscar_23(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) != NULL)
        {
            if (comparar_CEPs(cep_natal.CEP, raiz_pessoa->info1.pessoa.CEP_atual) != 0)
            {
                DADOS cep_atual;
                cep_atual.CEP = raiz_pessoa->info1.pessoa.CEP_atual;

                if (buscar_23(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) == NULL)
                    quantidade++;
            }
        }

        if (raiz_pessoa->nInfo == 2)
        {
            cep_natal.CEP = raiz_pessoa->info2.pessoa.CEP_natal;

            if (buscar_23(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) != NULL)
            {
                if (comparar_CEPs(cep_natal.CEP, raiz_pessoa->info2.pessoa.CEP_atual) != 0)
                {
                    DADOS cep_atual;
                    cep_atual.CEP = raiz_pessoa->info2.pessoa.CEP_atual;

                    if (buscar_23(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) == NULL)
                        quantidade++;
                }
            }
        }

        quantidade += quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(raiz_pessoa->esq, cidade);
        quantidade += quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(raiz_pessoa->cen, cidade);

        if (raiz_pessoa->nInfo == 2)
            quantidade += quant_de_pessoas_nascidas_em_uma_cidade_que_nao_mora_na_cidade_natal(raiz_pessoa->dir, cidade);
    }

    return quantidade;
}

int quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(AVR_23 *raiz_pessoa, CIDADE cidade)
{
    int quantidade = 0;

    if (raiz_pessoa != NULL)
    {
        DADOS cep_atual;
        cep_atual.CEP = raiz_pessoa->info1.pessoa.CEP_atual;

        if (buscar_23(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) != NULL)
        {
            if (comparar_CEPs(cep_atual.CEP, raiz_pessoa->info1.pessoa.CEP_natal) != 0)
            {
                DADOS cep_natal;
                cep_natal.CEP = raiz_pessoa->info1.pessoa.CEP_natal;

                if (buscar_23(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) == NULL)
                    quantidade++;
            }
        }

        if (raiz_pessoa->nInfo == 2)
        {
            cep_atual.CEP = raiz_pessoa->info2.pessoa.CEP_atual;

            if (buscar_23(cidade.raiz_arvore_CEPs, cep_atual, comparar_dados_CEP) != NULL)
            {
                if (comparar_CEPs(cep_atual.CEP, raiz_pessoa->info2.pessoa.CEP_natal) != 0)
                {
                    DADOS cep_natal;
                    cep_natal.CEP = raiz_pessoa->info2.pessoa.CEP_natal;

                    if (buscar_23(cidade.raiz_arvore_CEPs, cep_natal, comparar_dados_CEP) == NULL)
                        quantidade++;
                }
            }
        }

        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->esq, cidade);
        quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->cen, cidade);

        if (raiz_pessoa->nInfo == 2)
            quantidade += quant_de_pessoas_de_uma_cidade_nao_nasceram_na_cidade(raiz_pessoa->dir, cidade);
    }

    return quantidade;
}

// void mostrar_CEPs(AVR_23 *raiz)
// {
//     if (raiz != NULL)
//     {
//         mostrar_CEPs(raiz->esquerda);
//         imprimir_CEP(raiz->info.CEP);
//         mostrar_CEPs(raiz->direita);
//     }
// }

void mostrar_cidades(AVR_23 *raiz)
{
    if (raiz != NULL)
    {
        mostrar_cidades(raiz->esq);
        print_amarelo("\n\n=================CIDADE==================\n");
        imprimir_cidade(raiz->info1.cidade);

        print_amarelo("\n\n=================CEPS==================\n");
        imprimir_23_em_ordem(raiz->info1.cidade.raiz_arvore_CEPs, imprimir_dados_CEP);
        printf("\n\n");
        mostrar_cidades(raiz->cen);

        if (raiz->nInfo == 2)
        {
            print_amarelo("\n\n=================CIDADE==================\n");
            imprimir_cidade(raiz->info2.cidade);

            print_amarelo("\n\n=================CEPS==================\n");
            imprimir_23_em_ordem(raiz->info2.cidade.raiz_arvore_CEPs, imprimir_dados_CEP);
            printf("\n\n");

            mostrar_cidades(raiz->dir);
        }
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

void mostrar_pessoas(AVR_23 *raiz)
{
    if (raiz != NULL)
    {
        // mostrar_pessoas(raiz->esquerda);
        // imprimir_pessoa(raiz->info.pessoa);
        // printf("\n");
        // mostrar_pessoas(raiz->direita);

        imprimir_23_em_ordem(raiz, imprimir_dados_pessoa);
        printf("\n");
    }
}

void mostrar_tudo(LISTA_DUPLAMENTE *lista, AVR_23 *raiz_pessoa)
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
