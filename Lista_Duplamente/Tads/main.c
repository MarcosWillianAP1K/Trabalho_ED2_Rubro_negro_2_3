#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/main.h"

// Function to create a new node
ESTADOS *criarEstado()
{
    ESTADOS *novo = (ESTADOS *)malloc(sizeof(ESTADOS));
    if (!novo)
    {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    novo->nome = NULL;
    novo->estado = NULL;
    novo->qnt_estados = 0;
    novo->tam_populacao = 0;
    novo->ant = NULL;
    novo->prox = NULL;
    novo->end_vp = NULL;
    return novo;
}

int inserir_estado_recursivo(ESTADOS **r, ESTADOS *novo)
{
    if (!*r || strcmp(novo->nome, (*r)->nome) < 0)
    {
        novo->prox = *r;
        if (*r)
        {
            (*r)->ant = novo;
        }
        *r = novo;
        return 1;
    }
    return inserir_estado_recursivo(&(*r)->prox, novo);
}

int inserir_estado(ESTADOS **r, char *nome)
{
    int resultado = 0;

    if (!r)
    {
        printf("Lista não inicializada.\n");
    }
    else
    {
        ESTADOS *novo = criarEstado();
        if (!novo)
        {
            printf("Erro ao criar novo estado.\n");
        }
        else
        {
            novo->nome = strdup(nome);
            resultado = inserir_estado_recursivo(r, novo);
        }
    }

    return resultado;
}

int comparar_por_nome(char *nome1, char *nome2) {
    return strcmp(nome1, nome2) == 0;
}

int buscar_com_filtro(ESTADOS *r, char *nome, int (*comparar)(char *, char *)) {
    ESTADOS *temp = r;
    int encontrado = 0;
    while (temp) {
        if (comparar(temp->nome, nome)) {
            printf("Estado encontrado: Nome: %s, Estado: %s, Quantidade de Estados: %d\n", temp->nome, temp->estado, temp->qnt_estados);
            encontrado = 1;
            break;
        }
        temp = temp->prox;
    }
    if (!encontrado) {
        printf("Nenhum estado encontrado com o filtro fornecido.\n");
    }
    return encontrado;
}

// Function to remove a node
void removerEstado(ESTADOS **r, char *nome)
{
    if (!*r)
        return;
    ESTADOS *temp = *r;
    while (temp && strcmp(temp->nome, nome) != 0)
    {
        temp = temp->prox;
    }
    if (!temp)
    {
        printf("Estado não encontrado.\n");
        return;
    }
    if (temp->ant)
    {
        temp->ant->prox = temp->prox;
    }
    else
    {
        *r = temp->prox;
    }
    if (temp->prox)
    {
        temp->prox->ant = temp->ant;
    }
    free(temp->nome);
    free(temp->estado);
    free(temp);
}

// Function to display the list
void exibirLista(ESTADOS *r)
{
    ESTADOS *temp = r;
    while (temp)
    {
        printf("Nome: %s, Estado: %s, Quantidade de Estados: %d\n", temp->nome, temp->estado, temp->qnt_estados);
        temp = temp->prox;
    }
}

// Function to free the entire list
void liberarLista(ESTADOS **r)
{
    ESTADOS *temp = *r;
    while (temp)
    {
        ESTADOS *prox = temp->prox;
        free(temp->nome);
        free(temp->estado);
        free(temp);
        temp = prox;
    }
    *r = NULL;
}