#include "../../Includes/Objetos/Estado.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ESTADO *alocar_estado()
{
    ESTADO *estado = (ESTADO *)malloc(sizeof(ESTADO));

    verificar_alocacao(estado);

    estado->nome_estado = NULL;
    estado->nome_capital = NULL;
    estado->quantidade_cidade = 0;
    estado->quantidade_populacao = 0;
    estado->raiz_arvore_cidade = NULL;

    return estado;
}

ESTADO *criar_estado(char *nome_estado, char *nome_capital, short int quantidade_cidade, int quantidade_populacao, void *raiz_arvore_cidade)
{
    ESTADO *estado = alocar_estado();

    estado->nome_estado = nome_estado;
    estado->nome_capital = nome_capital;
    estado->quantidade_cidade = quantidade_cidade;
    estado->quantidade_populacao = quantidade_populacao;
    estado->raiz_arvore_cidade = raiz_arvore_cidade;

    return estado;
}

void imprimir_estado(ESTADO *estado)
{
    if (estado != NULL)
    {
        printf("Nome do Estado: %s\n", estado->nome_estado);
        printf("Nome da Capital: %s\n", estado->nome_capital);
        printf("Quantidade de Cidades: %d\n", estado->quantidade_cidade);
        printf("Quantidade de Populacao: %d\n", estado->quantidade_populacao);
    }
}

void liberar_estado(ESTADO **estado)
{
    if (*estado != NULL)
    {
        free((*estado)->nome_estado);
        free((*estado)->nome_capital);
        // free((*estado)->raiz_arvore_cidade);
        free(*estado);
        *estado = NULL;
    }
}

short int comparar_nome_estado(ESTADO *estado1, ESTADO *estado2)
{
    short int resultado = 0;

    if (estado1 != NULL && estado2 != NULL)
    {
        resultado = strcmp(estado1->nome_estado, estado2->nome_estado);
    }

    return resultado;
}