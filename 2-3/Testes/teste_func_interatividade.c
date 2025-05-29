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
#include "../Includes/Estruturas/2-3.h"
#include "../Includes/Estruturas/Dados.h"
#include "../Includes/Interatividade/func_interatividade.h"
#include "../Includes/Objetos/Estado.h"
#include "../Includes/Objetos/Cidade.h"
#include "../Includes/Objetos/Pessoa.h"
#include "../Includes/Objetos/CEP.h"
#include "../Includes/Objetos/Data.h"
#include "../Includes/Objetos/CPF.h"
#include "../Includes/Utilitarios/funcao_sistema.h"

// Teste de cadastro de estados
void testar_cadastrar_estado() {
    print_amarelo("\n=== TESTE DE CADASTRO DE ESTADOS ===\n");
    
    LISTA_DUPLAMENTE *lista_estados = NULL;
    
    // Criar estados para teste
    ESTADO estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso para teste!\n");
    
    ESTADO estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    mensagem_sucesso("Estado Rio de Janeiro criado com sucesso para teste!\n");
    
    ESTADO estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    mensagem_sucesso("Estado Minas Gerais criado com sucesso para teste!\n");
    
    // Testar cadastro de estados
    print_amarelo("Cadastrando estado: Sao Paulo\n");
    LISTA_DUPLAMENTE *resultado1 = cadastrar_estado(&lista_estados, estado1);
    if (resultado1 != NULL) {
        mensagem_sucesso("Estado Sao Paulo cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o estado Sao Paulo!\n");
    }
    
    print_amarelo("Cadastrando estado: Rio de Janeiro\n");
    LISTA_DUPLAMENTE *resultado2 = cadastrar_estado(&lista_estados, estado2);
    if (resultado2 != NULL) {
        mensagem_sucesso("Estado Rio de Janeiro cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o estado Rio de Janeiro!\n");
    }
    
    print_amarelo("Cadastrando estado: Minas Gerais\n");
    LISTA_DUPLAMENTE *resultado3 = cadastrar_estado(&lista_estados, estado3);
    if (resultado3 != NULL) {
        mensagem_sucesso("Estado Minas Gerais cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o estado Minas Gerais!\n");
    }
    
    // Tentativa de cadastrar estado duplicado (deve falhar ou atualizar)
    print_amarelo("Tentando cadastrar estado duplicado: Sao Paulo\n");
    LISTA_DUPLAMENTE *resultado_duplicado = cadastrar_estado(&lista_estados, estado1);
    if (resultado_duplicado == NULL) {
        mensagem_sucesso("Cadastro de estado duplicado foi rejeitado corretamente!\n");
    } else if (resultado_duplicado == resultado1) {
        mensagem_sucesso("Estado existente foi atualizado corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar cadastrar estado duplicado!\n");
    }
    
    // Exibir a lista de estados cadastrados
    print_amarelo("\nEstados cadastrados:\n");
    exibirLista(lista_estados);
    
    // Liberar a lista de estados
    print_amarelo("\nLiberando lista de estados...\n");
    liberar_lista(&lista_estados);
    if (lista_estados == NULL) {
        mensagem_sucesso("Lista de estados liberada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao liberar lista de estados!\n");
    }
}

