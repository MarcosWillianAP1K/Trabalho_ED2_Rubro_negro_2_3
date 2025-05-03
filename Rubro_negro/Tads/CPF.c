#include "../Includes/CPF.h"
#include <stdio.h>
#include <stdlib.h>




int validar_cpf(const char *cpf)
{
    int valido = 0;
    if (cpf && strlen(cpf) == 11)
    {
        int todos_digitos = 1;
        for (int i = 0; i < 11 && todos_digitos; i++)
        {
            if (!isdigit(cpf[i]))
            {
                todos_digitos = 0;
            }
        }
        valido = todos_digitos;
    }
    return valido;
}

int capturar_cpf(char *cpf)
{
    int sucesso = 0;
    char entrada[13]; // 11 dígitos + \n + \0
    printf("Digite o CPF (11 dígitos, sem pontos ou traços): ");
    if (fgets(entrada, sizeof(entrada), stdin))
    {
        entrada[strcspn(entrada, "\n")] = '\0';
        if (validar_cpf(entrada))
        {
            strcpy(cpf, entrada);
            sucesso = 1;
        }
        else
        {
            printf("Erro: CPF deve ter 11 dígitos numéricos!\n");
        }
    }
    else
    {
        printf("Erro: falha na leitura!\n");
    }
    return sucesso;
}