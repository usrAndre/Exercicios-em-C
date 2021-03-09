//*******************************************//
//                                           //
//          EP01 - 21/08/2015                //
// Gustavo dos Santos Gomides - 30818 - CCO  //
//       Sistemas Operacionais               //
//                                           //
//*******************************************//


#include<stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define max 1000000

void crivo(int valor);

int main() {
	pid_t n;
	int num,valor;
	int vet[2],vet2[2];
	pipe(vet);
	pipe(vet2);

	n=fork();

	if(n == -1) {
        perror("fork");
    	exit(EXIT_FAILURE);
	}
	else if(n == 0) {
        int v;
		close(vet[1]);
		read(vet[0],&valor,sizeof(int));
		close(vet[0]);
		crivo(valor);

		close(vet2[0]);
		write(vet2[1],&valor,sizeof(int));
		close(vet2[1]);
	}
	else {
		printf("Digite um numero entre 100 e 1000: ");
		scanf("%d",&num);
		if(num<100 || num>1000) {
            printf("\nO numero deve estrar entre 100 e 1000!\n");
            exit(EXIT_FAILURE);
		}
		close(vet[0]);
		write(vet[1],&num,sizeof(int));
		close(vet[1]);

		close(vet2[1]);
		read(vet2[0],&valor,sizeof(int));
		close(vet2[0]);
		exit(0);
	}
	return 0;
}

void crivo(int valor) {
	int i,j,vet[max],raiz, cont=0;
	raiz=valor;
	for (i=2;i<=valor;i++)
		vet[i]=i;

	for (i=2; i<=raiz; i++) {
		if (vet[i]==i) {
			cont=cont+1; //Este é o contador de números primos
			printf("%d\n", vet[i]);
			for (j=i+i;j<=valor;j+=i)
				vet[j]=0;
		}
	}
	//return soma; //A função retorna a soma;
}

