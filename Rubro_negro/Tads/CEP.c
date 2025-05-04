#include "../Includes/CEP.h"
#include "../Includes/funcao_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *corrigir_formatacao_cep(char *cep)
{
    if (cep != NULL)
    {
        char *cep_corrigido = (char *)malloc(10 * sizeof(char)); // 8 dígitos + 1 hífen + 1 terminador
        verificar_alocacao(cep_corrigido);                       // Verifica se a alocação foi bem-sucedida

        cep_corrigido[0] = '\0';

        short int tamanho = strlen(cep);

        // Extrai apenas os dígitos
        for (int i = 0; i < tamanho && i < 9; i++)
        {
            if (isdigit(cep[i]) && i != 5) // Ignora o hífen
            {
                strncat(cep_corrigido, &cep[i], 1); // Adiciona o dígito ao CEP corrigido
            }
            else if (i == 5) // Adiciona o hífen na posição correta
            {
                strncat(cep_corrigido, "-", 1);
            } 
            
        }
        
        free(cep);           // Libera o CEP original
        cep = cep_corrigido; // Atualiza o ponteiro para o CEP corrigido
    }

    return cep;
}

int validar_cep(char *cep)
{
    int valido = 0;
    if (cep  && strlen(cep) == 9 && cep[5] == '-')
    {
        valido = 1; // CEP deve ter 8 dígitos e um hífen na posição correta
        
        for (int i = 0; i < 9 && valido == 1; i++)
        {
            if (i != 5 && !isdigit(cep[i]))
            {
                valido = 0; // CEP deve conter apenas dígitos e o hífen na formatação correta
            }
        }
        
    }

    return valido;
}