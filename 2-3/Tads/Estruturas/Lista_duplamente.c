#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Includes/Estruturas/Lista_duplamente.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"

// Function to create a new node
LISTA_DUPLAMENTE *alocar_no_duplamente()
{
    LISTA_DUPLAMENTE *novo = (LISTA_DUPLAMENTE *)malloc(sizeof(LISTA_DUPLAMENTE));

    verificar_alocacao(novo);
    
    novo->ant = NULL;
    novo->prox = NULL;

    return novo;
}

void liberar_no_duplamente(LISTA_DUPLAMENTE **raiz)
{
    if (raiz != NULL && *raiz != NULL)
    {
        LISTA_DUPLAMENTE *temp = *raiz;
        *raiz = (*raiz)->prox;
        liberar_estado(&temp->estado);
        free(temp);
    }
}

void liberar_lista(LISTA_DUPLAMENTE **raiz)
{
    LISTA_DUPLAMENTE *temp = *raiz;
    LISTA_DUPLAMENTE *proximo;

    while (temp != NULL)
    {
        proximo = temp->prox;
        liberar_no_duplamente(&temp);
        temp = proximo;
    }

    *raiz = NULL;
}

LISTA_DUPLAMENTE *inserir_ordernado_duplamente(LISTA_DUPLAMENTE **raiz, ESTADO info)
{

    LISTA_DUPLAMENTE *retorno = NULL;

    if (raiz != NULL)
    {
        if (*raiz == NULL)
        {
            LISTA_DUPLAMENTE *novo = alocar_no_duplamente();
            if (novo != NULL)
            {
                novo->estado = info;
                *raiz = novo;
                retorno = novo;
            }
        }
        else
        {
            LISTA_DUPLAMENTE *temp = *raiz;
            short int comparar_estado = comparar_nome_estado(temp->estado, info);

            while (temp->prox != NULL && comparar_estado < 0 && comparar_estado != 0)
            {
                temp = temp->prox;
                comparar_estado = comparar_nome_estado(temp->estado, info);
            }

            if (comparar_estado != 0)
            {
                LISTA_DUPLAMENTE *novo = alocar_no_duplamente();
                novo->estado = info;

                if (comparar_estado < 0)
                {
                    novo->prox = temp->prox;
                    novo->ant = temp;
                    temp->prox = novo;
                    if (novo->prox != NULL)
                    {
                        novo->prox->ant = novo;
                    }
                }
                else
                {
                    novo->prox = temp;
                    novo->ant = temp->ant;
                    if (temp->ant != NULL)
                      temp->ant->prox = novo;
                    else
                    {
                        *raiz = novo; // Atualiza a raiz se o novo nó for o primeiro
                    }
                    temp->ant = novo;
                }

                retorno = novo;
            }
        }
    }

    return retorno;
}

LISTA_DUPLAMENTE *buscar_duplamente(LISTA_DUPLAMENTE *raiz, ESTADO info)
{
    int comparacao = 0;
    LISTA_DUPLAMENTE *temp = NULL;

    while (raiz != NULL && comparacao == 0)
    {
        if (comparar_nome_estado(raiz->estado, info) == 0)
        {
            temp = raiz;
           comparacao = 1;
        }
        raiz = raiz->prox;
    }
    return temp;
}

// Function to remove a node
LISTA_DUPLAMENTE *remover_duplamente(LISTA_DUPLAMENTE **raiz, ESTADO info)
{
    LISTA_DUPLAMENTE *retorno = NULL;

    if (raiz != NULL && *raiz != NULL)
    {
        LISTA_DUPLAMENTE *temp = *raiz;

        while (temp != NULL && comparar_nome_estado(temp->estado, info) != 0)
        {
            temp = temp->prox;
        }

        if (temp != NULL)
        {
            if (temp->ant != NULL)
              temp->ant->prox = temp->prox;
            else
                *raiz = temp->prox;

            if (temp->prox != NULL)
              temp->prox->ant = temp->ant;
        

            retorno = temp;
        }
    }

    return retorno;
}

// Function to display the list
void exibirLista(LISTA_DUPLAMENTE *raiz)
{
    while (raiz != NULL)
    {
        imprimir_estado(raiz->estado);
        raiz = raiz->prox;
    }
}