// Teste de cadastro de cidades
void testar_cadastrar_cidade() {
    print_amarelo("\n=== TESTE DE CADASTRO DE CIDADES ===\n");
    
    // Primeiro, criar um estado para testar o cadastro de cidades
    ESTADO estado = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso para teste!\n");
    
    // Criar cidades para teste
    CIDADE cidade1 = criar_cidade("Sao Paulo", 12000000, NULL);
    mensagem_sucesso("Cidade Sao Paulo criada com sucesso para teste!\n");
    
    CIDADE cidade2 = criar_cidade("Campinas", 1200000, NULL);
    mensagem_sucesso("Cidade Campinas criada com sucesso para teste!\n");
    
    CIDADE cidade3 = criar_cidade("Santos", 430000, NULL);
    mensagem_sucesso("Cidade Santos criada com sucesso para teste!\n");
    
    // Testar cadastro de cidades
    print_amarelo("Cadastrando cidade: Sao Paulo\n");
    RUBRO_NEGRO *resultado1 = cadastrar_cidade(&estado, cidade1);
    if (resultado1 != NULL) {
        mensagem_sucesso("Cidade Sao Paulo cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar a cidade Sao Paulo!\n");
    }
    
    print_amarelo("Cadastrando cidade: Campinas\n");
    RUBRO_NEGRO *resultado2 = cadastrar_cidade(&estado, cidade2);
    if (resultado2 != NULL) {
        mensagem_sucesso("Cidade Campinas cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar a cidade Campinas!\n");
    }
    
    print_amarelo("Cadastrando cidade: Santos\n");
    RUBRO_NEGRO *resultado3 = cadastrar_cidade(&estado, cidade3);
    if (resultado3 != NULL) {
        mensagem_sucesso("Cidade Santos cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar a cidade Santos!\n");
    }
    
    // Tentativa de cadastrar cidade duplicada (deve falhar ou atualizar)
    print_amarelo("Tentando cadastrar cidade duplicada: Sao Paulo\n");
    RUBRO_NEGRO *resultado_duplicado = cadastrar_cidade(&estado, cidade1);
    if (resultado_duplicado == NULL) {
        mensagem_sucesso("Cadastro de cidade duplicada foi rejeitado corretamente!\n");
    } else if (resultado_duplicado == resultado1) {
        mensagem_sucesso("Cidade existente foi atualizada corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar cadastrar cidade duplicada!\n");
    }
    
    // Exibir cidades cadastradas
    print_amarelo("\nCidades cadastradas no estado Sao Paulo:\n");
    if (estado.raiz_arvore_cidade != NULL) {
        imprimir_rubro_negro(estado.raiz_arvore_cidade, imprimir_dados_cidade);
    } else {
        mensagem_erro("A raiz da árvore de cidades está vazia!\n");
    }
    
    // Liberar a memoria das cidades (através do estado)
    print_amarelo("\nLiberando memoria do estado e suas cidades...\n");
    liberar_estado(&estado);
    mensagem_sucesso("Memoria liberada com sucesso!\n");
}

