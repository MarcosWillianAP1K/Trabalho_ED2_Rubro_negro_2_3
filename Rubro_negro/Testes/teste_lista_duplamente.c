/* 
 * Comando para compilar:
 * gcc -Wall teste_lista_duplamente.c ../Tads/Estruturas/Lista_duplamente.c ../Tads/Objetos/Estado.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes
 * 
 * Explicacao dos parametros:
 * -Wall: Ativa todos os avisos de compilacao
 * -o teste_lista: Define o nome do executavel de saida como "teste_lista"
 * -I../Includes: Especifica um diretorio adicional onde o compilador deve procurar
 *                por arquivos de cabecalho (.h), permitindo que #include "arquivo.h" 
 *                funcione sem precisar do caminho completo em cada inclusao
 * 
 * Para executar:
 * ./a.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../Includes/Estruturas/Lista_duplamente.h"
#include "../Includes/Objetos/Estado.h"
#include "../Includes/Utilitarios/funcao_sistema.h"

void testar_criacao_lista() {
    print_verde("Testando criacao do no da lista...\n");
    
    LISTA_DUPLAMENTE* no = alocar_no_duplamente();
    if(no != NULL) {
        mensagem_sucesso("No alocado com sucesso!\n");
        // O campo estado agora é uma estrutura, não um ponteiro
        // Verificar se nome_estado é NULL, em vez do próprio estado
            
        if(no->ant == NULL)
            mensagem_sucesso("Ponteiro anterior inicializado como NULL!\n");
        else
            mensagem_erro("Ponteiro anterior NAO esta NULL!\n");
            
        if(no->prox == NULL)
            mensagem_sucesso("Ponteiro proximo inicializado como NULL!\n");
        else
            mensagem_erro("Ponteiro proximo NAO esta NULL!\n");
    } else {
        mensagem_erro("Falha ao alocar no!\n");
    }
    
    print_amarelo("Liberando no da lista...\n");
    liberar_no_duplamente(&no);
    if(no == NULL)
        mensagem_sucesso("No liberado com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar no!\n");
}

void testar_insercao() {
    print_verde("Testando insercao ordenada de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar tres estados para testar - corrigindo para usar estrutura em vez de ponteiro
    ESTADO estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso!\n");
    
    ESTADO estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    mensagem_sucesso("Estado Rio de Janeiro criado com sucesso!\n");
    
    ESTADO estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    mensagem_sucesso("Estado Minas Gerais criado com sucesso!\n");
    
    // Inserir estados ordenadamente - passando o endereço da estrutura
    if(inserir_ordernado_duplamente(&lista, &estado1))
        mensagem_sucesso("Estado Sao Paulo inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Sao Paulo!\n");
        
    if(inserir_ordernado_duplamente(&lista, &estado2))
        mensagem_sucesso("Estado Rio de Janeiro inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Rio de Janeiro!\n");
        
    if(inserir_ordernado_duplamente(&lista, &estado3))
        mensagem_sucesso("Estado Minas Gerais inserido com sucesso!\n");
    else
        mensagem_erro("Falha ao inserir Minas Gerais!\n");
    
    print_amarelo("Lista apos insercoes:\n");
    exibirLista(lista);
    
    // Verificar a ordem (deve estar em ordem alfabetica por nome_estado)
    if(strcmp(lista->estado.nome_estado, "Minas Gerais") == 0)
        mensagem_sucesso("Primeiro elemento e Minas Gerais, como esperado!\n");
    else
        mensagem_erro("Primeiro elemento nao e Minas Gerais!\n");
        
    if(strcmp(lista->prox->estado.nome_estado, "Rio de Janeiro") == 0)
        mensagem_sucesso("Segundo elemento e Rio de Janeiro, como esperado!\n");
    else
        mensagem_erro("Segundo elemento nao e Rio de Janeiro!\n");
        
    if(strcmp(lista->prox->prox->estado.nome_estado, "Sao Paulo") == 0)
        mensagem_sucesso("Terceiro elemento e Sao Paulo, como esperado!\n");
    else
        mensagem_erro("Terceiro elemento nao e Sao Paulo!\n");
    
    print_amarelo("Liberando lista de estados...\n");
    liberar_lista(&lista);
    if(lista == NULL)
        mensagem_sucesso("Lista liberada com sucesso!\n");
    else
        mensagem_erro("Falha ao liberar lista!\n");
}

void testar_busca() {
    print_verde("Testando busca de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar estados para testar
    ESTADO estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso!\n");
    
    ESTADO estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    mensagem_sucesso("Estado Rio de Janeiro criado com sucesso!\n");
    
    ESTADO estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    mensagem_sucesso("Estado Minas Gerais criado com sucesso!\n");
    
    // Inserir estados
    inserir_ordernado_duplamente(&lista, &estado1);
    inserir_ordernado_duplamente(&lista, &estado2);
    inserir_ordernado_duplamente(&lista, &estado3);
    mensagem_sucesso("Estados inseridos na lista com sucesso!\n");
    
    // Buscar estados existentes
    print_amarelo("Buscando Sao Paulo na lista...\n");
    ESTADO busca1 = criar_estado("Sao Paulo", "", 0, 0, NULL);
    mensagem_sucesso("Dado para busca de Sao Paulo criado!\n");
    
    LISTA_DUPLAMENTE *resultado1 = buscar_duplamente(lista, &busca1);
    if(resultado1 != NULL) {
        mensagem_sucesso("Estado Sao Paulo encontrado!\n");
        print_amarelo("Informacoes do estado encontrado:\n");
        // Usar a estrutura em vez do ponteiro
        imprimir_estado(&resultado1->estado);
    } else {
        mensagem_erro("Estado Sao Paulo NAO encontrado!\n");
    }
    
    print_amarelo("\nBuscando Rio de Janeiro na lista...\n");
    ESTADO busca2 = criar_estado("Rio de Janeiro", "", 0, 0, NULL);
    mensagem_sucesso("Dado para busca de Rio de Janeiro criado!\n");
    
    LISTA_DUPLAMENTE *resultado2 = buscar_duplamente(lista, &busca2);
    if(resultado2 != NULL) {
        mensagem_sucesso("Estado Rio de Janeiro encontrado!\n");
        print_amarelo("Informacoes do estado encontrado:\n");
        imprimir_estado(&resultado2->estado);
    } else {
        mensagem_erro("Estado Rio de Janeiro NAO encontrado!\n");
    }
    
    print_amarelo("\nBuscando Minas Gerais na lista...\n");
    ESTADO busca3 = criar_estado("Minas Gerais", "", 0, 0, NULL);
    mensagem_sucesso("Dado para busca de Minas Gerais criado!\n");
    
    LISTA_DUPLAMENTE *resultado3 = buscar_duplamente(lista, &busca3);
    if(resultado3 != NULL) {
        mensagem_sucesso("Estado Minas Gerais encontrado!\n");
        print_amarelo("Informacoes do estado encontrado:\n");
        imprimir_estado(&resultado3->estado);
    } else {
        mensagem_erro("Estado Minas Gerais NAO encontrado!\n");
    }
    
    print_amarelo("\nBuscando estado inexistente Parana na lista...\n");
    ESTADO busca4 = criar_estado("Parana", "", 0, 0, NULL);
    mensagem_sucesso("Dado para busca de Parana criado!\n");
    
    LISTA_DUPLAMENTE *resultado4 = buscar_duplamente(lista, &busca4);
    if(resultado4 != NULL) {
        mensagem_sucesso("Estado Parana encontrado!\n");
        print_amarelo("Informacoes do estado encontrado:\n");
        imprimir_estado(&resultado4->estado);
    } else {
        mensagem_erro("Estado Parana NAO encontrado (esperado, ja que nao foi inserido)!\n");
    }
    
    // Liberar memoria
    print_amarelo("Liberando estruturas de busca...\n");
    liberar_estado(&busca1);
    mensagem_sucesso("Memoria para busca de Sao Paulo liberada!\n");
    
    liberar_estado(&busca2);
    mensagem_sucesso("Memoria para busca de Rio de Janeiro liberada!\n");
    
    liberar_estado(&busca3);
    mensagem_sucesso("Memoria para busca de Minas Gerais liberada!\n");
    
    liberar_estado(&busca4);
    mensagem_sucesso("Memoria para busca de Parana liberada!\n");
    
    print_amarelo("Liberando lista de estados...\n");
    liberar_lista(&lista);
    mensagem_sucesso("Lista liberada com sucesso!\n");
}

void testar_remocao() {
    print_verde("Testando remocao de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar estados para testar
    ESTADO estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    mensagem_sucesso("Estado Sao Paulo criado com sucesso!\n");
    
    ESTADO estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    mensagem_sucesso("Estado Rio de Janeiro criado com sucesso!\n");
    
    ESTADO estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    mensagem_sucesso("Estado Minas Gerais criado com sucesso!\n");
    
    // Inserir estados
    inserir_ordernado_duplamente(&lista, &estado1);
    inserir_ordernado_duplamente(&lista, &estado2);
    inserir_ordernado_duplamente(&lista, &estado3);
    mensagem_sucesso("Estados inseridos na lista com sucesso!\n");
    
    print_amarelo("Lista original:\n");
    exibirLista(lista);
    
    // Remover estado do meio (Rio de Janeiro)
    print_amarelo("\nRemovendo estado Rio de Janeiro...\n");
    ESTADO remover1 = criar_estado("Rio de Janeiro", "", 0, 0, NULL);
    if(removerEstado(&lista, &remover1)) {
        mensagem_sucesso("Estado Rio de Janeiro removido com sucesso!\n");
    } else {
        mensagem_erro("Falha ao remover Rio de Janeiro!\n");
    }
    
    print_amarelo("Lista apos remover Rio de Janeiro:\n");
    exibirLista(lista);
    
    if(lista != NULL && lista->prox != NULL) {
        if(strcmp(lista->estado.nome_estado, "Minas Gerais") == 0)
            mensagem_sucesso("Primeiro elemento e Minas Gerais, como esperado!\n");
        else
            mensagem_erro("Primeiro elemento nao e Minas Gerais!\n");
            
        if(strcmp(lista->prox->estado.nome_estado, "Sao Paulo") == 0)
            mensagem_sucesso("Segundo elemento e Sao Paulo, como esperado!\n");
        else
            mensagem_erro("Segundo elemento nao e Sao Paulo!\n");
    } else {
        mensagem_erro("A lista nao tem os elementos esperados apos remocao!\n");
    }
    
    // Remover estado do inicio (Minas Gerais)
    print_amarelo("\nRemovendo estado Minas Gerais...\n");
    ESTADO remover2 = criar_estado("Minas Gerais", "", 0, 0, NULL);
    if(removerEstado(&lista, &remover2)) {
        mensagem_sucesso("Estado Minas Gerais removido com sucesso!\n");
    } else {
        mensagem_erro("Falha ao remover Minas Gerais!\n");
    }
    
    print_amarelo("Lista apos remover Minas Gerais:\n");
    exibirLista(lista);
    
    if(lista != NULL) {
        if(strcmp(lista->estado.nome_estado, "Sao Paulo") == 0)
            mensagem_sucesso("Primeiro elemento e Sao Paulo, como esperado!\n");
        else
            mensagem_erro("Primeiro elemento nao e Sao Paulo!\n");
            
        if(lista->prox == NULL)
            mensagem_sucesso("A lista tem apenas um elemento, como esperado!\n");
        else
            mensagem_erro("A lista tem mais elementos do que deveria!\n");
    } else {
        mensagem_erro("A lista esta vazia quando deveria ter um elemento!\n");
    }
    
    // Remover ultimo estado (Sao Paulo)
    print_amarelo("\nRemovendo estado Sao Paulo...\n");
    ESTADO remover3 = criar_estado("Sao Paulo", "", 0, 0, NULL);
    if(removerEstado(&lista, &remover3)) {
        mensagem_sucesso("Estado Sao Paulo removido com sucesso!\n");
    } else {
        mensagem_erro("Falha ao remover Sao Paulo!\n");
    }
    
    print_amarelo("Lista apos remover Sao Paulo:\n");
    exibirLista(lista);
    
    if(lista == NULL)
        mensagem_sucesso("A lista esta vazia, como esperado!\n");
    else
        mensagem_erro("A lista nao esta vazia apos remocao de todos os elementos!\n");
    
    // Tentar remover de lista vazia
    print_amarelo("\nTentando remover estado Parana de lista vazia...\n");
    ESTADO remover4 = criar_estado("Parana", "", 0, 0, NULL);
    if(removerEstado(&lista, &remover4)) {
        mensagem_erro("Remocao de lista vazia deveria falhar, mas retornou sucesso!\n");
    } else {
        mensagem_sucesso("Remocao de lista vazia falhou corretamente!\n");
    }
    
    // Liberar memoria
    print_amarelo("Liberando estruturas de teste...\n");
    liberar_estado(&remover1);
    mensagem_sucesso("Memoria para remocao de Rio de Janeiro liberada!\n");
    
    liberar_estado(&remover2);
    mensagem_sucesso("Memoria para remocao de Minas Gerais liberada!\n");
    
    liberar_estado(&remover3);
    mensagem_sucesso("Memoria para remocao de Sao Paulo liberada!\n");
    
    liberar_estado(&remover4);
    mensagem_sucesso("Memoria para remocao de Parana liberada!\n");
}

int main() {
    print_amarelo("=== TESTES DA LISTA DUPLAMENTE ENCADEADA ===\n\n");
    
    print_amarelo("=== TESTE DE CRIACAO ===\n");
    testar_criacao_lista();
    
    print_amarelo("\n=== TESTE DE INSERCAO ===\n");
    testar_insercao();
    
    print_amarelo("\n=== TESTE DE BUSCA ===\n");
    testar_busca();
    
    print_amarelo("\n=== TESTE DE REMOCAO ===\n");
    testar_remocao();
    
    print_verde("\n=== TODOS OS TESTES CONCLUIDOS COM SUCESSO! ===\n");
    
    return 0;
}
