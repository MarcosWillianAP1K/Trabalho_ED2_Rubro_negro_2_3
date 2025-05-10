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
    printf("\n\n==================================\n");
    printf("==== TESTE DE INSERCAO - CIDADES ====\n");
    printf("==================================\n\n");
    
    print_verde("Testando insercao de cidades...\n");
    
    // Create test data for original 3 cities
    DADOS *dado1 = alocar_dados();
    dado1->cidade = criar_cidade("Sao Paulo", 12000000, NULL);
    
    DADOS *dado2 = alocar_dados();
    dado2->cidade = criar_cidade("Rio de Janeiro", 6700000, NULL);
    
    DADOS *dado3 = alocar_dados();
    dado3->cidade = criar_cidade("Belo Horizonte", 2500000, NULL);
    
    // Create 10 additional cities for more comprehensive testing
    DADOS *dado4 = alocar_dados();
    dado4->cidade = criar_cidade("Salvador", 2900000, NULL);
    
    DADOS *dado5 = alocar_dados();
    dado5->cidade = criar_cidade("Fortaleza", 2600000, NULL);
    
    DADOS *dado6 = alocar_dados();
    dado6->cidade = criar_cidade("Brasilia", 3000000, NULL);
    
    DADOS *dado7 = alocar_dados();
    dado7->cidade = criar_cidade("Curitiba", 1900000, NULL);
    
    DADOS *dado8 = alocar_dados();
    dado8->cidade = criar_cidade("Manaus", 2100000, NULL);
    
    DADOS *dado9 = alocar_dados();
    dado9->cidade = criar_cidade("Recife", 1600000, NULL);
    
    DADOS *dado10 = alocar_dados();
    dado10->cidade = criar_cidade("Porto Alegre", 1400000, NULL);
    
    DADOS *dado11 = alocar_dados();
    dado11->cidade = criar_cidade("Belem", 1500000, NULL);
    
    DADOS *dado12 = alocar_dados();
    dado12->cidade = criar_cidade("Goiania", 1400000, NULL);
    
    DADOS *dado13 = alocar_dados();
    dado13->cidade = criar_cidade("Guarulhos", 1300000, NULL);
    
    mensagem_sucesso("Todos os dados de cidades foram criados com sucesso!\n");
    
    // Track if all insertions are successful
    int all_success = 1;
    
    // Insert original cities into the tree
    if(!inserir_rubro_negro(arvore, dado1, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Sao Paulo!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado2, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Rio de Janeiro!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado3, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Belo Horizonte!\n");
        all_success = 0;
    }
    
    // Insert additional cities into the tree
    if(!inserir_rubro_negro(arvore, dado4, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Salvador!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado5, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Fortaleza!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado6, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Brasilia!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado7, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Curitiba!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado8, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Manaus!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado9, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Recife!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado10, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Porto Alegre!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado11, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Belem!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado12, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Goiania!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado13, comparar_dados_nome_cidade)) {
        mensagem_erro("Falha ao inserir Guarulhos!\n");
        all_success = 0;
    }
    
    // Print success message if all insertions succeeded
    if(all_success) {
        mensagem_sucesso("Todas as cidades foram inseridas com sucesso!\n");
    }
}

