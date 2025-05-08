#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Includes/main.h"

// Contador de testes bem-sucedidos e falhos
int testes_bem_sucedidos = 0;
int testes_falhos = 0;

// Protótipos de funções de teste para evitar erros de compilação
void reportar_teste(const char *nome_teste, int resultado);
void test_criarEstado();
void test_inserir_estado();
void test_inserir_estado_recursivo();
void test_buscar_com_filtro();
void test_comparar_por_nome();
void test_removerEstado();
void test_exibirLista();
void test_liberarLista();

// Garantir que o protótipo do comparar_por_nome está correto
// Assumindo que a função comparar_por_nome espera dois const char*
int comparar_por_nome( char *nome1,  char *nome2);

void reportar_teste(const char *nome_teste, int resultado)
{
    if (resultado)
    {
        printf("[PASSOU] %s\n", nome_teste);
        testes_bem_sucedidos++;
    }
    else
    {
        printf("[FALHOU] %s\n", nome_teste);
        testes_falhos++;
    }
}

void test_criarEstado()
{
    printf("\n=== Teste: criarEstado ===\n");

    // Teste básico
    ESTADOS *estado = criarEstado();
    reportar_teste("Criar estado", estado != NULL);

    // Verificar inicialização
    if (estado)
    {
        reportar_teste("Estado inicializado corretamente",
                       estado->nome == NULL &&
                           estado->estado == NULL &&
                           estado->qnt_estados == 0 &&
                           estado->tam_populacao == NULL &&
                           estado->ant == NULL &&
                           estado->prox == NULL);
        free(estado);
    }
}

void test_inserir_estado()
{
    printf("\n=== Teste: inserir_estado ===\n");

    // Inicialização
    ESTADOS *lista = NULL;

    // Teste inserir primeiro elemento
    reportar_teste("Inserir primeiro estado", inserir_estado(&lista, "Estado1"));
    reportar_teste("Lista não é NULL após inserção", lista != NULL);

    if (lista)
    {
        reportar_teste("Nome correto", strcmp(lista->nome, "Estado1") == 0);
    }

    // Teste inserir segundo elemento
    reportar_teste("Inserir segundo estado", inserir_estado(&lista, "Estado2"));

    // Teste inserir elemento duplicado
    reportar_teste("Inserir elemento duplicado falha", !inserir_estado(&lista, "Estado1"));

    // Teste inserir com ponteiro NULL
    reportar_teste("Inserir com ponteiro NULL falha", !inserir_estado(NULL, "Estado3"));

    // Teste inserir nome NULL
    reportar_teste("Inserir nome NULL falha", !inserir_estado(&lista, NULL));

    liberarLista(&lista);
}

void test_inserir_estado_recursivo()
{
    printf("\n=== Teste: inserir_estado_recursivo ===\n");

    ESTADOS *lista = NULL;
    ESTADOS *novo = criarEstado();
    if (novo)
    {
        novo->nome = strdup("EstadoRecursivo");

        // Teste inserir recursivamente
        reportar_teste("Inserir estado recursivamente", inserir_estado_recursivo(&lista, novo));
        reportar_teste("Lista não é NULL após inserção recursiva", lista != NULL);

        if (lista)
        {
            reportar_teste("Nome correto após inserção recursiva",
                           strcmp(lista->nome, "EstadoRecursivo") == 0);
        }

        // Teste inserir duplicado
        ESTADOS *duplicado = criarEstado();
        if (duplicado)
        {
            duplicado->nome = strdup("EstadoRecursivo");
            reportar_teste("Inserir duplicado recursivamente falha",
                           !inserir_estado_recursivo(&lista, duplicado));
            free(duplicado->nome);
            free(duplicado);
        }

        liberarLista(&lista);
    }
    else
    {
        reportar_teste("Criar estado para teste recursivo", 0);
    }
}

void test_buscar_com_filtro()
{
    printf("\n=== Teste: buscar_com_filtro ===\n");

    ESTADOS *lista = NULL;
    inserir_estado(&lista, "Estado1");
    inserir_estado(&lista, "Estado2");
    inserir_estado(&lista, "Estado3");

    // Busca básica
    ESTADOS *resultado = buscar_com_filtro(lista, "Estado1", comparar_por_nome);
    reportar_teste("Buscar estado existente", resultado != NULL);
    if (resultado)
    {
        reportar_teste("Nome correto no resultado", strcmp(resultado->nome, "Estado1") == 0);
    }

    // Buscar segundo elemento
    resultado = buscar_com_filtro(lista, "Estado2", comparar_por_nome);
    reportar_teste("Buscar segundo estado", resultado != NULL);
    if (resultado)
    {
        reportar_teste("Nome correto no segundo resultado", strcmp(resultado->nome, "Estado2") == 0);
    }

    // Buscar elemento inexistente
    resultado = buscar_com_filtro(lista, "EstadoInexistente", comparar_por_nome);
    reportar_teste("Buscar estado inexistente retorna NULL", resultado == NULL);

    // Buscar com lista vazia
    ESTADOS *lista_vazia = NULL;
    resultado = buscar_com_filtro(lista_vazia, "Estado1", comparar_por_nome);
    reportar_teste("Buscar em lista vazia retorna NULL", resultado == NULL);

    // Buscar com parâmetros NULL
    reportar_teste("Buscar com nome NULL retorna NULL",
                   buscar_com_filtro(lista, NULL, comparar_por_nome) == NULL);
    reportar_teste("Buscar com função NULL retorna NULL",
                   buscar_com_filtro(lista, "Estado1", NULL) == NULL);

    liberarLista(&lista);
}

