

#pragma once



void imprimir_CEP(char *cep);

void liberar_CEP(char **cep);

void corrigir_formatacao_CEP(char **cep);

int validar_CEP(char *cep);

char *digitar_CEP();

short int comparar_CEPs(char *cep1, char *cep2);