// Teste de cadastro de CEPs
void testar_cadastrar_CEP() {
    print_amarelo("\n=== TESTE DE CADASTRO DE CEPs ===\n");
    
    // Criar uma lista de estados e um estado para testar
    LISTA_DUPLAMENTE *lista_estados = NULL;
    ESTADO estado = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    LISTA_DUPLAMENTE *estado_cadastrado = cadastrar_estado(&lista_estados, estado);
    
    if (estado_cadastrado == NULL) {
        mensagem_erro("Falha ao cadastrar estado para teste de CEP!\n");
        return;
    }
    
    mensagem_sucesso("Estado Sao Paulo cadastrado com sucesso para teste de CEP!\n");
    
    // Cadastrar uma cidade no estado
    CIDADE cidade = criar_cidade("Sao Paulo", 12000000, NULL);
    RUBRO_NEGRO *cidade_cadastrada = cadastrar_cidade(&estado_cadastrado->estado, cidade);
    
    if (cidade_cadastrada == NULL) {
        mensagem_erro("Falha ao cadastrar cidade para teste de CEP!\n");
        liberar_lista(&lista_estados);
        return;
    }
    
    mensagem_sucesso("Cidade Sao Paulo cadastrada com sucesso para teste de CEP!\n");
    
    // Criar CEPs para teste
    char cep1[] = "01001-000";
    char cep2[] = "01002-000";
    char cep3[] = "01003-000";
    
    // Testar cadastro de CEPs
    print_amarelo("Cadastrando CEP: 01001-000\n");
    RUBRO_NEGRO *resultado1 = cadastrar_CEP(estado_cadastrado, &cidade_cadastrada->info.cidade, cep1);
    if (resultado1 != NULL) {
        mensagem_sucesso("CEP 01001-000 cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o CEP 01001-000!\n");
    }
    
    print_amarelo("Cadastrando CEP: 01002-000\n");
    RUBRO_NEGRO *resultado2 = cadastrar_CEP(estado_cadastrado, &cidade_cadastrada->info.cidade, cep2);
    if (resultado2 != NULL) {
        mensagem_sucesso("CEP 01002-000 cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o CEP 01002-000!\n");
    }
    
    print_amarelo("Cadastrando CEP: 01003-000\n");
    RUBRO_NEGRO *resultado3 = cadastrar_CEP(estado_cadastrado, &cidade_cadastrada->info.cidade, cep3);
    if (resultado3 != NULL) {
        mensagem_sucesso("CEP 01003-000 cadastrado com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar o CEP 01003-000!\n");
    }
    
    // Tentativa de cadastrar CEP duplicado
    print_amarelo("Tentando cadastrar CEP duplicado: 01001-000\n");
    RUBRO_NEGRO *resultado_duplicado = cadastrar_CEP(estado_cadastrado, &cidade_cadastrada->info.cidade, cep1);
    if (resultado_duplicado == NULL) {
        mensagem_sucesso("Cadastro de CEP duplicado foi rejeitado corretamente!\n");
    } else if (resultado_duplicado == resultado1) {
        mensagem_sucesso("CEP existente foi atualizado corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar cadastrar CEP duplicado!\n");
    }
    
    // Verificar se o CEP existe
    print_amarelo("\nVerificando se o CEP 01001-000 existe:\n");
    short int existe_cep = verificar_se_existe_CEP(estado_cadastrado, cep1);
    if (existe_cep) {
        mensagem_sucesso("CEP 01001-000 existe!\n");
    } else {
        mensagem_erro("CEP 01001-000 não foi encontrado (deveria existir)!\n");
    }
    
    print_amarelo("Verificando se o CEP 99999-999 existe (nao deve existir):\n");
    existe_cep = verificar_se_existe_CEP(estado_cadastrado, "99999-999");
    if (!existe_cep) {
        mensagem_sucesso("CEP 99999-999 nao existe (comportamento esperado)!\n");
    } else {
        mensagem_erro("CEP 99999-999 foi encontrado (nao deveria existir)!\n");
    }
    
    // Remover um CEP
    print_amarelo("\nRemovendo CEP: 01002-000\n");
    RUBRO_NEGRO *cep_removido = remover_CEP(&cidade_cadastrada->info.cidade, cep2, comparar_dados_CEP);
    if (cep_removido != NULL) {
        mensagem_sucesso("CEP 01002-000 removido com sucesso!\n");
        // Liberar o nó removido
        liberar_no_rubro_negro(&cep_removido, liberar_dados_CEP);
    } else {
        mensagem_erro("Falha ao remover o CEP 01002-000!\n");
    }
    
    // Tentar remover um CEP inexistente
    print_amarelo("Tentando remover CEP inexistente: 99999-999\n");
    RUBRO_NEGRO *cep_removido_inexistente = remover_CEP(&cidade_cadastrada->info.cidade, "99999-999", comparar_dados_CEP);
    if (cep_removido_inexistente == NULL) {
        mensagem_sucesso("Tentativa de remover CEP inexistente tratada corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar remover CEP inexistente!\n");
        liberar_no_rubro_negro(&cep_removido_inexistente, liberar_dados_CEP);
    }
    
    // Exibir CEPs da cidade
    print_amarelo("\nCEPs cadastrados na cidade Sao Paulo:\n");
    if (cidade_cadastrada->info.cidade.raiz_arvore_CEPs != NULL) {
        imprimir_rubro_negro(cidade_cadastrada->info.cidade.raiz_arvore_CEPs, imprimir_dados_CEP);
    } else {
        mensagem_erro("A raiz da árvore de CEPs está vazia!\n");
    }
    
    // Liberar a lista de estados
    print_amarelo("\nLiberando lista de estados...\n");
    liberar_lista(&lista_estados);
    mensagem_sucesso("Lista de estados liberada com sucesso!\n");
}

