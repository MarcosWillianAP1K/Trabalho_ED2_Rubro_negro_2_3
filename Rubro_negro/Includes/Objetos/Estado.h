

#pragma once


typedef struct ESTADO
{
    char *nome_estado;
    char *nome_capital;
    short int quantidade_cidade;
    int quantidade_populacao;
    void *raiz_arvore_cidade; 
}ESTADO;


// ESTADO *alocar_estado();

ESTADO criar_estado(char *nome_estado, char *nome_capital, short int quantidade_cidade, int quantidade_populacao, void *raiz_arvore_cidade);

void imprimir_estado(ESTADO *estado);

void liberar_estado(ESTADO *estado);

short int comparar_nome_estado(ESTADO *estado1, ESTADO *estado2);


