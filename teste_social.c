#include <stdio.h>
#include <stdlib.h>



int *alocar_int( int valor )
{
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    *p = valor;
    return p;
}


int main()
{

    int *ponteiro = alocar_int(10);
    int var = *ponteiro;

    free(ponteiro); // Free the allocated memory


    printf("Valor alocado: %d\n", var);
    printf("Endereco de memoria: %p\n", (void *)&(*ponteiro));
    printf("Endereco de memoria: %p\n", (void *)&var);



    return 0;
}