/*
 * Comando para compilar:
gcc -Wall teste_func_interatividade.c ../Tads/Estruturas/Lista_duplamente.c ../Tads/Estruturas/Rubro_negro.c ../Tads/Estruturas/Dados.c ../Tads/Interatividade/func_interatividade.c ../Tads/Objetos/Estado.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/
 *
 * Para executar:
 * ./a.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/Estruturas/Lista_duplamente.h"
#include "../Includes/Estruturas/2-3.h" // Mudança para 2-3
#include "../Includes/Estruturas/Dados.h"
#include "../Includes/Interatividade/func_interatividade.h"
#include "../Includes/Objetos/Estado.h"
#include "../Includes/Objetos/Cidade.h"
#include "../Includes/Objetos/Pessoa.h"
#include "../Includes/Objetos/CEP.h"
#include "../Includes/Objetos/Data.h"
#include "../Includes/Objetos/CPF.h"
#include "../Includes/Utilitarios/funcao_sistema.h"

// Função para criar estados, cidades e CEPs
LISTA_DUPLAMENTE *povoar_estados()
{
    // Inicializar a lista de estados
    LISTA_DUPLAMENTE *lista_estados = NULL;

    // Criar 40 CEPs com formato "00000-001" até "00000-040" - alterado para ponteiros
    char *ceps[40];
    for (int i = 0; i < 40; i++)
    {
        char temp_cep[10];
        sprintf(temp_cep, "%05d-%03d", 0, i + 1);
        ceps[i] = strdup(temp_cep); // Alocação dinâmica com strdup
        printf("CEP criado: %s\n", ceps[i]);
    }

    // Criar 20 cidades com populações crescentes
    CIDADE cidades[20];
    for (int i = 0; i < 20; i++)
    {
        char nome_cidade[20];
        sprintf(nome_cidade, "cidade%d", i + 1);
        int populacao = (i + 1) * 10; // Começando com 10 e incrementando de 10 em 10
        cidades[i] = criar_cidade(nome_cidade, populacao, NULL);
        printf("Cidade criada: %s, População: %d\n", nome_cidade, populacao);
    }

    // Criar 10 estados, cada um com duas cidades (sendo uma delas a capital)
    for (int i = 0; i < 10; i++)
    {
        char nome_estado[20];
        sprintf(nome_estado, "estado%d", i + 1);

        // A capital é a cidade número (estado * 2)
        int num_capital = (i + 1) * 2;
        char nome_capital[20];
        sprintf(nome_capital, "cidade%d", num_capital);

        // A outra cidade é a próxima cidade após a capital
        int num_outra_cidade = (num_capital % 20) + 1; // Garantir que não ultrapasse 20

        // Criar o estado
        printf("Criando estado: %s com capital: %s\n", nome_estado, nome_capital);
        ESTADO estado = criar_estado(nome_estado, nome_capital,
                                     0,           // número de municípios
                                     (i + 1) * 10, // população
                                     NULL);
    }

    

    return lista_estados;
}

int main()
{
    limpar_tela();
    print_amarelo("=== TESTE DE POVOAMENTO DE ESTADOS ===\n");

    LISTA_DUPLAMENTE *lista_estados = povoar_estados();

    printf("\nLista de estados povoada com sucesso.\n");

    // Aqui pode adicionar código para verificar os elementos povoados

    print_verde("\n=== POVOAMENTO CONCLUIDO COM SUCESSO ===\n");

    return 0;
}
