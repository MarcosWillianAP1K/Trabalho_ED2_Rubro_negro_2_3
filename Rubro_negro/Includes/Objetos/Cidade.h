

#pragma once

typedef struct CIDADE
{
    char *nome;
    int quantidade_populacao;
    void *raiz_arvore_CEPs;
}CIDADE;


CIDADE *alocar_cidade();

CIDADE *criar_cidade(char *nome, int quantidade_populacao, void *raiz_arvore_CEPs);

void imprimir_cidade(CIDADE *cidade);

void liberar_cidade(CIDADE **cidade);

short int comparar_nome_cidades(CIDADE *cidade1, CIDADE *cidade2);
