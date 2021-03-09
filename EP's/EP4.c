#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSortC(int vet[])
{
      int i,j,temp;

      for (i=1;i<100000;i++)
      {
          j = i;
          while (j > 0 && vet[j - 1] > vet[j])
          {
              temp=vet[j];
              vet[j]=vet[j - 1];
              vet[j-1]=temp;
              j--;
          }
      }
}

int main()
{
    int vet[100000],ordem,i;
    clock_t inicio,fim;
    double tempo;

    for(i=0;i<100000;i++)
    {
        vet[i]=rand();
    }

    inicio=clock();

    insertSortC(vet);

    fim=clock();

    printf("Em ordem crescente: ");

    for(i=0; i<100000; i++)
    {
      printf("\n%d", vet[i]);
    }
    tempo=(fim-inicio)/CLOCKS_PER_SEC;
    printf("\n\nTempo: %lf\n",tempo);

    return 0;
}