// Teste de cadastro e remoção de pessoas
void testar_cadastrar_remover_pessoas() {
    print_amarelo("\n=== TESTE DE CADASTRO E REMOCAO DE PESSOAS ===\n");
    
    // Criar árvore de pessoas
    RUBRO_NEGRO *raiz_pessoas = NULL;
    
    // Criar pessoas para teste
    DATA data1 = criar_data(1, 1, 1990);
    PESSOA pessoa1 = criar_pessoa("123.456.789-00", "Joao Silva", "01001-000", "01001-000", data1);
    mensagem_sucesso("Pessoa 'Joao Silva' criada com sucesso para teste!\n");
    
    DATA data2 = criar_data(15, 5, 1985);
    PESSOA pessoa2 = criar_pessoa("987.654.321-00", "Maria Santos", "01002-000", "01003-000", data2);
    mensagem_sucesso("Pessoa 'Maria Santos' criada com sucesso para teste!\n");
    
    DATA data3 = criar_data(30, 10, 1995);
    PESSOA pessoa3 = criar_pessoa("111.222.333-44", "Pedro Oliveira", "01003-000", "01002-000", data3);
    mensagem_sucesso("Pessoa 'Pedro Oliveira' criada com sucesso para teste!\n");
    
    // Testar cadastro de pessoas
    print_amarelo("Cadastrando pessoa: Joao Silva\n");
    RUBRO_NEGRO *resultado1 = cadastrar_pessoa(&raiz_pessoas, pessoa1);
    if (resultado1 != NULL) {
        mensagem_sucesso("Pessoa 'Joao Silva' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Joao Silva'!\n");
    }
    
    print_amarelo("Cadastrando pessoa: Maria Santos\n");
    RUBRO_NEGRO *resultado2 = cadastrar_pessoa(&raiz_pessoas, pessoa2);
    if (resultado2 != NULL) {
        mensagem_sucesso("Pessoa 'Maria Santos' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Maria Santos'!\n");
    }
    
    print_amarelo("Cadastrando pessoa: Pedro Oliveira\n");
    RUBRO_NEGRO *resultado3 = cadastrar_pessoa(&raiz_pessoas, pessoa3);
    if (resultado3 != NULL) {
        mensagem_sucesso("Pessoa 'Pedro Oliveira' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Pedro Oliveira'!\n");
    }
    
    // Tentativa de cadastrar pessoa duplicada (por CPF)
    print_amarelo("\nTentando cadastrar pessoa com CPF duplicado: 123.456.789-00\n");
    PESSOA pessoa_duplicada = criar_pessoa("123.456.789-00", "Joao Silva (duplicado)", "01001-000", "01001-000", data1);
    RUBRO_NEGRO *resultado_duplicado = cadastrar_pessoa(&raiz_pessoas, pessoa_duplicada);
    if (resultado_duplicado == NULL) {
        mensagem_sucesso("Cadastro de pessoa com CPF duplicado foi rejeitado corretamente!\n");
    } else if (resultado_duplicado == resultado1) {
        mensagem_sucesso("Pessoa existente foi atualizada corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar cadastrar pessoa com CPF duplicado!\n");
    }
    
    // Exibir pessoas cadastradas
    print_amarelo("\nPessoas cadastradas:\n");
    imprimir_rubro_negro(raiz_pessoas, imprimir_dados_pessoa);
    
    // Remover uma pessoa
    print_amarelo("\nRemovendo pessoa: Maria Santos (CPF: 987.654.321-00)\n");
    RUBRO_NEGRO *pessoa_removida = remover_pessoa(&raiz_pessoas, pessoa2, comparar_dados_CPF_pessoa);
    if (pessoa_removida != NULL) {
        mensagem_sucesso("Pessoa 'Maria Santos' removida com sucesso!\n");
        print_amarelo("Informacoes da pessoa removida:\n");
        imprimir_dados_pessoa(pessoa_removida->info);
        liberar_no_rubro_negro(&pessoa_removida, liberar_dados_pessoa);
    } else {
        mensagem_erro("Falha ao remover pessoa 'Maria Santos'!\n");
    }
    
    // Tentar remover uma pessoa inexistente
    print_amarelo("\nTentando remover pessoa com CPF inexistente: 000.000.000-00\n");
    DATA data_teste = criar_data(1, 1, 2000);
    PESSOA pessoa_inexistente = criar_pessoa("000.000.000-00", "Pessoa Inexistente", "01001-000", "01001-000", data_teste);
    RUBRO_NEGRO *pessoa_removida_inexistente = remover_pessoa(&raiz_pessoas, pessoa_inexistente, comparar_dados_CPF_pessoa);
    if (pessoa_removida_inexistente == NULL) {
        mensagem_sucesso("Tentativa de remover pessoa inexistente tratada corretamente!\n");
    } else {
        mensagem_erro("Comportamento inesperado ao tentar remover pessoa inexistente!\n");
        liberar_no_rubro_negro(&pessoa_removida_inexistente, liberar_dados_pessoa);
    }
    
    // Exibir pessoas após remoção
    print_amarelo("\nPessoas cadastradas após remoção:\n");
    imprimir_rubro_negro(raiz_pessoas, imprimir_dados_pessoa);
    
    // Liberar dados temporarios
    print_amarelo("\nLiberando dados temporarios...\n");
    liberar_pessoa(&pessoa_inexistente);
    
    // Liberar a arvore de pessoas
    print_amarelo("Liberando arvore de pessoas...\n");
    liberar_rubro_negro(&raiz_pessoas, liberar_dados_pessoa);
    if (raiz_pessoas == NULL) {
        mensagem_sucesso("Arvore de pessoas liberada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao liberar arvore de pessoas!\n");
    }
}