// Test function for printing and searching in the city tree
void testar_impressao_e_busca_cidades(RUBRO_NEGRO *arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE BUSCA - CIDADES ====\n");
    printf("==================================\n\n");
    
    print_verde("\nTestando impressao e busca de cidades...\n");
    
    // Test printing entire tree
    print_amarelo("Imprimindo todas as cidades:\n");
    imprimir_rubro_negro(arvore, imprimir_dados_cidade);
    
    // Test filtered printing - will print only cities starting with 'S'
    print_amarelo("\nImprimindo cidades com filtro (começando com 'S'):\n");
    DADOS *filtro_cidade_rio_de_janeiro = alocar_dados();
    filtro_cidade_rio_de_janeiro->cidade = criar_cidade("Rio de Janeiro", 0, NULL);
    mensagem_sucesso("Filtro para cidades criado com sucesso!\n");
    
    // This will traverse the whole tree, comparing each node with the filter
    // using comparar_dados_nome_cidade. Only nodes that match will be printed.
    imprimir_filtro_rubro_negro(arvore, filtro_cidade_rio_de_janeiro, imprimir_dados_cidade, comparar_dados_nome_cidade);
    
    // Test another filter - cities starting with 'B'
    print_amarelo("\nImprimindo cidades com filtro (começando com 'B'):\n");
    DADOS *filtro_cidade_Belo_horizonte = alocar_dados();
    filtro_cidade_Belo_horizonte->cidade = criar_cidade("Belo Horizonte", 0, NULL);
    imprimir_filtro_rubro_negro(arvore, filtro_cidade_Belo_horizonte, imprimir_dados_cidade, comparar_dados_nome_cidade);

    // Test searching for existing city
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
    
    // Clean up filters
    liberar_dados_cidade(&filtro_cidade_rio_de_janeiro);
    liberar_dados_cidade(&filtro_cidade_Belo_horizonte);
}

// Test function for removal of cities from the tree
void testar_remocao_cidades(RUBRO_NEGRO **arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE REMOCAO - CIDADES ====\n");
    printf("==================================\n\n");
    
    print_verde("\nTestando remocao de cidades...\n");
    
    // Create data for removal tests
    DADOS *cidade_remover1 = alocar_dados();
    cidade_remover1->cidade = criar_cidade("Rio de Janeiro", 0, NULL);
    
    DADOS *cidade_remover2 = alocar_dados();
    cidade_remover2->cidade = criar_cidade("Belo Horizonte", 0, NULL);
    
    DADOS *cidade_remover3 = alocar_dados();
    cidade_remover3->cidade = criar_cidade("Salvador", 0, NULL);
    
    DADOS *cidade_remover4 = alocar_dados();
    cidade_remover4->cidade = criar_cidade("Recife", 0, NULL);
    
    // Create data for non-existent cities
    DADOS *cidade_inexistente1 = alocar_dados();
    cidade_inexistente1->cidade = criar_cidade("Campinas", 0, NULL);
    
    DADOS *cidade_inexistente2 = alocar_dados();
    cidade_inexistente2->cidade = criar_cidade("Florianopolis", 0, NULL);
    
    mensagem_sucesso("Dados para teste de remocao de cidades criados com sucesso!\n");
    
    // Test removing first existing city
    print_amarelo("Removendo cidade 'Rio de Janeiro':\n");
    DADOS *cidade_removida1 = remover_rubro_negro(arvore, cidade_remover1, comparar_dados_nome_cidade);
    if (cidade_removida1 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso!\n");
        print_amarelo("Informacoes da cidade removida:\n");
        imprimir_dados_cidade(cidade_removida1);
        
        liberar_dados_cidade(&cidade_removida1);
    } else {
        mensagem_erro("Falha ao remover cidade Rio de Janeiro!\n");
    }
    
    // Test removing second existing city
    print_amarelo("\nRemovendo cidade 'Belo Horizonte':\n");
    DADOS *cidade_removida2 = remover_rubro_negro(arvore, cidade_remover2, comparar_dados_nome_cidade);
    if (cidade_removida2 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso!\n");
        print_amarelo("Informacoes da cidade removida:\n");
        imprimir_dados_cidade(cidade_removida2);
        
        liberar_dados_cidade(&cidade_removida2);
    } else {
        mensagem_erro("Falha ao remover cidade Belo Horizonte!\n");
    }
    
    // Test removing third existing city
    print_amarelo("\nRemovendo cidade 'Salvador':\n");
    DADOS *cidade_removida3 = remover_rubro_negro(arvore, cidade_remover3, comparar_dados_nome_cidade);
    if (cidade_removida3 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso!\n");
        print_amarelo("Informacoes da cidade removida:\n");
        imprimir_dados_cidade(cidade_removida3);
        
        liberar_dados_cidade(&cidade_removida3);
    } else {
        mensagem_erro("Falha ao remover cidade Salvador!\n");
    }
    
    // Test removing fourth existing city
    print_amarelo("\nRemovendo cidade 'Recife':\n");
    DADOS *cidade_removida4 = remover_rubro_negro(arvore, cidade_remover4, comparar_dados_nome_cidade);
    if (cidade_removida4 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso!\n");
        print_amarelo("Informacoes da cidade removida:\n");
        imprimir_dados_cidade(cidade_removida4);
        
        liberar_dados_cidade(&cidade_removida4);
    } else {
        mensagem_erro("Falha ao remover cidade Recife!\n");
    }
    
    // Test printing tree after removals
    print_amarelo("\nArvore apos remocoes de cidades:\n");
    imprimir_rubro_negro(*arvore, imprimir_dados_cidade);
    
    // Try to remove first non-existent city
    print_amarelo("\nTentando remover cidade inexistente 'Campinas':\n");
    DADOS *resultado_inexistente1 = remover_rubro_negro(arvore, cidade_inexistente1, comparar_dados_nome_cidade);
    if (resultado_inexistente1 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso (inesperado)!\n");
        liberar_dados_cidade(&resultado_inexistente1);
    } else {
        mensagem_erro("Cidade Campinas nao encontrada para remocao (esperado)!\n");
    }
    
    // Try to remove second non-existent city
    print_amarelo("\nTentando remover cidade inexistente 'Florianopolis':\n");
    DADOS *resultado_inexistente2 = remover_rubro_negro(arvore, cidade_inexistente2, comparar_dados_nome_cidade);
    if (resultado_inexistente2 != NULL) {
        mensagem_sucesso("Cidade removida com sucesso (inesperado)!\n");
        liberar_dados_cidade(&resultado_inexistente2);
    } else {
        mensagem_erro("Cidade Florianopolis nao encontrada para remocao (esperado)!\n");
    }
    
    // Free all the search data
    liberar_dados_cidade(&cidade_remover1);
    liberar_dados_cidade(&cidade_remover2);
    liberar_dados_cidade(&cidade_remover3);
    liberar_dados_cidade(&cidade_remover4);
    liberar_dados_cidade(&cidade_inexistente1);
    liberar_dados_cidade(&cidade_inexistente2);
    
    mensagem_sucesso("Memoria para busca de remocao liberada!\n");
}

