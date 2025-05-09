#include "../Includes/Objetos/Pessoa.h"
#include "../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>


PESSOA *alocar_pessoa()
{
    PESSOA *pessoa = (PESSOA *)malloc(sizeof(PESSOA));

    verificar_alocacao(pessoa);

    pessoa->CPF = NULL;
    pessoa->nome = NULL;
    pessoa->CEP_atual = NULL;
    pessoa->CEP_natal = NULL;
    pessoa->data_nascimento = NULL;
}


PESSOA *criar_pessoa(char *CPF, char *nome, char *CEP_natal, char *CEP_atual, DATA *data_nascimento)
{
    PESSOA *pessoa = alocar_pessoa();

    pessoa->CPF = CPF;
    pessoa->nome = nome;
    pessoa->CEP_natal = CEP_natal;
    pessoa->CEP_atual = CEP_atual;
    pessoa->data_nascimento = data_nascimento;

    return pessoa;
}

void imprimir_pessoa(PESSOA *pessoa)
{
    if (pessoa != NULL)
    {
        printf("CPF: %s\n", pessoa->CPF);
        printf("Nome: %s\n", pessoa->nome);
        printf("CEP Natal: %s\n", pessoa->CEP_natal);
        printf("CEP Atual: %s\n", pessoa->CEP_atual);
        printf("Data Nascimento: %s\n", pessoa->data_nascimento);
    }
}

void liberar_pessoa(PESSOA **pessoa)
{
    if (*pessoa != NULL)
    {
        free((*pessoa)->CPF);
        free((*pessoa)->nome);
        free((*pessoa)->CEP_natal);
        free((*pessoa)->CEP_atual);
        free((*pessoa)->data_nascimento);
        free(*pessoa);
        *pessoa = NULL;
    }
}