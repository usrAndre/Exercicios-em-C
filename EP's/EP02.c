/*Eduardo de Freitas Silva - 31127
COM120 - EP02 - 28/08/15*/

#include<stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include<math.h>

#define max 1000000

float seno(float angulo);
float cosseno(float angulo);

int main()
{
	pid_t n,n2;
	float x,valor1,valor2,final,final2,resposta;
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
		read(vet[0],&x,sizeof(int));
		close(vet[0]);
		valor1 = seno(x);
		close(vet2[0]);
		write(vet2[1],&valor1,sizeof(int));
		close(vet2[1]);
		wait(NULL);
	}
	else if(n2==0)
	{
		close(vet4[1]);
		read(vet4[0],&x,sizeof(int));
		close(vet4[0]);
		valor2 = cosseno(x);
		close(vet3[0]);
		write(vet3[1],&valor2,sizeof(int));
		close(vet3[1]);
		wait(NULL);
	}
	else
	{
		scanf("%f",&x);
		close(vet[0]);
		write(vet[1],&x,sizeof(int));
		close(vet[1]);
		close(vet4[0]);
		write(vet4[1],&x,sizeof(int));
		close(vet4[1]);
		wait(NULL);
		close(vet2[1]);
		read(vet2[0],&valor1,sizeof(int));
		close(vet2[0]);
		close(vet3[1]);
		read(vet3[0],&valor2,sizeof(int));
		close(vet3[0]);
		final=valor1;
		final2=valor2;
		resposta=valor1/valor2;
		printf("\nTangente = %f.\n",resposta);
		exit(EXIT_SUCCESS);
	}
	return 0;
}


float seno(float angulo)
{
    int repeticao=10,a,sinal,expoente,b,c;
    float fat,rad,soma;
    soma=0;
    sinal=1;
    expoente=1;
    fat=1;
    b=1;
    rad=angulo;
    for(a=1;a<=repeticao;a+=1)
    {
    	for(c=1;c<=b;c+=1)
        fat=fat*c;
        soma=soma+sinal*pow(rad,expoente)/fat;
        expoente+=2;
        b+=2;
        fat=1;
        sinal=-sinal;
    }
    return soma;
}

float cosseno(float angulo)
{
    int repeticao=10,a,sinal,expoente,b,c;
    float fat,rad,soma;
    soma=0;
    sinal=1;
    expoente=1;
    fat=1;
    b=1;
    rad=angulo;
    for(a=1;a<=repeticao;a+=1)
    {
    	for(c=1;c<=b;c+=1)
        fat=fat*c;
        soma=soma+sinal*pow(rad,expoente)/fat;
        expoente+=2;
        b+=3;
        fat=1;
        sinal=-sinal;
    }
    return soma;
}