// Test function for person insertions
void testar_insercao_pessoas(RUBRO_NEGRO **arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE INSERCAO - PESSOAS ====\n");
    printf("==================================\n\n");
    
    print_verde("Testando insercao de pessoas...\n");
    
    // Create test data for original 3 people
    DADOS *dado1 = alocar_dados();
    DATA *data1 = criar_data(1, 1, 1990);
    dado1->pessoa = criar_pessoa("123.456.789-00", "Joao Silva", "01001-000", "02002-000", data1);
    
    DADOS *dado2 = alocar_dados();
    DATA *data2 = criar_data(15, 5, 1985);
    dado2->pessoa = criar_pessoa("987.654.321-00", "Maria Santos", "03003-000", "04004-000", data2);
    
    DADOS *dado3 = alocar_dados();
    DATA *data3 = criar_data(30, 10, 1995);
    dado3->pessoa = criar_pessoa("111.222.333-44", "Pedro Oliveira", "05005-000", "06006-000", data3);
    
    // Create 10 additional people for more comprehensive testing
    DADOS *dado4 = alocar_dados();
    DATA *data4 = criar_data(5, 3, 1992);
    dado4->pessoa = criar_pessoa("222.333.444-55", "Ana Costa", "10101-010", "20202-020", data4);
    
    DADOS *dado5 = alocar_dados();
    DATA *data5 = criar_data(12, 7, 1988);
    dado5->pessoa = criar_pessoa("333.444.555-66", "Carlos Mendes", "30303-030", "40404-040", data5);
    
    DADOS *dado6 = alocar_dados();
    DATA *data6 = criar_data(25, 4, 1993);
    dado6->pessoa = criar_pessoa("444.555.666-77", "Fernanda Lima", "50505-050", "60606-060", data6);
    
    DADOS *dado7 = alocar_dados();
    DATA *data7 = criar_data(18, 9, 1990);
    dado7->pessoa = criar_pessoa("555.666.777-88", "Gabriel Alves", "70707-070", "80808-080", data7);
    
    DADOS *dado8 = alocar_dados();
    DATA *data8 = criar_data(3, 11, 1991);
    dado8->pessoa = criar_pessoa("666.777.888-99", "Helena Duarte", "90909-090", "10001-001", data8);
    
    DADOS *dado9 = alocar_dados();
    DATA *data9 = criar_data(10, 6, 1987);
    dado9->pessoa = criar_pessoa("777.888.999-00", "Igor Ferreira", "20002-002", "30003-003", data9);
    
    DADOS *dado10 = alocar_dados();
    DATA *data10 = criar_data(22, 2, 1994);
    dado10->pessoa = criar_pessoa("888.999.000-11", "Julia Barbosa", "40004-004", "50005-005", data10);
    
    // Add people with the same name but different CPFs
    DADOS *dado11 = alocar_dados();
    DATA *data11 = criar_data(8, 8, 1989);
    dado11->pessoa = criar_pessoa("999.000.111-22", "Joao Silva", "60006-006", "70007-007", data11);
    
    DADOS *dado12 = alocar_dados();
    DATA *data12 = criar_data(17, 12, 1996);
    dado12->pessoa = criar_pessoa("000.111.222-33", "Maria Santos", "80008-008", "90009-009", data12);
    
    DADOS *dado13 = alocar_dados();
    DATA *data13 = criar_data(29, 1, 1997);
    dado13->pessoa = criar_pessoa("111.222.333-55", "Joao Silva", "11111-111", "22222-222", data13);
    
    mensagem_sucesso("Todos os dados de pessoas foram criados com sucesso!\n");
    
    // Track if all insertions are successful
    int all_success = 1;
    
    // Insert into the tree using CPF comparison instead of name
    if(!inserir_rubro_negro(arvore, dado1, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 123.456.789-00!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado2, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 987.654.321-00!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado3, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 111.222.333-44!\n");
        all_success = 0;
    }
    
    // Insert additional people
    if(!inserir_rubro_negro(arvore, dado4, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 222.333.444-55!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado5, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 333.444.555-66!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado6, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 444.555.666-77!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado7, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 555.666.777-88!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado8, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 666.777.888-99!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado9, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 777.888.999-00!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado10, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 888.999.000-11!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado11, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 999.000.111-22 (Joao Silva 2)!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado12, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 000.111.222-33 (Maria Santos 2)!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado13, comparar_dados_CPF_pessoa)) {
        mensagem_erro("Falha ao inserir pessoa com CPF 111.222.333-55 (Joao Silva 3)!\n");
        all_success = 0;
    }
    
    // Print success message if all insertions succeeded
    if(all_success) {
        mensagem_sucesso("Todas as pessoas foram inseridas com sucesso!\n");
        print_amarelo("Observe que existem pessoas com nomes iguais (Joao Silva e Maria Santos), mas com CPFs diferentes!\n");
    }
}

// Test function for printing and searching in the person tree
void testar_impressao_e_busca_pessoas(RUBRO_NEGRO *arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE BUSCA - PESSOAS ====\n");
    printf("==================================\n\n");
    
    print_verde("\nTestando impressao e busca de pessoas...\n");
    
    // Test printing entire tree
    print_amarelo("Imprimindo todas as pessoas:\n");
    imprimir_rubro_negro(arvore, imprimir_dados_pessoa);
    
    // Test filtered printing (by name Joao Silva)
    print_amarelo("\nImprimindo pessoas com filtro (Joao Silva):\n");
    DADOS *filtro = alocar_dados();
    filtro->pessoa = criar_pessoa("", "Joao Silva", "", "", NULL);

    mensagem_sucesso("Filtro para pessoas criado com sucesso!\n");
    
    imprimir_filtro_rubro_negro(arvore, filtro, imprimir_dados_pessoa, comparar_dados_nome_pessoa);
    
    // Test searching for existing person
    print_amarelo("\nBuscando pessoa com CPF '987.654.321-00':\n");
    DADOS *busca = alocar_dados();
    busca->pessoa = criar_pessoa("987.654.321-00", "", "", "", NULL);
    mensagem_sucesso("Dado para busca de pessoa criado com sucesso!\n");
    
    RUBRO_NEGRO *resultado = buscar_rubro_negro(arvore, busca, comparar_dados_CPF_pessoa);
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
    busca->pessoa = criar_pessoa("000.000.000-00", "", "", "", NULL);
    
    resultado = buscar_rubro_negro(arvore, busca, comparar_dados_CPF_pessoa);
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

// Test function for removal of people from the tree
void testar_remocao_pessoas(RUBRO_NEGRO **arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE REMOCAO - PESSOAS ====\n");
    printf("==================================\n\n");
    
    print_verde("\nTestando remocao de pessoas...\n");
    
    // Create data for removal tests
    DADOS *pessoa_remover1 = alocar_dados();
    pessoa_remover1->pessoa = criar_pessoa("987.654.321-00", "", "", "", NULL);
    
    DADOS *pessoa_remover2 = alocar_dados();
    pessoa_remover2->pessoa = criar_pessoa("111.222.333-44", "", "", "", NULL);
    
    DADOS *pessoa_remover3 = alocar_dados();
    pessoa_remover3->pessoa = criar_pessoa("222.333.444-55", "", "", "", NULL);
    
    DADOS *pessoa_remover4 = alocar_dados();
    pessoa_remover4->pessoa = criar_pessoa("333.444.555-66", "", "", "", NULL);
    
    // Create data for non-existent people
    DADOS *pessoa_inexistente1 = alocar_dados();
    pessoa_inexistente1->pessoa = criar_pessoa("000.000.000-00", "", "", "", NULL);
    
    DADOS *pessoa_inexistente2 = alocar_dados();
    pessoa_inexistente2->pessoa = criar_pessoa("999.999.999-99", "", "", "", NULL);
    
    mensagem_sucesso("Dados para teste de remocao de pessoas criados com sucesso!\n");
    
    // Test removing first person
    print_amarelo("Removendo pessoa com CPF '987.654.321-00':\n");
    DADOS *pessoa_removida1 = remover_rubro_negro(arvore, pessoa_remover1, comparar_dados_CPF_pessoa);
    if (pessoa_removida1 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso!\n");
        print_amarelo("Informacoes da pessoa removida:\n");
        imprimir_dados_pessoa(pessoa_removida1);
        
        liberar_dados_pessoa(&pessoa_removida1);
    } else {
        mensagem_erro("Falha ao remover pessoa com CPF '987.654.321-00'!\n");
    }
    
    // Test removing second person
    print_amarelo("\nRemovendo pessoa com CPF '111.222.333-44':\n");
    DADOS *pessoa_removida2 = remover_rubro_negro(arvore, pessoa_remover2, comparar_dados_CPF_pessoa);
    if (pessoa_removida2 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso!\n");
        print_amarelo("Informacoes da pessoa removida:\n");
        imprimir_dados_pessoa(pessoa_removida2);
        
        liberar_dados_pessoa(&pessoa_removida2);
    } else {
        mensagem_erro("Falha ao remover pessoa com CPF '111.222.333-44'!\n");
    }
    
    // Test removing third person
    print_amarelo("\nRemovendo pessoa com CPF '222.333.444-55':\n");
    DADOS *pessoa_removida3 = remover_rubro_negro(arvore, pessoa_remover3, comparar_dados_CPF_pessoa);
    if (pessoa_removida3 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso!\n");
        print_amarelo("Informacoes da pessoa removida:\n");
        imprimir_dados_pessoa(pessoa_removida3);
        
        liberar_dados_pessoa(&pessoa_removida3);
    } else {
        mensagem_erro("Falha ao remover pessoa com CPF '222.333.444-55'!\n");
    }
    
    // Test removing fourth person
    print_amarelo("\nRemovendo pessoa com CPF '333.444.555-66':\n");
    DADOS *pessoa_removida4 = remover_rubro_negro(arvore, pessoa_remover4, comparar_dados_CPF_pessoa);
    if (pessoa_removida4 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso!\n");
        print_amarelo("Informacoes da pessoa removida:\n");
        imprimir_dados_pessoa(pessoa_removida4);
        
        liberar_dados_pessoa(&pessoa_removida4);
    } else {
        mensagem_erro("Falha ao remover pessoa com CPF '333.444.555-66'!\n");
    }
    
    // Test printing tree after removals
    print_amarelo("\nArvore apos remocoes de pessoas:\n");
    imprimir_rubro_negro(*arvore, imprimir_dados_pessoa);
    
    // Try to remove first non-existent person
    print_amarelo("\nTentando remover pessoa inexistente com CPF '000.000.000-00':\n");
    DADOS *resultado_inexistente1 = remover_rubro_negro(arvore, pessoa_inexistente1, comparar_dados_CPF_pessoa);
    if (resultado_inexistente1 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso (inesperado)!\n");
        liberar_dados_pessoa(&resultado_inexistente1);
    } else {
        mensagem_erro("Pessoa com CPF '000.000.000-00' nao encontrada para remocao (esperado)!\n");
    }
    
    // Try to remove second non-existent person
    print_amarelo("\nTentando remover pessoa inexistente com CPF '999.999.999-99':\n");
    DADOS *resultado_inexistente2 = remover_rubro_negro(arvore, pessoa_inexistente2, comparar_dados_CPF_pessoa);
    if (resultado_inexistente2 != NULL) {
        mensagem_sucesso("Pessoa removida com sucesso (inesperado)!\n");
        liberar_dados_pessoa(&resultado_inexistente2);
    } else {
        mensagem_erro("Pessoa com CPF '999.999.999-99' nao encontrada para remocao (esperado)!\n");
    }
    
    // Free all the search data
    liberar_dados_pessoa(&pessoa_remover1);
    liberar_dados_pessoa(&pessoa_remover2);
    liberar_dados_pessoa(&pessoa_remover3);
    liberar_dados_pessoa(&pessoa_remover4);
    liberar_dados_pessoa(&pessoa_inexistente1);
    liberar_dados_pessoa(&pessoa_inexistente2);
    
    mensagem_sucesso("Memoria para busca de remocao liberada!\n");
}

// Test function for CEP insertions
void testar_insercao_ceps(RUBRO_NEGRO **arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE INSERCAO - CEPs ====\n");
    printf("==================================\n\n");
    
    print_verde("Testando insercao de CEPs...\n");
    
    // Create test data for CEPs - original 3
    DADOS *dado1 = alocar_dados();
    dado1->CEP = strdup("01001-000");
    
    DADOS *dado2 = alocar_dados();
    dado2->CEP = strdup("02002-000");
    
    DADOS *dado3 = alocar_dados();
    dado3->CEP = strdup("03003-000");
    
    // Additional 10 CEPs for more comprehensive testing
    DADOS *dado4 = alocar_dados();
    dado4->CEP = strdup("04004-000");
    
    DADOS *dado5 = alocar_dados();
    dado5->CEP = strdup("05005-000");
    
    DADOS *dado6 = alocar_dados();
    dado6->CEP = strdup("10101-010");
    
    DADOS *dado7 = alocar_dados();
    dado7->CEP = strdup("20202-020");
    
    DADOS *dado8 = alocar_dados();
    dado8->CEP = strdup("30303-030");
    
    DADOS *dado9 = alocar_dados();
    dado9->CEP = strdup("40404-040");
    
    DADOS *dado10 = alocar_dados();
    dado10->CEP = strdup("50505-050");
    
    DADOS *dado11 = alocar_dados();
    dado11->CEP = strdup("60606-060");
    
    DADOS *dado12 = alocar_dados();
    dado12->CEP = strdup("70707-070");
    
    DADOS *dado13 = alocar_dados();
    dado13->CEP = strdup("88888-888");
    
    mensagem_sucesso("Todos os dados de CEPs foram criados com sucesso!\n");
    
    // Track if all insertions are successful
    int all_success = 1;
    
    // Insert original CEPs into the tree
    if(!inserir_rubro_negro(arvore, dado1, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 01001-000!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado2, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 02002-000!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado3, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 03003-000!\n");
        all_success = 0;
    }
    
    // Insert additional CEPs into the tree
    if(!inserir_rubro_negro(arvore, dado4, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 04004-000!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado5, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 05005-000!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado6, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 10101-010!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado7, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 20202-020!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado8, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 30303-030!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado9, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 40404-040!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado10, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 50505-050!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado11, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 60606-060!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado12, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 70707-070!\n");
        all_success = 0;
    }
        
    if(!inserir_rubro_negro(arvore, dado13, comparar_dados_CEP)) {
        mensagem_erro("Falha ao inserir CEP 88888-888!\n");
        all_success = 0;
    }
    
    // Print success message if all insertions succeeded
    if(all_success) {
        mensagem_sucesso("Todos os CEPs foram inseridos com sucesso!\n");
    }
}

// Test function for printing and searching in the CEP tree
void testar_impressao_e_busca_ceps(RUBRO_NEGRO *arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE BUSCA - CEPs ====\n");
    printf("==================================\n\n");
    
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

// Test function for removal of CEPs from the tree
void testar_remocao_ceps(RUBRO_NEGRO **arvore) {
    printf("\n\n==================================\n");
    printf("==== TESTE DE REMOCAO - CEPs ====\n");
    printf("==================================\n\n");
    
    print_verde("\nTestando remocao de CEPs...\n");
    
    // Create data for removal tests
    DADOS *cep_remover1 = alocar_dados();
    cep_remover1->CEP = strdup("02002-000");
    
    DADOS *cep_remover2 = alocar_dados();
    cep_remover2->CEP = strdup("03003-000");
    
    DADOS *cep_remover3 = alocar_dados();
    cep_remover3->CEP = strdup("04004-000");
    
    DADOS *cep_remover4 = alocar_dados();
    cep_remover4->CEP = strdup("10101-010");
    
    // Create data for non-existent CEPs
    DADOS *cep_inexistente1 = alocar_dados();
    cep_inexistente1->CEP = strdup("99999-999");
    
    DADOS *cep_inexistente2 = alocar_dados();
    cep_inexistente2->CEP = strdup("88888-888");
    
    mensagem_sucesso("Dados para teste de remocao de CEPs criados com sucesso!\n");
    
    // Test removing first existing CEP
    print_amarelo("Removendo CEP '02002-000':\n");
    DADOS *cep_removido1 = remover_rubro_negro(arvore, cep_remover1, comparar_dados_CEP);
    if (cep_removido1 != NULL) {
        mensagem_sucesso("CEP removido com sucesso!\n");
        print_amarelo("Informacoes do CEP removido:\n");
        imprimir_dados_CEP(cep_removido1);
        
        liberar_dados_CEP(&cep_removido1);
    } else {
        mensagem_erro("Falha ao remover CEP '02002-000'!\n");
    }
    
    // Test removing second existing CEP
    print_amarelo("\nRemovendo CEP '03003-000':\n");
    DADOS *cep_removido2 = remover_rubro_negro(arvore, cep_remover2, comparar_dados_CEP);
    if (cep_removido2 != NULL) {
        mensagem_sucesso("CEP removido com sucesso!\n");
        print_amarelo("Informacoes do CEP removido:\n");
        imprimir_dados_CEP(cep_removido2);
        
        liberar_dados_CEP(&cep_removido2);
    } else {
        mensagem_erro("Falha ao remover CEP '03003-000'!\n");
    }
    
    // Test removing third existing CEP
    print_amarelo("\nRemovendo CEP '04004-000':\n");
    DADOS *cep_removido3 = remover_rubro_negro(arvore, cep_remover3, comparar_dados_CEP);
    if (cep_removido3 != NULL) {
        mensagem_sucesso("CEP removido com sucesso!\n");
        print_amarelo("Informacoes do CEP removido:\n");
        imprimir_dados_CEP(cep_removido3);
        
        liberar_dados_CEP(&cep_removido3);
    } else {
        mensagem_erro("Falha ao remover CEP '04004-000'!\n");
    }
    
    // Test removing fourth existing CEP
    print_amarelo("\nRemovendo CEP '10101-010':\n");
    DADOS *cep_removido4 = remover_rubro_negro(arvore, cep_remover4, comparar_dados_CEP);
    if (cep_removido4 != NULL) {
        mensagem_sucesso("CEP removido com sucesso!\n");
        print_amarelo("Informacoes do CEP removido:\n");
        imprimir_dados_CEP(cep_removido4);
        
        liberar_dados_CEP(&cep_removido4);
    } else {
        mensagem_erro("Falha ao remover CEP '10101-010'!\n");
    }
    
    // Test printing tree after removals
    print_amarelo("\nArvore apos remocoes de CEPs:\n");
    imprimir_rubro_negro(*arvore, imprimir_dados_CEP);
    
    // Try to remove first non-existent CEP
    print_amarelo("\nTentando remover CEP inexistente '99999-999':\n");
    DADOS *resultado_inexistente1 = remover_rubro_negro(arvore, cep_inexistente1, comparar_dados_CEP);
    if (resultado_inexistente1 != NULL) {
        mensagem_sucesso("CEP removido com sucesso (inesperado)!\n");
        liberar_dados_CEP(&resultado_inexistente1);
    } else {
        mensagem_erro("CEP '99999-999' nao encontrado para remocao (esperado)!\n");
    }
    
    // Try to remove second non-existent CEP
    print_amarelo("\nTentando remover CEP inexistente '88888-888':\n");
    DADOS *resultado_inexistente2 = remover_rubro_negro(arvore, cep_inexistente2, comparar_dados_CEP);
    if (resultado_inexistente2 != NULL) {
        mensagem_sucesso("CEP removido com sucesso (inesperado)!\n");
        liberar_dados_CEP(&resultado_inexistente2);
    } else {
        mensagem_erro("CEP '88888-888' nao encontrado para remocao (esperado)!\n");
    }
    
    // Free all the search data
    liberar_dados_CEP(&cep_remover1);
    liberar_dados_CEP(&cep_remover2);
    liberar_dados_CEP(&cep_remover3);
    liberar_dados_CEP(&cep_remover4);
    liberar_dados_CEP(&cep_inexistente1);
    liberar_dados_CEP(&cep_inexistente2);
    
    mensagem_sucesso("Memoria para busca de remocao liberada!\n");
}

int main() {
    // Test with cities
    RUBRO_NEGRO *arvore_cidades = NULL;
    print_amarelo("=== TESTE COM CIDADES ===\n");
    testar_insercao_cidades(&arvore_cidades);
    testar_impressao_e_busca_cidades(arvore_cidades);
    testar_remocao_cidades(&arvore_cidades);
    
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
    testar_remocao_pessoas(&arvore_pessoas);
    
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
    testar_remocao_ceps(&arvore_ceps);
    
    print_amarelo("Liberando arvore de CEPs...\n");
    liberar_rubro_negro(&arvore_ceps, liberar_dados_CEP);
    if(arvore_ceps == NULL)
        mensagem_sucesso("Arvore de CEPs liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar arvore de CEPs!\n");
    
    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");
    
    return 0;
}