// Teste específico para remoção de CEP
void testar_remocao_CEP() {
    print_amarelo("\n=== TESTE DE REMOCAO DE CEPs ===\n");
    
    // Criar um estado e uma cidade para testar a remoção de CEPs
    ESTADO estado = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso para teste de remocao de CEP!\n");
    
    // Criar uma lista com o estado para usar nas funções
    LISTA_DUPLAMENTE *lista_estados = NULL;
    LISTA_DUPLAMENTE *estado_cadastrado = cadastrar_estado(&lista_estados, estado);
    if (estado_cadastrado == NULL) {
        mensagem_erro("Falha ao cadastrar estado em lista para teste de remocao de CEP!\n");
        return;
    }
    
    CIDADE cidade = criar_cidade("Sao Paulo", 12000000, NULL);
    RUBRO_NEGRO *cidade_cadastrada = cadastrar_cidade(&estado_cadastrado->estado, cidade);
    if (cidade_cadastrada == NULL) {
        mensagem_erro("Falha ao cadastrar cidade para teste de remocao de CEP!\n");
        liberar_lista(&lista_estados);
        return;
    }
    mensagem_sucesso("Cidade Sao Paulo cadastrada com sucesso para teste de remocao de CEP!\n");
    
    // Cadastrar múltiplos CEPs para testar remoção
    char ceps[5][10] = {"01001-000", "01002-000", "01003-000", "01004-000", "01005-000"};
    RUBRO_NEGRO *resultados[5];
    char mensagem_buffer[100]; // Buffer para mensagens formatadas
    
    print_amarelo("Cadastrando 5 CEPs para teste de remocao:\n");
    for (int i = 0; i < 5; i++) {
        resultados[i] = cadastrar_CEP(estado_cadastrado, &cidade_cadastrada->info.cidade, ceps[i]);
        if (resultados[i] != NULL) {
            // Usar sprintf para formatação antes de chamar mensagem_sucesso
            sprintf(mensagem_buffer, "CEP %s cadastrado com sucesso!\n", ceps[i]);
            mensagem_sucesso(mensagem_buffer);
        } else {
            // Usar sprintf para formatação antes de chamar mensagem_erro
            sprintf(mensagem_buffer, "Falha ao cadastrar o CEP %s!\n", ceps[i]);
            mensagem_erro(mensagem_buffer);
        }
    }
    
    // Exibir CEPs antes da remoção
    print_amarelo("\nCEPs cadastrados antes da remocao:\n");
    if (cidade_cadastrada->info.cidade.raiz_arvore_CEPs != NULL) {
        imprimir_rubro_negro(cidade_cadastrada->info.cidade.raiz_arvore_CEPs, imprimir_dados_CEP);
    } else {
        mensagem_erro("A raiz da arvore de CEPs esta vazia!\n");
    }
    
    // Teste de remoção de um CEP do meio
    print_amarelo("\nRemovendo CEP do meio: 01003-000\n");
    RUBRO_NEGRO *cep_removido_meio = remover_CEP(&cidade_cadastrada->info.cidade, "01003-000", comparar_dados_CEP);
    if (cep_removido_meio != NULL) {
        mensagem_sucesso("CEP 01003-000 removido com sucesso!\n");
        print_amarelo("Informacoes do CEP removido:\n");
        imprimir_dados_CEP(cep_removido_meio->info);
        liberar_no_rubro_negro(&cep_removido_meio, liberar_dados_CEP);
    } else {
        mensagem_erro("Falha ao remover o CEP 01003-000!\n");
    }
    
    // Verificar se o CEP foi realmente removido
    print_amarelo("\nVerificando se o CEP removido realmente nao existe mais:\n");
    short int existe_cep = verificar_se_existe_CEP(estado_cadastrado, "01003-000");
    if (!existe_cep) {
        mensagem_sucesso("CEP 01003-000 foi corretamente removido!\n");
    } else {
        mensagem_erro("CEP 01003-000 ainda existe na arvore (falha na remocao)!\n");
    }
    
    // Teste de remoção sequencial (remover todos os CEPs restantes)
    print_amarelo("\nRemovendo todos os CEPs restantes em sequencia:\n");
    char ceps_remover[4][10] = {"01001-000", "01002-000", "01004-000", "01005-000"};
    for (int i = 0; i < 4; i++) {
        // Usar sprintf para formatação
        sprintf(mensagem_buffer, "Removendo CEP: %s\n", ceps_remover[i]);
        print_amarelo(mensagem_buffer);
        
        RUBRO_NEGRO *cep_atual = remover_CEP(&cidade_cadastrada->info.cidade, ceps_remover[i], comparar_dados_CEP);
        if (cep_atual != NULL) {
            // Usar sprintf para formatação
            sprintf(mensagem_buffer, "CEP %s removido com sucesso!\n", ceps_remover[i]);
            mensagem_sucesso(mensagem_buffer);
            liberar_no_rubro_negro(&cep_atual, liberar_dados_CEP);
        } else {
            // Usar sprintf para formatação
            sprintf(mensagem_buffer, "Falha ao remover o CEP %s!\n", ceps_remover[i]);
            mensagem_erro(mensagem_buffer);
        }
    }
    
    // Verificar se a árvore está vazia após todas as remoções
    print_amarelo("\nVerificando se a arvore de CEPs esta vazia apos todas as remocoes:\n");
    if (cidade_cadastrada->info.cidade.raiz_arvore_CEPs == NULL) {
        mensagem_sucesso("Arvore de CEPs esta vazia como esperado!\n");
    } else {
        mensagem_erro("Arvore de CEPs nao esta vazia (deveria estar)!\n");
        print_amarelo("CEPs restantes na arvore:\n");
        imprimir_rubro_negro(cidade_cadastrada->info.cidade.raiz_arvore_CEPs, imprimir_dados_CEP);
    }
    
    // Liberar memória
    print_amarelo("\nLiberando memoria...\n");
    liberar_lista(&lista_estados);
    mensagem_sucesso("Memoria liberada com sucesso!\n");
}

