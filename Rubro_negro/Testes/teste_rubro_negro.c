/*
Instruções para compilação:

Para compilar este arquivo de teste, execute o seguinte comando no terminal:

gcc teste_rubro_negro.c ../Tads/Estruturas/Rubro_negro.c ../Tads/Estruturas/Dados.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/

Para executar o programa após compilação:
./a.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/Estruturas/Rubro_negro.h"
#include "../Includes/Estruturas/Dados.h"
#include "../Includes/Objetos/Cidade.h"
#include "../Includes/Objetos/Pessoa.h"
#include "../Includes/Objetos/CEP.h"
#include "../Includes/Objetos/Data.h"
#include "../Includes/Objetos/CPF.h"
#include "../Includes/Utilitarios/funcao_sistema.h"

// Comparison functions for each data type
short int comparar_cidades(DADOS *a, DADOS *b) {
    return strcmp(a->cidade->nome, b->cidade->nome);
}

short int comparar_pessoas(DADOS *a, DADOS *b) {
    return strcmp(a->pessoa->CPF, b->pessoa->CPF);
}

short int comparar_ceps(DADOS *a, DADOS *b) {
    return strcmp(a->CEP, b->CEP);
}

// Test function for city insertions
void testar_insercao_cidades(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de cidades...\n");
    
    // Create test data for cities
    DADOS *dado1 = (DADOS*)malloc(sizeof(DADOS));
    dado1->cidade = criar_cidade("Sao Paulo", 12000000, NULL);
    
    DADOS *dado2 = (DADOS*)malloc(sizeof(DADOS));
    dado2->cidade = criar_cidade("Rio de Janeiro", 6700000, NULL);
    
    DADOS *dado3 = (DADOS*)malloc(sizeof(DADOS));
    dado3->cidade = criar_cidade("Belo Horizonte", 2500000, NULL);
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_cidades))
        mensagem_sucesso("Cidade Sao Paulo inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Sao Paulo!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_cidades))
        mensagem_sucesso("Cidade Rio de Janeiro inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Rio de Janeiro!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_cidades))
        mensagem_sucesso("Cidade Belo Horizonte inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Belo Horizonte!\n");
}

// Test function for person insertions
void testar_insercao_pessoas(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de pessoas...\n");
    
    // Create test data for people
    DADOS *dado1 = (DADOS*)malloc(sizeof(DADOS));
    dado1->pessoa = alocar_pessoa();
    dado1->pessoa->CPF = strdup("123.456.789-00");
    dado1->pessoa->nome = strdup("Joao Silva");
    dado1->pessoa->CEP_natal = strdup("01001-000");
    dado1->pessoa->CEP_atual = strdup("02002-000");
    dado1->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado1->pessoa->data_nascimento->dia = 1;
    dado1->pessoa->data_nascimento->mes = 1;
    dado1->pessoa->data_nascimento->ano = 1990;
    
    DADOS *dado2 = (DADOS*)malloc(sizeof(DADOS));
    dado2->pessoa = alocar_pessoa();
    dado2->pessoa->CPF = strdup("987.654.321-00");
    dado2->pessoa->nome = strdup("Maria Santos");
    dado2->pessoa->CEP_natal = strdup("03003-000");
    dado2->pessoa->CEP_atual = strdup("04004-000");
    dado2->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado2->pessoa->data_nascimento->dia = 15;
    dado2->pessoa->data_nascimento->mes = 5;
    dado2->pessoa->data_nascimento->ano = 1985;
    
    DADOS *dado3 = (DADOS*)malloc(sizeof(DADOS));
    dado3->pessoa = alocar_pessoa();
    dado3->pessoa->CPF = strdup("111.222.333-44");
    dado3->pessoa->nome = strdup("Pedro Oliveira");
    dado3->pessoa->CEP_natal = strdup("05005-000");
    dado3->pessoa->CEP_atual = strdup("06006-000");
    dado3->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado3->pessoa->data_nascimento->dia = 30;
    dado3->pessoa->data_nascimento->mes = 10;
    dado3->pessoa->data_nascimento->ano = 1995;
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_pessoas))
        mensagem_sucesso("Pessoa Joao Silva inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Joao Silva!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_pessoas))
        mensagem_sucesso("Pessoa Maria Santos inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Maria Santos!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_pessoas))
        mensagem_sucesso("Pessoa Pedro Oliveira inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Pedro Oliveira!\n");
}

// Test function for CEP insertions
void testar_insercao_ceps(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de CEPs...\n");
    
    // Create test data for CEPs
    DADOS *dado1 = (DADOS*)malloc(sizeof(DADOS));
    dado1->CEP = strdup("01001-000");
    
    DADOS *dado2 = (DADOS*)malloc(sizeof(DADOS));
    dado2->CEP = strdup("02002-000");
    
    DADOS *dado3 = (DADOS*)malloc(sizeof(DADOS));
    dado3->CEP = strdup("03003-000");
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_ceps))
        mensagem_sucesso("CEP 01001-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 01001-000!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_ceps))
        mensagem_sucesso("CEP 02002-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 02002-000!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_ceps))
        mensagem_sucesso("CEP 03003-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 03003-000!\n");
}

int main() {
    // Test with cities
    RUBRO_NEGRO *arvore_cidades = NULL;
    print_amarelo("=== TESTE COM CIDADES ===\n");
    testar_insercao_cidades(&arvore_cidades);
    
    print_amarelo("Liberando arvore de cidades...\n");
    liberar_rubro_negro(&arvore_cidades, liberar_dados_cidade);
    if(arvore_cidades == NULL)
        mensagem_sucesso("Arvore de cidades liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar arvore de cidades!\n");
    
    // Test with people
    RUBRO_NEGRO *arvore_pessoas = NULL;
    print_amarelo("\n=== TESTE COM PESSOAS ===\n");
    testar_insercao_pessoas(&arvore_pessoas);
    
    print_amarelo("Liberando arvore de pessoas...\n");
    liberar_rubro_negro(&arvore_pessoas, liberar_dados_pessoa);
    if(arvore_pessoas == NULL)
        mensagem_sucesso("Arvore de pessoas liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar arvore de pessoas!\n");
    
    // Test with CEPs
    RUBRO_NEGRO *arvore_ceps = NULL;
    print_amarelo("\n=== TESTE COM CEPs ===\n");
    testar_insercao_ceps(&arvore_ceps);
    
    print_amarelo("Liberando arvore de CEPs...\n");
    liberar_rubro_negro(&arvore_ceps, liberar_dados_CEP);
    if(arvore_ceps == NULL)
        mensagem_sucesso("Arvore de CEPs liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar arvore de CEPs!\n");
    
    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");
    
    return 0;
}
