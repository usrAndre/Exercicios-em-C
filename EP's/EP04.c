/*
  COM220 - Sistemas Operacionais
  Victor Rodrigues da Silva - 31054
  EP04 - 11/09/15
  Método de ordenação InsertSort
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 1000

void *thread1(int *V);
void *thread2(int *V);
void InsertionSort(int i, int V[], int N);

int main(int argc, char** argv) {
    pthread_t threads[2];
    pthread_attr_t attr;
    int i, V[MAX];
    clock_t inicio, fim;
    double tempo;
    char opc;

    inicio = clock();
    srand(time(NULL)); // Evitar repetição
    for(i=0; i<MAX; i++)
        V[i] = rand()%MAX;


    inicio = clock();
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&(threads[0]), NULL, thread1, V);
    pthread_create(&(threads[1]), NULL, thread2, V);

    pthread_attr_destroy(&attr);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    fim = clock();
    tempo = (double)(fim-inicio)/CLOCKS_PER_SEC;

    printf("Tempo: %.2lf\n\nDeseja ver o vetor ordenado? R[s/n]: ", tempo);
    scanf(" %c", &opc);

    if(opc == 's'){
        for (i=0; i<MAX; i++)
            printf("%d ", V[i]);
        printf("\n\n");
    } else if(opc == 'n')
        exit(0);
    else
        printf("Opcao invalida!\n\n");

    return (EXIT_SUCCESS);
}

void *thread1(int *V) {
    InsertionSort(0, V, MAX/2-1);

    pthread_exit(NULL);
}

void *thread2(int *V) {
    InsertionSort(MAX/2, V, MAX);

    pthread_exit(NULL);
}

void InsertionSort(int i, int V[], int N){
    if (i<N){
        int j, aux = V[i];

        for (j=i; j>0 && V[j-1]>aux; j--)
            V[j] = V[j-1];
        V[j] = aux;

        InsertionSort(++i, V, N);
    }
}