// Função auxiliar para contar nós na árvore rubro-negra
int contar_nos_rubro_negro(RUBRO_NEGRO *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contar_nos_rubro_negro(raiz->esquerda) + contar_nos_rubro_negro(raiz->direita);
}

// Teste detalhado para cadastro de pessoa
void testar_cadastro_pessoa_detalhado() {
    print_amarelo("\n=== TESTE DETALHADO DE CADASTRO DE PESSOAS ===\n");
    
    // Criar árvore de pessoas
    RUBRO_NEGRO *raiz_pessoas = NULL;
    
    // Teste com diferentes tipos de pessoas (diferentes idades, CEPs, etc.)
    print_amarelo("Cadastrando pessoas com diferentes perfis:\n");
    
    // Pessoa jovem, mesmo CEP de residência e nascimento
    DATA data1 = criar_data(15, 5, 2000);
    PESSOA pessoa1 = criar_pessoa("111.111.111-11", "Ana Jovem", "01001-000", "01001-000", data1);
    
    // Pessoa de meia-idade, CEPs diferentes
    DATA data2 = criar_data(20, 8, 1980);
    PESSOA pessoa2 = criar_pessoa("222.222.222-22", "Bruno Meia-Idade", "02002-000", "03003-000", data2);
    
    // Pessoa idosa, CEPs diferentes
    DATA data3 = criar_data(10, 3, 1950);
    PESSOA pessoa3 = criar_pessoa("333.333.333-33", "Carlos Idoso", "04004-000", "05005-000", data3);
    
    // Pessoas com mesmo nome, mas CPFs diferentes
    DATA data4 = criar_data(5, 7, 1995);
    PESSOA pessoa4 = criar_pessoa("444.444.444-44", "Diana Silva", "06006-000", "07007-000", data4);
    
    DATA data5 = criar_data(12, 9, 1992);
    PESSOA pessoa5 = criar_pessoa("555.555.555-55", "Diana Silva", "08008-000", "09009-000", data5);
    
    // Cadastrar pessoas
    mensagem_sucesso("Pessoas criadas com sucesso para teste!\n");
    
    // Teste de cadastro 1
    print_amarelo("\nCadastrando pessoa jovem (Ana):\n");
    RUBRO_NEGRO *resultado1 = cadastrar_pessoa(&raiz_pessoas, pessoa1);
    if (resultado1 != NULL) {
        mensagem_sucesso("Pessoa 'Ana Jovem' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Ana Jovem'!\n");
    }
    
    // Teste de cadastro 2
    print_amarelo("\nCadastrando pessoa de meia-idade (Bruno):\n");
    RUBRO_NEGRO *resultado2 = cadastrar_pessoa(&raiz_pessoas, pessoa2);
    if (resultado2 != NULL) {
        mensagem_sucesso("Pessoa 'Bruno Meia-Idade' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Bruno Meia-Idade'!\n");
    }
    
    // Teste de cadastro 3
    print_amarelo("\nCadastrando pessoa idosa (Carlos):\n");
    RUBRO_NEGRO *resultado3 = cadastrar_pessoa(&raiz_pessoas, pessoa3);
    if (resultado3 != NULL) {
        mensagem_sucesso("Pessoa 'Carlos Idoso' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar pessoa 'Carlos Idoso'!\n");
    }
    
    // Teste de cadastro de pessoas com mesmo nome
    print_amarelo("\nCadastrando duas pessoas com mesmo nome (Diana Silva):\n");
    RUBRO_NEGRO *resultado4 = cadastrar_pessoa(&raiz_pessoas, pessoa4);
    if (resultado4 != NULL) {
        mensagem_sucesso("Primeira 'Diana Silva' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar primeira 'Diana Silva'!\n");
    }
    
    RUBRO_NEGRO *resultado5 = cadastrar_pessoa(&raiz_pessoas, pessoa5);
    if (resultado5 != NULL) {
        mensagem_sucesso("Segunda 'Diana Silva' cadastrada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao cadastrar segunda 'Diana Silva'!\n");
    }
    
    // Imprimindo as pessoas cadastradas
    print_amarelo("\nPessoas cadastradas (ordenadas por CPF):\n");
    imprimir_rubro_negro(raiz_pessoas, imprimir_dados_pessoa);
    
    // Verificar número de nós na árvore
    print_amarelo("\nVerificando numero de pessoas na arvore:\n");
    int numero_pessoas = contar_nos_rubro_negro(raiz_pessoas);
    
    // Usar sprintf para formatação
    char mensagem_buffer[100];
    sprintf(mensagem_buffer, "Numero de pessoas na arvore: %d (esperado: 5)\n", numero_pessoas);
    mensagem_sucesso(mensagem_buffer);
    
    // Liberar a árvore de pessoas
    print_amarelo("\nLiberando arvore de pessoas...\n");
    liberar_rubro_negro(&raiz_pessoas, liberar_dados_pessoa);
    if (raiz_pessoas == NULL) {
        mensagem_sucesso("Arvore de pessoas liberada com sucesso!\n");
    } else {
        mensagem_erro("Falha ao liberar arvore de pessoas!\n");
    }
}

int main() {
    limpar_tela();
    print_amarelo("=== TESTES DE FUNCOES DE CADASTRO E REMOCAO ===\n");
    
    testar_cadastrar_estado();
    
    pausar_tela();
    limpar_tela();
    
    testar_cadastrar_cidade();
    
    pausar_tela();
    limpar_tela();
    
    testar_cadastrar_CEP();
    
    pausar_tela();
    limpar_tela();
    
    // Adicionar os novos testes
    testar_remocao_CEP();
    
    pausar_tela();
    limpar_tela();
    
    testar_cadastro_pessoa_detalhado();
    
    pausar_tela();
    limpar_tela();
    
    testar_cadastrar_remover_pessoas();
    
    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");
    
    return 0;
}
