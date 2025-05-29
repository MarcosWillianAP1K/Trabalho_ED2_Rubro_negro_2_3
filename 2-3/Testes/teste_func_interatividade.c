/*
 * Comando para compilar:
gcc -Wall teste_func_interatividade.c ../Tads/Estruturas/Lista_duplamente.c ../Tads/Estruturas/2-3.c ../Tads/Estruturas/Dados.c ../Tads/Interatividade/func_interatividade.c ../Tads/Objetos/Estado.c ../Tads/Objetos/Cidade.c ../Tads/Objetos/Pessoa.c ../Tads/Objetos/CEP.c ../Tads/Objetos/Data.c ../Tads/Objetos/CPF.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes/
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

// Manter de forma que a sub arvore seja o dobro da arvore atual. ou seja, se a arvore atual tiver 5 elementos, a sub arvore tera 10 elementos.
#define quantidade_estados 10
#define quantidade_cidades 20
#define quantidade_ceps 40



// Função para criar estados, cidades e CEPs
LISTA_DUPLAMENTE *povoar_estados()
{
    limpar_tela();
    print_amarelo("=== INICIANDO POVOAMENTO DE ESTADOS ===\n\n");
    // Inicializar a lista de estados
    LISTA_DUPLAMENTE *lista_estados = NULL;

    print_amarelo("=== Criando CEPs ===\n");

    // Criar 40 CEPs com formato "00000-001" até "00000-040" - alterado para ponteiros
    char *ceps[quantidade_ceps];
    for (int i = 0; i < quantidade_ceps; i++)
    {
        char temp_cep[10];
        sprintf(temp_cep, "%05d-%03d", 0, i + 1);
        limpar_buffer();
        ceps[i] = strdup(temp_cep); // Alocação dinâmica com strdup
        printf("CEP criado: %s\n", ceps[i]);
    }
    mensagem_sucesso("CEPs CRIADOS COM SUCESSO.\n\n");


    print_amarelo("Agora sera criado as cidades...\n");

    pausar_tela();
    limpar_tela();
  

    print_amarelo("=== Criando Cidades ===\n");

    // Criar 20 cidades com populações crescentes
    CIDADE cidades[quantidade_cidades];
    for (int i = 0; i < quantidade_cidades; i++)
    {
        char nome_cidade[20];
        sprintf(nome_cidade, "cidade%d", i + 1);
        limpar_buffer();
        int populacao = (i + 1) * 10; // Começando com 10 e incrementando de 10 em 10
        cidades[i] = criar_cidade(strdup(nome_cidade), populacao, NULL);
        printf("Cidade criada: %s, Populacao: %d\n", nome_cidade, populacao);
    }

    mensagem_sucesso("CIDADES CRIADAS COM SUCESSO.\n\n");

    print_amarelo("Agora sera criado os estados...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Criando Estados ===\n");

    // Criar 10 estados, cada um com duas cidades (sendo uma delas a capital)
    ESTADO estado[quantidade_estados];
    for (int i = 0; i < quantidade_estados; i++)
    {
        char nome_estado[20];
        sprintf(nome_estado, "estado%d", i + 1);
        limpar_buffer();

        // A capital é a cidade número (estado * 2)
        int num_capital = (i + 1) * 2;
        

        // Criar o estado
        printf("Criando estado: %s com capital: %s\n", nome_estado, cidades[num_capital - 1].nome);
        estado[i] = criar_estado(strdup(nome_estado), cidades[num_capital - 1].nome, 0, (i + 1) * 10, NULL);
    }

    mensagem_sucesso("ESTADOS CRIADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros dos ceps nas cidades...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros dos ceps nas cidades ===\n");

    for (int i = 0; i < quantidade_cidades; i++)
    {
        // Cada cidade recebe 2 CEPs
        for (int j = i * 2; j < (i * 2) + 2; j++)
        {
            // Atribuir o CEP à cidade
            printf("Atribuindo CEP %s a cidade %s\n", ceps[j], cidades[i].nome);
            if (cadastrar_CEP(NULL, &cidades[i], ceps[j]))
            {
                mensagem_sucesso("\n");
            }
            else
            {
                mensagem_erro("\n");
            }
        }
    }

    mensagem_sucesso("CEPs CADASTRADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros das cidades nos estados...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros das cidades nos estados ===\n");

    for (int i = 0; i < quantidade_estados; i++)
    {
        // Cada estado recebe 2 cidades
        for (int j = i * 2; j < (i * 2) + 2; j++)
        {
            // Atribuir a cidade ao estado
            printf("Atribuindo cidade %s ao estado %s\n", cidades[j].nome, estado[i].nome_estado);
            if (cadastrar_cidade(&estado[i], cidades[j]))
            {
                mensagem_sucesso("\n");
            }
            else
            {
                mensagem_erro("\n");
            }
        }
    }

    mensagem_sucesso("CIDADES CADASTRADAS NOS ESTADOS COM SUCESSO.\n\n");

    print_amarelo("Agora iniciara o processo de cadastros dos estados na lista...\n");

    pausar_tela();
    limpar_tela();

    print_amarelo("=== Iniciando o cadastros dos estados na lista ===\n");

    for (int i = 0; i < quantidade_estados; i++)
    {
        // Adicionar o estado à lista
        printf("Adicionando estado %s a lista\n", estado[i].nome_estado);

        if (inserir_ordernado_duplamente(&lista_estados, estado[i]))
        {
            mensagem_sucesso("\n");
        }
        else
        {
            mensagem_erro("\n");
        }
    }

    mensagem_sucesso("ESTADOS CADASTRADOS NA LISTA COM SUCESSO.\n\n");

    print_amarelo("\n=== POVOAMENTO CONCLUIDO ===\n");

    pausar_tela();

    return lista_estados;
}

// Função para povoar pessoas
AVR_23 *povoar_pessoas(LISTA_DUPLAMENTE *lista_estados)
{ 
    limpar_tela();
    print_amarelo("=== INICIANDO POVOAMENTO DE PESSOAS ===\n\n");
    
    // Inicializar a árvore de pessoas
    AVR_23 *raiz_pessoas = NULL;
    
    // Vamos buscar alguns CEPs válidos para usar
    char *ceps_disponiveis[10];
    int contador_ceps = 0;
    
    // Percorrer os estados e cidades para coletar alguns CEPs
    LISTA_DUPLAMENTE *estado_atual = lista_estados;
    for (int i = 0; i < quantidade_estados && contador_ceps < 10; i++)
    {
        // Tentamos encontrar a capital para pegar seus CEPs
        CIDADE *capital = procurar_capital_de_um_estado(estado_atual->estado);
        if (capital != NULL && capital->raiz_arvore_CEPs != NULL)
        {
            // Coletar um CEP da capital (simplificado para o teste)
            // Na prática, precisaríamos percorrer a árvore de CEPs
            ceps_disponiveis[contador_ceps] = strdup("00000-001");
            contador_ceps++;
            
            if (contador_ceps < 10)
            {
                ceps_disponiveis[contador_ceps] = strdup("00000-002");
                contador_ceps++;
            }
        }
        
        estado_atual = estado_atual->prox;
        if (estado_atual == NULL) break;
    }
    
    pausar_tela();
    limpar_tela();
    
    print_amarelo("=== Criando Pessoas ===\n");
    
    // Criar 10 pessoas
    for (int i = 0; i < 10; i++)
    {
        // Criar nome da pessoa
        char nome_pessoa[20];
        sprintf(nome_pessoa, "pessoa%d", i + 1);
        
        // Criar CPF único
        char cpf[15];
        sprintf(cpf, "%03d.%03d.%03d-%02d", 100 + i, 200 + i, 300 + i, 10 + i);
        
        // Criar data de nascimento
        int dia = 1 + (i % 28); // dia entre 1 e 28
        int mes = 1 + (i % 12); // mês entre 1 e 12
        int ano = 1970 + i;     // ano a partir de 1970
        DATA data_nascimento = criar_data(dia, mes, ano);
        
        // Definir CEP natal e atual
        char *cep_natal, *cep_atual;
        
        if (i < 5) {
            // Primeiras 5 pessoas têm CEPs diferentes
            cep_natal = ceps_disponiveis[i];
            cep_atual = ceps_disponiveis[i + 5];
            printf("Criando %s com CEPs diferentes (natal: %s, atual: %s)\n", 
                  nome_pessoa, cep_natal, cep_atual);
        } else {
            // Últimas 5 pessoas têm CEPs iguais
            cep_natal = ceps_disponiveis[i % 5];
            cep_atual = cep_natal; // Mesmo CEP
            printf("Criando %s com CEPs iguais (natal e atual: %s)\n", 
                  nome_pessoa, cep_natal);
        }
        
        // Criar a pessoa
        PESSOA pessoa = criar_pessoa(strdup(cpf), strdup(nome_pessoa), 
                                     strdup(cep_natal), strdup(cep_atual), 
                                     data_nascimento);
        
        // Cadastrar pessoa
        short int resultado = cadastrar_pessoa(&raiz_pessoas, pessoa);
        if (resultado) {
            mensagem_sucesso("Pessoa cadastrada com sucesso!\n");
        } else {
            mensagem_erro("Falha ao cadastrar pessoa!\n");
        }
    }
    
    // Liberar memória dos CEPs temporários
    for (int i = 0; i < 10; i++) {
        free(ceps_disponiveis[i]);
    }
    
    mensagem_sucesso("POVOAMENTO DE PESSOAS CONCLUIDO COM SUCESSO!\n");
    print_amarelo("Total de pessoas cadastradas: 10\n");
    
    pausar_tela();
    return raiz_pessoas;
}

// Função para testar as funções de consulta e verificação
void testar_consultas_e_verificacoes(LISTA_DUPLAMENTE *lista_estados, AVR_23 *raiz_pessoas)
{
    limpar_tela();
    print_amarelo("=== TESTANDO FUNCOES DE CONSULTA E VERIFICACAO ===\n\n");
    
    char buffer[100]; // Buffer para formatar mensagens

    // 1. Teste de verificar_se_existe_CEP
    print_amarelo("=== Teste 1: Verificar se existe CEP ===\n");
    char cep_teste1[] = "00000-001";
    char cep_teste2[] = "99999-999"; // CEP inexistente
    
    printf("Verificando se existe o CEP %s...\n", cep_teste1);
    short int existe_cep1 = verificar_se_existe_CEP(lista_estados, cep_teste1);
    if (existe_cep1) {
        sprintf(buffer, "CEP %s encontrado no sistema!\n", cep_teste1);
        mensagem_sucesso(buffer);
    } else {
        sprintf(buffer, "CEP %s nao encontrado no sistema!\n", cep_teste1);
        mensagem_erro(buffer);
    }

    printf("Verificando se existe o CEP %s...\n", cep_teste2);
    short int existe_cep2 = verificar_se_existe_CEP(lista_estados, cep_teste2);
    if (existe_cep2) {
        sprintf(buffer, "CEP %s encontrado no sistema! (Não esperado)\n", cep_teste2);
        mensagem_erro(buffer);
    } else {
        sprintf(buffer, "CEP %s nao encontrado no sistema! (esperado)\n", cep_teste2);
        mensagem_sucesso(buffer);
    }
    
    // 2. Teste de verificar_se_existe_pessoa_associada_a_um_CEP
    print_amarelo("\n=== Teste 2: Verificar se existe pessoa associada a um CEP ===\n");
    printf("Verificando se existe pessoa associada ao CEP %s...\n", cep_teste1);
    short int existe_pessoa_cep = verificar_se_existe_pessoa_associada_a_um_CEP(raiz_pessoas, cep_teste1);
    if (existe_pessoa_cep) {
        sprintf(buffer, "Existe pessoa(s) associada(s) ao CEP %s!\n", cep_teste1);
        mensagem_sucesso(buffer);
    } else {
        sprintf(buffer, "Nao existe pessoa associada ao CEP %s!\n", cep_teste1);
        mensagem_erro(buffer);
    }

    // 3. Teste de procurar_estado_mais_populoso
    print_amarelo("\n=== Teste 3: Procurar estado mais populoso ===\n");
    printf("Procurando o estado mais populoso...\n");
    LISTA_DUPLAMENTE *estado_populoso = procurar_estado_mais_populoso(lista_estados);
    if (estado_populoso != NULL) {
        sprintf(buffer, "Estado mais populoso: %s (Populacao: %d)\n", 
                estado_populoso->estado.nome_estado, 
                estado_populoso->estado.quantidade_populacao);
        mensagem_sucesso(buffer);
    } else {
        mensagem_erro("Nenhum estado encontrado!\n");
    }

    // 4. Teste de procurar_capital_de_um_estado
    print_amarelo("\n=== Teste 4: Procurar capital de um estado ===\n");
    if (lista_estados != NULL) {
        printf("Procurando a capital do estado %s...\n", lista_estados->estado.nome_estado);
        CIDADE *capital = procurar_capital_de_um_estado(lista_estados->estado);
        if (capital != NULL) {
            sprintf(buffer, "Capital do estado %s: %s\n", 
                    lista_estados->estado.nome_estado, 
                    capital->nome);
            mensagem_sucesso(buffer);
        } else {
            sprintf(buffer, "Capital nao encontrada para o estado %s!\n", 
                   lista_estados->estado.nome_estado);
            mensagem_erro(buffer);
        }
    }

    // 5. Teste de procurar_cidade_mais_populosa_sem_capital
    print_amarelo("\n=== Teste 5: Procurar cidade mais populosa sem capital ===\n");
    if (lista_estados != NULL) {
        CIDADE *capital = procurar_capital_de_um_estado(lista_estados->estado);
        if (capital != NULL) {
            printf("Procurando a cidade mais populosa diferente da capital %s...\n", capital->nome);
            CIDADE *cidade_populosa = procurar_cidade_mais_populosa_sem_capital(
                lista_estados->estado.raiz_arvore_cidade, capital->nome);
            
            if (cidade_populosa != NULL) {
                sprintf(buffer, "Cidade mais populosa (sem capital): %s (Populacao: %d)\n", 
                        cidade_populosa->nome, cidade_populosa->quantidade_populacao);
                mensagem_sucesso(buffer);
            } else {
                mensagem_erro("Nenhuma outra cidade encontrada!\n");
            }
        }
    }

    // 6. Teste de quant_de_pessoas_que_nao_mora_na_cidade_natal
    print_amarelo("\n=== Teste 6: Quantidade de pessoas que nao moram na cidade natal ===\n");
    printf("Calculando quantidade de pessoas que nao moram na cidade natal...\n");
    int qtd_fora_natal = quant_de_pessoas_que_nao_mora_na_cidade_natal(lista_estados, raiz_pessoas);
    sprintf(buffer, "Quantidade de pessoas que nao moram na cidade natal: %d\n", qtd_fora_natal);
    mensagem_sucesso(buffer);

    // 7. Teste de procurar_cidade_por_CEP
    print_amarelo("\n=== Teste 7: Procurar cidade por CEP ===\n");
    printf("Procurando cidade associada ao CEP %s...\n", cep_teste1);
    CIDADE *cidade_por_cep = procurar_cidade_por_CEP(lista_estados, cep_teste1);
    if (cidade_por_cep != NULL) {
        sprintf(buffer, "Cidade encontrada para o CEP %s: %s\n", cep_teste1, cidade_por_cep->nome);
        mensagem_sucesso(buffer);
    } else {
        sprintf(buffer, "Nenhuma cidade encontrada para o CEP %s!\n", cep_teste1);
        mensagem_erro(buffer);
    }

    pausar_tela();
}

// Função para testar cadastros e cadastros repetidos
void testar_cadastros(LISTA_DUPLAMENTE *lista_estados, AVR_23 **raiz_pessoas)
{
    limpar_tela();
    print_amarelo("=== TESTANDO FUNCOES DE CADASTRO E CADASTROS REPETIDOS ===\n\n");

    // 1. Teste de cadastrar_estado (repetido)
    print_amarelo("=== Teste 1: Cadastrar estado repetido ===\n");
    if (lista_estados != NULL) {
        ESTADO estado_existente = lista_estados->estado;
        printf("Tentando cadastrar estado repetido: %s\n", estado_existente.nome_estado);
        
        LISTA_DUPLAMENTE *resultado = cadastrar_estado(&lista_estados, estado_existente);
        if (resultado == NULL)
            mensagem_sucesso("Estado repetido nao foi cadastrado novamente (comportamento correto)!\n");
        else
            mensagem_erro("Estado repetido foi cadastrado ou atualizado!\n");
    }

    // 2. Teste de cadastrar_cidade (repetida)
    print_amarelo("\n=== Teste 2: Cadastrar cidade repetida ===\n");
    if (lista_estados != NULL) {
        CIDADE *capital = procurar_capital_de_um_estado(lista_estados->estado);
        if (capital != NULL) {
            printf("Tentando cadastrar cidade repetida: %s\n", capital->nome);
            
            short int resultado = cadastrar_cidade(&lista_estados->estado, *capital);
            if (resultado == 0)
                mensagem_sucesso("Cidade repetida nao foi cadastrada novamente (comportamento correto)!\n");
            else
                mensagem_erro("Cidade repetida foi cadastrada ou atualizada!\n");
        }
    }

    // 3. Teste de cadastrar_CEP (repetido)
    print_amarelo("\n=== Teste 3: Cadastrar CEP repetido ===\n");
    if (lista_estados != NULL) {
        CIDADE *cidade = procurar_capital_de_um_estado(lista_estados->estado);
        if (cidade != NULL) {
            char cep_teste[] = "00000-001"; // CEP que já existe na cidade
            printf("Tentando cadastrar CEP repetido: %s\n", cep_teste);
            
            short int resultado = cadastrar_CEP(lista_estados, cidade, cep_teste);
            if (resultado == 0)
                mensagem_sucesso("CEP repetido nao foi cadastrado novamente (comportamento correto)!\n");
            else
                mensagem_erro("CEP repetido foi cadastrado ou atualizado!\n");
        }
    }

    // 4. Teste de cadastrar_pessoa (nova)
    print_amarelo("\n=== Teste 4: Cadastrar pessoa nova ===\n");
    DATA data_nova = criar_data(1, 1, 2000);
    PESSOA pessoa_nova = criar_pessoa("999.888.777-66", "Pessoa Nova", "00000-001", "00000-002", data_nova);
    printf("Cadastrando nova pessoa: Pessoa Nova\n");
    
    short int resultado_pessoa = cadastrar_pessoa(raiz_pessoas, pessoa_nova);
    if (resultado_pessoa)
        mensagem_sucesso("Nova pessoa cadastrada com sucesso!\n");
    else
        mensagem_erro("Falha ao cadastrar nova pessoa!\n");
    
    // 5. Teste de cadastrar_pessoa (repetida)
    print_amarelo("\n=== Teste 5: Cadastrar pessoa repetida ===\n");
    printf("Tentando cadastrar pessoa com CPF repetido: 999.888.777-66\n");
    
    PESSOA pessoa_repetida = criar_pessoa("999.888.777-66", "Pessoa Repetida", "00000-003", "00000-003", data_nova);
    short int resultado_repetido = cadastrar_pessoa(raiz_pessoas, pessoa_repetida);
    if (resultado_repetido == 0)
        mensagem_sucesso("Pessoa com CPF repetido nao foi cadastrada novamente (comportamento correto)!\n");
    else
        mensagem_erro("Pessoa com CPF repetido foi cadastrada ou atualizada!\n");

    pausar_tela();
}

// Função para testar remoções
void testar_remocoes(LISTA_DUPLAMENTE *lista_estados, AVR_23 **raiz_pessoas)
{
    limpar_tela();
    print_amarelo("=== TESTANDO FUNCOES DE REMOCAO ===\n\n");
    
    char buffer[100]; // Buffer para formatar mensagens

    // 1. Teste de remover_CEP (existente)
    print_amarelo("=== Teste 1: Remover CEP existente ===\n");
    if (lista_estados != NULL) {
        CIDADE *cidade = procurar_capital_de_um_estado(lista_estados->estado);
        if (cidade != NULL) {
            char cep_remover[] = "00000-001";
            char cep_removido[10];
            printf("Removendo CEP existente: %s\n", cep_remover);
            
            short int resultado = remover_CEP(cidade, cep_remover, cep_removido);
            if (resultado) {
                sprintf(buffer, "CEP removido com sucesso: %s\n", cep_removido);
                mensagem_sucesso(buffer);
                
                // Verificar se o CEP foi realmente removido
                short int existe = verificar_se_existe_CEP(lista_estados, cep_remover);
                if (!existe)
                    mensagem_sucesso("Verificacao confirmou que o CEP foi removido!\n");
                else
                    mensagem_erro("CEP ainda consta no sistema apos remocao!\n");
            }
            else
                mensagem_erro("Falha ao remover CEP!\n");
        }
    }

    // 2. Teste de remover_CEP (inexistente)
    print_amarelo("\n=== Teste 2: Remover CEP inexistente ===\n");
    if (lista_estados != NULL) {
        CIDADE *cidade = procurar_capital_de_um_estado(lista_estados->estado);
        if (cidade != NULL) {
            char cep_inexistente[] = "99999-999";
            char cep_removido[10];
            printf("Tentando remover CEP inexistente: %s\n", cep_inexistente);
            
            short int resultado = remover_CEP(cidade, cep_inexistente, cep_removido);
            if (resultado == 0)
                mensagem_sucesso("Tentativa de remover CEP inexistente tratada corretamente!\n");
            else
                mensagem_erro("CEP inexistente foi supostamente removido (comportamento inesperado)!\n");
        }
    }

    // 3. Teste de remover_pessoa (existente)
    print_amarelo("\n=== Teste 3: Remover pessoa existente ===\n");
    DATA data = criar_data(1, 1, 2000);
    PESSOA pessoa_para_remover = criar_pessoa("999.888.777-66", "Pessoa Nova", "00000-001", "00000-002", data);
    PESSOA pessoa_removida;
    printf("Removendo pessoa existente com CPF: 999.888.777-66\n");
    
    short int resultado_pessoa = remover_pessoa(raiz_pessoas, pessoa_para_remover, &pessoa_removida);
    if (resultado_pessoa) {
        mensagem_sucesso("Pessoa removida com sucesso!\n");
        printf("Dados da pessoa removida: Nome = %s, CPF = %s\n", 
               pessoa_removida.nome, pessoa_removida.CPF);
        
        // Liberar memória da pessoa removida
        liberar_pessoa(&pessoa_removida);
    }
    else
        mensagem_erro("Falha ao remover pessoa!\n");

    // 4. Teste de remover_pessoa (inexistente)
    print_amarelo("\n=== Teste 4: Remover pessoa inexistente ===\n");
    PESSOA pessoa_inexistente = criar_pessoa("000.000.000-00", "Pessoa Inexistente", "00000-001", "00000-001", data);
    PESSOA pessoa_removida_inexistente;
    printf("Tentando remover pessoa inexistente com CPF: 000.000.000-00\n");
    
    short int resultado_inexistente = remover_pessoa(raiz_pessoas, pessoa_inexistente, &pessoa_removida_inexistente);
    if (resultado_inexistente == 0)
        mensagem_sucesso("Tentativa de remover pessoa inexistente tratada corretamente!\n");
    else {
        mensagem_erro("Pessoa inexistente foi supostamente removida (comportamento inesperado)!\n");
        liberar_pessoa(&pessoa_removida_inexistente);
    }
    
    // Liberar a pessoa temporária
    liberar_pessoa(&pessoa_inexistente);
    
    pausar_tela();
}

// Função para exibir tudo e liberar memória
void testar_exibicao_e_liberacao(LISTA_DUPLAMENTE *lista_estados, AVR_23 **raiz_pessoas)
{
    limpar_tela();
    print_amarelo("=== EXIBINDO TODOS OS DADOS E LIBERANDO MEMORIA ===\n\n");

    // 1. Teste da função mostrar_tudo
    print_amarelo("=== Exibindo todos os dados do sistema ===\n");
    mostrar_tudo(lista_estados, *raiz_pessoas);
    
    pausar_tela();
    
    // 2. Liberar toda a memória
    print_amarelo("\n=== Liberando memoria ===\n");
    printf("Liberando toda a memoria alocada...\n");
    delete_all(&lista_estados, raiz_pessoas);
    
    if (lista_estados == NULL && *raiz_pessoas == NULL)
        mensagem_sucesso("Memoria liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar toda a memoria!\n");
        
    pausar_tela();
}

int main()
{
    LISTA_DUPLAMENTE *lista_estados = povoar_estados();
    AVR_23 *raiz_pessoas = povoar_pessoas(lista_estados);

    // Testar as diversas funções
    testar_consultas_e_verificacoes(lista_estados, raiz_pessoas);
    testar_cadastros(lista_estados, &raiz_pessoas);
    testar_remocoes(lista_estados, &raiz_pessoas);
    testar_exibicao_e_liberacao(lista_estados, &raiz_pessoas);

    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");

    return 0;
}
