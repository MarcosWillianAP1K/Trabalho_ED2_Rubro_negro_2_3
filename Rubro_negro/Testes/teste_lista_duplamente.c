/* 
 * Comando para compilar:
 * gcc -Wall -o teste_lista teste_lista_duplamente.c ../Tads/Estruturas/Lista_duplamente.c ../Tads/Objetos/Estado.c ../Tads/Utilitarios/funcao_sistema.c -I../Includes
 * 
 * Explicacao dos parametros:
 * -Wall: Ativa todos os avisos de compilacao
 * -o teste_lista: Define o nome do executavel de saida como "teste_lista"
 * -I../Includes: Especifica um diretorio adicional onde o compilador deve procurar
 *                por arquivos de cabecalho (.h), permitindo que #include "arquivo.h" 
 *                funcione sem precisar do caminho completo em cada inclusao
 * 
 * Para executar:
 * ./teste_lista
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../Includes/Estruturas/Lista_duplamente.h"
#include "../Includes/Objetos/Estado.h"

void testar_criacao_lista() {
    printf("Testando criacao do no da lista...\n");
    
    LISTA_DUPLAMENTE* no = alocar_no_duplamente();
    assert(no != NULL);
    assert(no->estado == NULL);
    assert(no->ant == NULL);
    assert(no->prox == NULL);
    
    printf("Teste de criacao concluido com sucesso!\n");
    liberar_no_duplamente(&no);
    assert(no == NULL);
}

void testar_insercao() {
    printf("Testando insercao ordenada de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar tres estados para testar
    ESTADO *estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    ESTADO *estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    ESTADO *estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    
    // Inserir estados ordenadamente
    assert(inserir_ordernado_duplamente(&lista, estado1) == 1);
    assert(inserir_ordernado_duplamente(&lista, estado2) == 1);
    assert(inserir_ordernado_duplamente(&lista, estado3) == 1);
    
    printf("Lista apos insercoes:\n");
    exibirLista(lista);
    
    // Verificar a ordem (deve estar em ordem alfabetica por nome_estado)
    assert(strcmp(lista->estado->nome_estado, "Minas Gerais") == 0);
    assert(strcmp(lista->prox->estado->nome_estado, "Rio de Janeiro") == 0);
    assert(strcmp(lista->prox->prox->estado->nome_estado, "Sao Paulo") == 0);
    
    printf("Teste de insercao concluido com sucesso!\n");
    
    // Liberar lista e estados
    liberar_lista(&lista);
    assert(lista == NULL);
}

void testar_busca() {
    printf("Testando busca de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar estados para testar
    ESTADO *estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    ESTADO *estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    ESTADO *estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    
    // Inserir estados
    inserir_ordernado_duplamente(&lista, estado1);
    inserir_ordernado_duplamente(&lista, estado2);
    inserir_ordernado_duplamente(&lista, estado3);
    
    // Buscar estados existentes
    ESTADO *busca1 = criar_estado("Sao Paulo", "", 0, 0, NULL);
    ESTADO *busca2 = criar_estado("Rio de Janeiro", "", 0, 0, NULL);
    ESTADO *busca3 = criar_estado("Minas Gerais", "", 0, 0, NULL);
    ESTADO *busca4 = criar_estado("Parana", "", 0, 0, NULL); // Nao existe na lista
    
    LISTA_DUPLAMENTE *resultado1 = buscar_duplamente(lista, busca1);
    LISTA_DUPLAMENTE *resultado2 = buscar_duplamente(lista, busca2);
    LISTA_DUPLAMENTE *resultado3 = buscar_duplamente(lista, busca3);
    LISTA_DUPLAMENTE *resultado4 = buscar_duplamente(lista, busca4);
    
    assert(resultado1 != NULL);
    assert(resultado2 != NULL);
    assert(resultado3 != NULL);
    assert(resultado4 == NULL);
    
    assert(strcmp(resultado1->estado->nome_estado, "Sao Paulo") == 0);
    assert(strcmp(resultado2->estado->nome_estado, "Rio de Janeiro") == 0);
    assert(strcmp(resultado3->estado->nome_estado, "Minas Gerais") == 0);
    
    printf("Teste de busca concluido com sucesso!\n");
    
    // Liberar memoria
    liberar_lista(&lista);
    liberar_estado(&busca1);
    liberar_estado(&busca2);
    liberar_estado(&busca3);
    liberar_estado(&busca4);
}

void testar_remocao() {
    printf("Testando remocao de estados...\n");
    
    LISTA_DUPLAMENTE* lista = NULL;
    
    // Criar estados para testar
    ESTADO *estado1 = criar_estado("Sao Paulo", "Sao Paulo", 645, 45000000, NULL);
    ESTADO *estado2 = criar_estado("Rio de Janeiro", "Rio de Janeiro", 92, 17000000, NULL);
    ESTADO *estado3 = criar_estado("Minas Gerais", "Belo Horizonte", 853, 21000000, NULL);
    
    // Inserir estados
    inserir_ordernado_duplamente(&lista, estado1);
    inserir_ordernado_duplamente(&lista, estado2);
    inserir_ordernado_duplamente(&lista, estado3);
    
    printf("Lista original:\n");
    exibirLista(lista);
    
    // Remover estado do meio (Rio de Janeiro)
    ESTADO *remover1 = criar_estado("Rio de Janeiro", "", 0, 0, NULL);
    assert(removerEstado(&lista, remover1) == 1);
    
    printf("Lista apos remover Rio de Janeiro:\n");
    exibirLista(lista);
    assert(lista != NULL);
    assert(lista->prox != NULL);
    assert(strcmp(lista->estado->nome_estado, "Minas Gerais") == 0);
    assert(strcmp(lista->prox->estado->nome_estado, "Sao Paulo") == 0);
    
    // Remover estado do inicio (Minas Gerais)
    ESTADO *remover2 = criar_estado("Minas Gerais", "", 0, 0, NULL);
    assert(removerEstado(&lista, remover2) == 1);
    
    printf("Lista apos remover Minas Gerais:\n");
    exibirLista(lista);
    assert(lista != NULL);
    assert(strcmp(lista->estado->nome_estado, "Sao Paulo") == 0);
    assert(lista->prox == NULL);
    
    // Remover ultimo estado (Sao Paulo)
    ESTADO *remover3 = criar_estado("Sao Paulo", "", 0, 0, NULL);
    assert(removerEstado(&lista, remover3) == 1);
    
    printf("Lista apos remover Sao Paulo:\n");
    exibirLista(lista);
    assert(lista == NULL);
    
    // Tentar remover de lista vazia
    ESTADO *remover4 = criar_estado("Parana", "", 0, 0, NULL);
    assert(removerEstado(&lista, remover4) == 0);
    
    printf("Teste de remocao concluido com sucesso!\n");
    
    // Liberar memoria
    liberar_estado(&remover1);
    liberar_estado(&remover2);
    liberar_estado(&remover3);
    liberar_estado(&remover4);
}

int main() {
    printf("Iniciando testes da Lista Duplamente Encadeada\n");
    printf("=============================================\n\n");
    
    testar_criacao_lista();
    printf("\n");
    
    testar_insercao();
    printf("\n");
    
    testar_busca();
    printf("\n");
    
    testar_remocao();
    printf("\n");
    
    printf("Todos os testes foram concluidos com sucesso!\n");
    
    return 0;
}
