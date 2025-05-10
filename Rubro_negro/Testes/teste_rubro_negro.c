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

// Removendo as funções de comparação anteriores e usando as fornecidas pelo Dados.h

// Test function for city insertions
void testar_insercao_cidades(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de cidades...\n");
    
    // Create test data for cities
    DADOS *dado1 = alocar_dados();
    dado1->cidade = criar_cidade("Sao Paulo", 12000000, NULL);
    mensagem_sucesso("Dados para Sao Paulo criados com sucesso!\n");
    
    DADOS *dado2 = alocar_dados();
    dado2->cidade = criar_cidade("Rio de Janeiro", 6700000, NULL);
    mensagem_sucesso("Dados para Rio de Janeiro criados com sucesso!\n");
    
    DADOS *dado3 = alocar_dados();
    dado3->cidade = criar_cidade("Belo Horizonte", 2500000, NULL);
    mensagem_sucesso("Dados para Belo Horizonte criados com sucesso!\n");
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_dados_nome_cidade))
        mensagem_sucesso("Cidade Sao Paulo inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Sao Paulo!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_dados_nome_cidade))
        mensagem_sucesso("Cidade Rio de Janeiro inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Rio de Janeiro!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_dados_nome_cidade))
        mensagem_sucesso("Cidade Belo Horizonte inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Belo Horizonte!\n");
}

// Test function for printing and searching in the city tree
void testar_impressao_e_busca_cidades(RUBRO_NEGRO *arvore) {
    print_verde("\nTestando impressao e busca de cidades...\n");
    
    // Test printing entire tree
    print_amarelo("Imprimindo todas as cidades:\n");
    imprimir_rubro_negro(arvore, imprimir_dados_cidade);
    
    // Test filtered printing
    print_amarelo("\nImprimindo cidades com filtro (começando com 'S'):\n");
    DADOS *filtro = alocar_dados();
    filtro->cidade = criar_cidade("S", 0, NULL);
    mensagem_sucesso("Filtro para cidades criado com sucesso!\n");
    
    imprimir_filtro_rubro_negro(arvore, filtro, imprimir_dados_cidade, comparar_dados_nome_cidade);
    
    // Test searching
    print_amarelo("\nBuscando cidade 'Rio de Janeiro':\n");
    DADOS *busca = alocar_dados();
    busca->cidade = criar_cidade("Rio de Janeiro", 0, NULL);
    mensagem_sucesso("Dado para busca de cidade criado com sucesso!\n");
    
    RUBRO_NEGRO *resultado = buscar_rubro_negro(arvore, busca, comparar_dados_nome_cidade);
    if (resultado != NULL) {
        mensagem_sucesso("Cidade encontrada:\n");
        imprimir_dados_cidade(resultado->info);
    } else {
        mensagem_erro("Cidade nao encontrada!\n");
    }
    
    // Free memory after search
    liberar_dados_cidade(&busca);
    mensagem_sucesso("Memoria para busca de 'Rio de Janeiro' liberada!\n");
    
    // Test searching for non-existent city
    print_amarelo("\nBuscando cidade inexistente 'Brasilia':\n");
    busca = alocar_dados();
    busca->cidade = criar_cidade("Brasilia", 0, NULL);
    
    resultado = buscar_rubro_negro(arvore, busca, comparar_dados_nome_cidade);
    if (resultado != NULL) {
        mensagem_sucesso("Cidade encontrada:\n");
        imprimir_dados_cidade(resultado->info);
    } else {
        mensagem_erro("Cidade nao encontrada!\n");
    }
    
    // Free memory after search
    liberar_dados_cidade(&busca);
    mensagem_sucesso("Memoria para busca de 'Brasilia' liberada!\n");
    
    // Only clean up filter at the end
    liberar_dados_cidade(&filtro);
}

// Test function for person insertions
void testar_insercao_pessoas(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de pessoas...\n");
    
    // Create test data for people
    DADOS *dado1 = alocar_dados();
    dado1->pessoa = alocar_pessoa();
    dado1->pessoa->CPF = strdup("123.456.789-00");
    dado1->pessoa->nome = strdup("Joao Silva");
    dado1->pessoa->CEP_natal = strdup("01001-000");
    dado1->pessoa->CEP_atual = strdup("02002-000");
    dado1->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado1->pessoa->data_nascimento->dia = 1;
    dado1->pessoa->data_nascimento->mes = 1;
    dado1->pessoa->data_nascimento->ano = 1990;
    mensagem_sucesso("Dados para Joao Silva criados com sucesso!\n");
    
    DADOS *dado2 = alocar_dados();
    dado2->pessoa = alocar_pessoa();
    dado2->pessoa->CPF = strdup("987.654.321-00");
    dado2->pessoa->nome = strdup("Maria Santos");
    dado2->pessoa->CEP_natal = strdup("03003-000");
    dado2->pessoa->CEP_atual = strdup("04004-000");
    dado2->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado2->pessoa->data_nascimento->dia = 15;
    dado2->pessoa->data_nascimento->mes = 5;
    dado2->pessoa->data_nascimento->ano = 1985;
    mensagem_sucesso("Dados para Maria Santos criados com sucesso!\n");
    
    DADOS *dado3 = alocar_dados();
    dado3->pessoa = alocar_pessoa();
    dado3->pessoa->CPF = strdup("111.222.333-44");
    dado3->pessoa->nome = strdup("Pedro Oliveira");
    dado3->pessoa->CEP_natal = strdup("05005-000");
    dado3->pessoa->CEP_atual = strdup("06006-000");
    dado3->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    dado3->pessoa->data_nascimento->dia = 30;
    dado3->pessoa->data_nascimento->mes = 10;
    dado3->pessoa->data_nascimento->ano = 1995;
    mensagem_sucesso("Dados para Pedro Oliveira criados com sucesso!\n");
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_dados_nome_pessoa))
        mensagem_sucesso("Pessoa Joao Silva inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Joao Silva!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_dados_nome_pessoa))
        mensagem_sucesso("Pessoa Maria Santos inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Maria Santos!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_dados_nome_pessoa))
        mensagem_sucesso("Pessoa Pedro Oliveira inserida com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Pedro Oliveira!\n");
}

// Test function for printing and searching in the person tree
void testar_impressao_e_busca_pessoas(RUBRO_NEGRO *arvore) {
    print_verde("\nTestando impressao e busca de pessoas...\n");
    
    // Test printing entire tree
    print_amarelo("Imprimindo todas as pessoas:\n");
    imprimir_rubro_negro(arvore, imprimir_dados_pessoa);
    
    // Test filtered printing (by CPF starting with '1')
    print_amarelo("\nImprimindo pessoas com filtro (CPF começando com '1'):\n");
    DADOS *filtro = alocar_dados();
    filtro->pessoa = alocar_pessoa();
    filtro->pessoa->CPF = strdup("1");
    filtro->pessoa->nome = strdup("");
    filtro->pessoa->CEP_natal = strdup("");
    filtro->pessoa->CEP_atual = strdup("");
    filtro->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    filtro->pessoa->data_nascimento->dia = 0;
    filtro->pessoa->data_nascimento->mes = 0;
    filtro->pessoa->data_nascimento->ano = 0;
    mensagem_sucesso("Filtro para pessoas criado com sucesso!\n");
    
    imprimir_filtro_rubro_negro(arvore, filtro, imprimir_dados_pessoa, comparar_dados_nome_pessoa);
    
    // Test searching for existing person
    print_amarelo("\nBuscando pessoa com CPF '987.654.321-00':\n");
    DADOS *busca = alocar_dados();
    busca->pessoa = alocar_pessoa();
    busca->pessoa->CPF = strdup("987.654.321-00");
    busca->pessoa->nome = strdup("");
    busca->pessoa->CEP_natal = strdup("");
    busca->pessoa->CEP_atual = strdup("");
    busca->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    busca->pessoa->data_nascimento->dia = 0;
    busca->pessoa->data_nascimento->mes = 0;
    busca->pessoa->data_nascimento->ano = 0;
    mensagem_sucesso("Dado para busca de pessoa criado com sucesso!\n");
    
    RUBRO_NEGRO *resultado = buscar_rubro_negro(arvore, busca, comparar_dados_nome_pessoa);
    if (resultado != NULL) {
        mensagem_sucesso("Pessoa encontrada:\n");
        imprimir_dados_pessoa(resultado->info);
    } else {
        mensagem_erro("Pessoa nao encontrada!\n");
    }
    
    // Free memory after search
    liberar_dados_pessoa(&busca);
    mensagem_sucesso("Memoria para busca de CPF '987.654.321-00' liberada!\n");
    
    // Test searching for non-existent person
    print_amarelo("\nBuscando pessoa inexistente com CPF '000.000.000-00':\n");
    busca = alocar_dados();
    busca->pessoa = alocar_pessoa();
    busca->pessoa->CPF = strdup("000.000.000-00");
    busca->pessoa->nome = strdup("");
    busca->pessoa->CEP_natal = strdup("");
    busca->pessoa->CEP_atual = strdup("");
    busca->pessoa->data_nascimento = (DATA*)malloc(sizeof(DATA));
    busca->pessoa->data_nascimento->dia = 0;
    busca->pessoa->data_nascimento->mes = 0;
    busca->pessoa->data_nascimento->ano = 0;
    
    resultado = buscar_rubro_negro(arvore, busca, comparar_dados_nome_pessoa);
    if (resultado != NULL) {
        mensagem_sucesso("Pessoa encontrada:\n");
        imprimir_dados_pessoa(resultado->info);
    } else {
        mensagem_erro("Pessoa nao encontrada!\n");
    }
    
    // Free memory after search
    liberar_dados_pessoa(&busca);
    mensagem_sucesso("Memoria para busca de CPF '000.000.000-00' liberada!\n");
    
    // Only clean up filter at the end
    liberar_dados_pessoa(&filtro);
}

// Test function for CEP insertions
void testar_insercao_ceps(RUBRO_NEGRO **arvore) {
    print_verde("Testando insercao de CEPs...\n");
    
    // Create test data for CEPs
    DADOS *dado1 = alocar_dados();
    dado1->CEP = strdup("01001-000");
    mensagem_sucesso("Dados para CEP 01001-000 criados com sucesso!\n");
    
    DADOS *dado2 = alocar_dados();
    dado2->CEP = strdup("02002-000");
    mensagem_sucesso("Dados para CEP 02002-000 criados com sucesso!\n");
    
    DADOS *dado3 = alocar_dados();
    dado3->CEP = strdup("03003-000");
    mensagem_sucesso("Dados para CEP 03003-000 criados com sucesso!\n");
    
    // Insert into the tree
    if(inserir_rubro_negro(arvore, dado1, comparar_dados_CEP))
        mensagem_sucesso("CEP 01001-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 01001-000!\n");
        
    if(inserir_rubro_negro(arvore, dado2, comparar_dados_CEP))
        mensagem_sucesso("CEP 02002-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 02002-000!\n");
        
    if(inserir_rubro_negro(arvore, dado3, comparar_dados_CEP))
        mensagem_sucesso("CEP 03003-000 inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir CEP 03003-000!\n");
}

// Test function for printing and searching in the CEP tree
void testar_impressao_e_busca_ceps(RUBRO_NEGRO *arvore) {
    print_verde("\nTestando impressao e busca de CEPs...\n");
    
    // Test printing entire tree
    print_amarelo("Imprimindo todos os CEPs:\n");
    imprimir_rubro_negro(arvore, imprimir_dados_CEP);
    
    // Test filtered printing (CEPs starting with '0')
    print_amarelo("\nImprimindo CEPs com filtro (começando com '0'):\n");
    DADOS *filtro = alocar_dados();
    filtro->CEP = strdup("0");
    mensagem_sucesso("Filtro para CEPs criado com sucesso!\n");
    
    imprimir_filtro_rubro_negro(arvore, filtro, imprimir_dados_CEP, comparar_dados_CEP);
    
    // Test searching for existing CEP
    print_amarelo("\nBuscando CEP '02002-000':\n");
    DADOS *busca = alocar_dados();
    busca->CEP = strdup("02002-000");
    mensagem_sucesso("Dado para busca de CEP criado com sucesso!\n");
    
    RUBRO_NEGRO *resultado = buscar_rubro_negro(arvore, busca, comparar_dados_CEP);
    if (resultado != NULL) {
        mensagem_sucesso("CEP encontrado:\n");
        imprimir_dados_CEP(resultado->info);
    } else {
        mensagem_erro("CEP nao encontrado!\n");
    }
    
    // Free memory after search
    liberar_dados_CEP(&busca);
    mensagem_sucesso("Memoria para busca de '02002-000' liberada!\n");
    
    // Test searching for non-existent CEP
    print_amarelo("\nBuscando CEP inexistente '99999-999':\n");
    busca = alocar_dados();
    busca->CEP = strdup("99999-999");
    
    resultado = buscar_rubro_negro(arvore, busca, comparar_dados_CEP);
    if (resultado != NULL) {
        mensagem_sucesso("CEP encontrado:\n");
        imprimir_dados_CEP(resultado->info);
    } else {
        mensagem_erro("CEP nao encontrado!\n");
    }
    
    // Free memory after search
    liberar_dados_CEP(&busca);
    mensagem_sucesso("Memoria para busca de '99999-999' liberada!\n");
    
    // Only clean up filter at the end
    liberar_dados_CEP(&filtro);
}

int main() {
    // Test with cities
    RUBRO_NEGRO *arvore_cidades = NULL;
    print_amarelo("=== TESTE COM CIDADES ===\n");
    testar_insercao_cidades(&arvore_cidades);
    testar_impressao_e_busca_cidades(arvore_cidades);
    
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
    testar_impressao_e_busca_pessoas(arvore_pessoas);
    
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
    testar_impressao_e_busca_ceps(arvore_ceps);
    
    print_amarelo("Liberando arvore de CEPs...\n");
    liberar_rubro_negro(&arvore_ceps, liberar_dados_CEP);
    if(arvore_ceps == NULL)
        mensagem_sucesso("Arvore de CEPs liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar arvore de CEPs!\n");
    
    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");
    
    return 0;
}
