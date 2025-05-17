#include "../../Includes/Objetos/CEP.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void imprimir_CEP(char *cep)
{
    if (cep != NULL)
    {
        printf("CEP: %s\n", cep);
    }
    else
    {
        printf("CEP: N/A\n");
    }
}

void liberar_CEP(char **cep)
{
    if (*cep != NULL)
    {
        free(*cep);
        *cep = NULL;
    }
}

void corrigir_formatacao_CEP(char **cep)
{
    if (cep != NULL && *cep != NULL)
    {
        char *cep_corrigido = (char *)malloc(10 * sizeof(char)); // 8 dígitos + 1 hífen + 1 terminador
        verificar_alocacao(cep_corrigido);                       // Verifica se a alocação foi bem-sucedida

        cep_corrigido[0] = '\0';

        short int tamanho = strlen(*cep);
        int numeros_inseridos = 0; // Contador de números inseridos
        // Extrai apenas os dígitos
        for (int i = 0; i < tamanho && numeros_inseridos < 8; i++)
        {
            if (isdigit((*cep)[i])) // Ignora o hífen
            {
                if (numeros_inseridos == 5) // Adiciona o hífen na posição correta
                    strncat(cep_corrigido, "-", 1);
                

                strncat(cep_corrigido, &(*cep)[i], 1); // Adiciona o dígito ao CEP corrigido
                numeros_inseridos++;                   // Incrementa o contador de números inseridos
            }
        }

        free(*cep);           // Libera o CEP original
        *cep = cep_corrigido; // Atualiza o ponteiro para o CEP corrigido
    }
}

short int validar_CEP(char *cep)
{
    short int valido = 0;
    if (cep && strlen(cep) == 10 && cep[5] == '-')
    {
        valido = 1; // CEP deve ter 8 dígitos e um hífen na posição correta
        for (int i = 0; i < 9 && valido == 1; i++)
        {
            if (i == 5 && cep[i] == '-')
                valido = 1; // Hífen na posição correta
            else if (isdigit(cep[i]))
                valido = 1; // Verifica se é dígito
            else
                valido = 0; // Não é dígito
        }
    }

    return valido;
}

char *digitar_CEP()
{
    char *cep = NULL;
    short int valido = 0;

    while (valido == 0)
    {
        cep = digitar_string();
        corrigir_formatacao_CEP(&cep);

        valido = validar_CEP(cep);

        if (valido == 0)
        {
            free(cep); // Libera a memória alocada para o CEP inválido
            cep = NULL;
            mensagem_erro("CEP invalido.");
            printf("Digite novamente: ");
        }
    }
    return cep;
}

short int comparar_CEPs(char *cep1, char *cep2)
{
    short int resultado = 0;

    if (cep1 != NULL && cep2 != NULL)
        resultado = strcmp(cep1, cep2);
    else if (cep1 == NULL && cep2 != NULL)
        resultado = -1; // cep1 é menor que cep2
    else if (cep1 != NULL && cep2 == NULL)
        resultado = 1; // cep1 é maior que cep2

    return resultado;
}