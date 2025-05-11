#include "../Objetos/Estado.h"

#pragma once


typedef struct LISTA_DUPLAMENTE
{
    ESTADO *estado;
    struct LISTA_DUPLAMENTE *ant;
    struct LISTA_DUPLAMENTE *prox;
} LISTA_DUPLAMENTE;


LISTA_DUPLAMENTE *alocar_no_duplamente();

void liberar_no_duplamente(LISTA_DUPLAMENTE **raiz);

short int inserir_ordernado_duplamente(LISTA_DUPLAMENTE **raiz, ESTADO *info);

LISTA_DUPLAMENTE *buscar_duplamente(LISTA_DUPLAMENTE *raiz, ESTADO *info);

short int removerEstado(LISTA_DUPLAMENTE **raiz, ESTADO *info);

void exibirLista(LISTA_DUPLAMENTE *raiz);

void liberar_lista(LISTA_DUPLAMENTE **raiz);

