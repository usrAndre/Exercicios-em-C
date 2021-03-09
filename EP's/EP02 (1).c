/*Eduardo de Freitas Silva - 31127*/

#include<stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include<math.h>

#define max 1000000

float fun_seno(float angulo);
float fun_cosseno(float angulo);

int main()
{
	pid_t n,n2;
	float x,seno,cosseno,resposta,resposta2,tangente;
	int vet[2],vet2[2],vet3[2],vet4[2];
	pipe(vet);
	pipe(vet2);
	pipe(vet3);
	pipe(vet4);
	n=fork();
	n2=fork();
	if((n==-1)||(n2==-1))
	{
    		perror("fork");
    		exit(EXIT_FAILURE);
	}
	else if(n==0)
	{
		close(vet[1]);
		read(vet[0],&x,sizeof(float));
		close(vet[0]);

		seno=fun_seno(x);

		close(vet2[0]);
		write(vet2[1],&seno,sizeof(float));
		close(vet2[1]);

		wait(NULL);
	}
	else if(n2==0)
	{
		close(vet3[1]);
		read(vet3[0],&x,sizeof(float));
		close(vet3[0]);

		cosseno=fun_cosseno(x);

		close(vet4[0]);
		write(vet4[1],&cosseno,sizeof(float));
		close(vet4[1]);

		wait(NULL);
	}
	else
	{
		scanf("%f",&x);
		close(vet[0]);
		write(vet[1],&x,sizeof(float));
		close(vet[1]);

		close(vet3[0]);
		write(vet3[1],&x,sizeof(float));
		close(vet3[1]);
		wait(NULL);

		close(vet2[1]);
		read(vet2[0],&seno,sizeof(float));
		close(vet2[0]);

		close(vet4[1]);
		read(vet4[0],&cosseno,sizeof(float));
		close(vet4[0]);

		resposta=seno;
		resposta2=cosseno;
		tangente=seno/cosseno;
		printf("\nTangente = %.5f.\n",tangente);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

float fun_seno(float angulo)
{
	int num,fat,sinal;
	float soma;
	register int i,j;
	num=3;
	soma=0;
	sinal=-1;
    	for(i=0;i<5;i++)
    	{
		fat=1;
    		for(j=1;j<=num;j++)
        		fat=fat*j;
        	soma=soma+(pow(angulo,num)*sinal)/fat;
		sinal=sinal*-1;
        	num=num+2;
    	}
    	return soma;
}

float fun_cosseno(float angulo)
{
	int num,fat,sinal;
	float soma;
	register int i,j;
	num=2;
	soma=0;
	sinal=-1;
    	for(i=0;i<5;i++)
    	{
		fat=1;
    		for(j=1;j<=num;j++)
        		fat=fat*j;
        	soma=soma+(pow(angulo,num)*sinal)/fat;
		sinal=sinal*-1;
        	num=num+2;
    	}
    	return soma;
}
