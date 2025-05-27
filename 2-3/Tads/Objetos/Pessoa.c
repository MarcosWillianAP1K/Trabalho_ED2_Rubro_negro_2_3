#include "../../Includes/Objetos/Pessoa.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// PESSOA *alocar_pessoa()
// {
//     PESSOA *pessoa = (PESSOA *)malloc(sizeof(PESSOA));

//     verificar_alocacao(pessoa);

//     pessoa->CPF = NULL;
//     pessoa->nome = NULL;
//     pessoa->CEP_atual = NULL;
//     pessoa->CEP_natal = NULL;
//     pessoa->data_nascimento = NULL;

//     return pessoa;
// }


PESSOA criar_pessoa(char *CPF, char *nome, char *CEP_natal, char *CEP_atual, DATA data_nascimento)
{
    PESSOA pessoa;

    pessoa.CPF = CPF;
    pessoa.nome = nome;
    pessoa.CEP_natal = CEP_natal;
    pessoa.CEP_atual = CEP_atual;
    pessoa.data_nascimento = data_nascimento;

    return pessoa;
}

void imprimir_pessoa(PESSOA pessoa)
{
   
        printf("CPF: %s\n", pessoa.CPF);
        printf("Nome: %s\n", pessoa.nome);
        printf("CEP Natal: %s\n", pessoa.CEP_natal);
        printf("CEP Atual: %s\n", pessoa.CEP_atual);
        imprimir_data(pessoa.data_nascimento);
    
}

void liberar_pessoa(PESSOA *pessoa)
{
    if (pessoa != NULL)
    {
        free(pessoa->CPF);
        free(pessoa->nome);
        free(pessoa->CEP_natal);
        free(pessoa->CEP_atual);
    }
}

short int comparar_nome_pessoas(PESSOA pessoa1, PESSOA pessoa2)
{
    short int resultado = 0;

    if (pessoa1.nome != NULL && pessoa2.nome != NULL)
      resultado = strcmp(pessoa1.nome, pessoa2.nome);
    else if (pessoa1.nome == NULL && pessoa2.nome != NULL)
           resultado = -1;
    else if (pessoa1.nome != NULL && pessoa2.nome == NULL)
           resultado = 1;
    return resultado;
}

short int comparar_CPF_pessoas(PESSOA pessoa1, PESSOA pessoa2)
{
    short int resultado = 0;

    if (pessoa1.CPF != NULL && pessoa2.CPF != NULL)
      resultado = strcmp(pessoa1.CPF, pessoa2.CPF);
    else if (pessoa1.CPF == NULL && pessoa2.CPF != NULL)
           resultado = -1;
    else if (pessoa1.CPF != NULL && pessoa2.CPF == NULL)
           resultado = 1;

    return resultado;
}