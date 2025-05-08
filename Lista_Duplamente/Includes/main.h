#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct ESTADOS
{
    char *nome;
    char *estado;
    int qnt_estados;
    float *tam_populacao;
    struct ESTADOS *ant;
    struct ESTADOS *prox;
    void *end_vp;
} ESTADOS;

ESTADOS *criarEstado();
int inserir_estado(ESTADOS **r, char *nome);
int inserir_estado_recursivo(ESTADOS **r, ESTADOS *novo);
int buscar_com_filtro(ESTADOS *r, char *nome, int (*comparar)(char *, char *));
int comparar_por_nome(char *nome1, char *nome2);
void removerEstado(ESTADOS **r, char *nome);
void exibirLista(ESTADOS *r);
void liberarLista(ESTADOS **r);