void test_comparar_por_nome()
{
    printf("\n=== Teste: comparar_por_nome ===\n");

    // Comparações básicas
    reportar_teste("Nomes iguais", comparar_por_nome("Estado1", "Estado1") == 0);
    reportar_teste("Nome1 vem antes de Nome2", comparar_por_nome("Estado1", "Estado2") < 0);
    reportar_teste("Nome2 vem depois de Nome1", comparar_por_nome("Estado2", "Estado1") > 0);

    // Casos especiais
    reportar_teste("Nome1 NULL", comparar_por_nome(NULL, "Estado1") != 0);
    reportar_teste("Nome2 NULL", comparar_por_nome("Estado1", NULL) != 0);
    reportar_teste("Ambos NULL", comparar_por_nome(NULL, NULL) == 0);
}

void test_removerEstado()
{
    printf("\n=== Teste: removerEstado ===\n");

    ESTADOS *lista = NULL;
    inserir_estado(&lista, "Estado1");
    inserir_estado(&lista, "Estado2");
    inserir_estado(&lista, "Estado3");

    // Remover do meio
    removerEstado(&lista, "Estado2");
    reportar_teste("Estado removido não está mais na lista",
                   buscar_com_filtro(lista, "Estado2", comparar_por_nome) == NULL);
    reportar_teste("Estados anteriores ainda na lista",
                   buscar_com_filtro(lista, "Estado1", comparar_por_nome) != NULL);
    reportar_teste("Estados posteriores ainda na lista",
                   buscar_com_filtro(lista, "Estado3", comparar_por_nome) != NULL);

    // Remover do início
    removerEstado(&lista, "Estado1");
    reportar_teste("Estado inicial removido não está mais na lista",
                   buscar_com_filtro(lista, "Estado1", comparar_por_nome) == NULL);
    reportar_teste("Novo primeiro elemento correto",
                   lista != NULL && strcmp(lista->nome, "Estado3") == 0);

    // Remover o último
    removerEstado(&lista, "Estado3");
    reportar_teste("Lista vazia após remover todos elementos", lista == NULL);

    // Tentativa de remover de lista vazia
    removerEstado(&lista, "Estado4");
    reportar_teste("Remover de lista vazia não causa falha", 1); // Só verifica que não houve crash

    // Remover elemento inexistente
    inserir_estado(&lista, "Estado4");
    removerEstado(&lista, "EstadoInexistente");
    reportar_teste("Elemento ainda existe após tentativa de remover inexistente",
                   buscar_com_filtro(lista, "Estado4", comparar_por_nome) != NULL);

    liberarLista(&lista);
}

void test_exibirLista()
{
    printf("\n=== Teste: exibirLista ===\n");

    ESTADOS *lista = NULL;

    // Teste com lista vazia
    printf("Teste exibir lista vazia (não deve mostrar nada):\n");
    exibirLista(lista);

    // Teste com um elemento
    inserir_estado(&lista, "Estado1");
    printf("\nTeste exibir lista com um elemento:\n");
    exibirLista(lista);

    // Teste com vários elementos
    inserir_estado(&lista, "Estado2");
    inserir_estado(&lista, "Estado3");
    printf("\nTeste exibir lista com vários elementos:\n");
    exibirLista(lista);

    liberarLista(&lista);
    reportar_teste("exibirLista não causou falha", 1); // Verifica que não houve crash
}

void test_liberarLista()
{
    printf("\n=== Teste: liberarLista ===\n");

    ESTADOS *lista = NULL;

    // Teste liberar lista vazia
    liberarLista(&lista);
    reportar_teste("Liberar lista vazia não causa falha", lista == NULL);

    // Teste liberar lista com elementos
    inserir_estado(&lista, "Estado1");
    inserir_estado(&lista, "Estado2");
    liberarLista(&lista);
    reportar_teste("Lista é NULL após liberação", lista == NULL);

    // Teste liberar ponteiro NULL
    ESTADOS **ptr_null = NULL;
    liberarLista(ptr_null);
    reportar_teste("Liberar ponteiro NULL não causa falha", 1); // Verifica que não houve crash
}

int main()
{
    printf("=== INICIANDO TESTES ===\n");

    test_criarEstado();
    test_inserir_estado();
    test_inserir_estado_recursivo();
    test_comparar_por_nome();
    test_buscar_com_filtro();
    test_removerEstado();
    test_exibirLista();
    test_liberarLista();

    printf("\n=== RESUMO DOS TESTES ===\n");
    printf("Testes bem-sucedidos: %d\n", testes_bem_sucedidos);
    printf("Testes falhos: %d\n", testes_falhos);
    printf("Total de testes: %d\n", testes_bem_sucedidos + testes_falhos);

    return testes_falhos > 0 ? 1 : 0;
}