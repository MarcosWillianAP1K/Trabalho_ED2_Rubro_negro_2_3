#include "../../Includes/Objetos/CPF.h"
#include "../../Includes/Utilitarios/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void imprimir_cpf(char *cpf)
{
    if (cpf != NULL)
    {
        printf("CPF: %s\n", cpf);
    }
    else
    {
        printf("CPF: N/A\n");
    }
}

void corrigir_formatacao_cpf(char **cpf)
{
    if (cpf != NULL && *cpf != NULL)
    {
        char *cpf_corrigido = (char *)malloc(15 * sizeof(char)); // 11 dígitos + 3 pontos + 1 terminador
        verificar_alocacao(cpf_corrigido);                       // Verifica se a alocação foi bem-sucedida

        cpf_corrigido[0] = '\0';

        short int tamanho = strlen(*cpf);
        int numeros_inseridos = 0; // Contador de números inseridos
        // Extrai apenas os dígitos
        for (int i = 0; i < tamanho && numeros_inseridos < 11; i++)
        {
            if (isdigit((*cpf)[i])) // Ignora os pontos e o traço
            {
                // Adiciona o ponto após o 3º, 6º e 9º dígito
                if (numeros_inseridos == 3 || numeros_inseridos == 6 || numeros_inseridos == 9)
                    strcat(cpf_corrigido, ".");
                
                strncat(cpf_corrigido, &(*cpf)[i], 1); // Adiciona o dígito ao CPF corrigido
                numeros_inseridos++;                // Incrementa o contador de números inseridos
            }
        }

        free(*cpf);           // Libera o CPF original
        *cpf = cpf_corrigido; // Atualiza o ponteiro para o CPF corrigido
    }
}

int validar_cpf(char *cpf)
{
    int valido = 0;
    if (cpf != NULL && strlen(cpf) == 11)
    {
        valido = 1; // CPF deve ter 11 dígitos

        for (int i = 0; i < 11 && valido == 1; i++)
        {
            if (!isdigit(cpf[i]) || ((i == 3 || i == 7) && cpf[i] != '.') || (i == 11 && cpf[i] != '-'))
              valido = 0; // CPF deve conter apenas dígitos, pontos e traço na formatação correta
            
        }
    }

    return valido;
}

char *digitar_CPF()
{
    char *cpf = digitar_string();

    // corrigir_espacos(&cpf);

    corrigir_formatacao_cpf(&cpf);

    // if (validar_cpf(cpf) == 0)
    //   cpf = NULL;
    return cpf;
}