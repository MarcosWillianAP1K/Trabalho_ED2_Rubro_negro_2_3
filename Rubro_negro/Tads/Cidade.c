#include "../Includes/Cidade.h"
#include "../Includes/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>

CIDADE *alocar_cidade()
{
    CIDADE *cidade = (CIDADE *)malloc(sizeof(CIDADE));

    verificar_alocacao(cidade);

    cidade->nome = NULL;
    cidade->quantidade_populacao = 0;
    cidade->raiz_arvore_CEPs = NULL;

    return cidade;
}

CIDADE *criar_cidade(char *nome, int quantidade_populacao, void *raiz_arvore_CEPs)
{
    CIDADE *cidade = alocar_cidade();

    cidade->nome = nome;
    cidade->quantidade_populacao = quantidade_populacao;
    cidade->raiz_arvore_CEPs = raiz_arvore_CEPs;

    return cidade;
}

void imprimir_cidade(CIDADE *cidade)
{
    if (cidade != NULL)
    {
        printf("Nome da Cidade: %s\n", cidade->nome);
        printf("Quantidade de População: %d\n", cidade->quantidade_populacao);
    }
}

void liberar_cidade(CIDADE **cidade)
{
    if (*cidade != NULL)
    {
        free((*cidade)->nome);
        // free((*cidade)->raiz_arvore_CEPs);
        free(*cidade);
        *cidade = NULL;
    }
}