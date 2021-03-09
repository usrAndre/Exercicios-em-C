#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void *thread(void *vargp);
void *thread2(void *vargp);
float fun_seno(float angulo);
float fun_cosseno(float angulo);

float b,b1;

pthread_mutex_t mutex;

int main(){
    pthread_t tid[2];
    float a,tangente;
	pthread_mutex_init(&mutex, NULL);
    scanf("%f",&a);
    pthread_create(&tid[0], NULL, thread, &a); //Cria Thread
	pthread_create(&tid[1], NULL, thread2, &a); //Cria Thread
    pthread_join(tid[0], NULL); //Executa
	pthread_join(tid[1], NULL); //Executa
	tangente=b/b1;
	printf("%.5f",tangente);
	pthread_mutex_destroy(&mutex);
    pthread_exit((void *)NULL); //E finaliza
}

void *thread(void *vargp){
	float aux;
	float *a = (float *) vargp;
	aux = *a;
	b=fun_seno(aux);
    pthread_exit((void *)NULL);
}

void *thread2(void *vargp){
	float aux;
	float *a = (float *) vargp;
	aux = *a;
	b1=fun_cosseno(aux);
    pthread_exit((void *)NULL);
}

float fun_seno(float angulo){
	int num,fat,sinal;
	float soma;
	register int i,j;
	num=3;
	soma=0;
	sinal=-1;
    	for(i=0;i<5;i++){
		fat=1;
    		for(j=1;j<=num;j++)
        		fat=fat*j;
        	soma=soma+(pow(angulo,num)*sinal)/fat;
		sinal=sinal*-1;
        	num=num+2;
    	}
    	return soma;
}

float fun_cosseno(float angulo){
	int num,fat,sinal;
	float soma;
	register int i,j;
	num=2;
	soma=1;
	sinal=-1;
    	for(i=0;i<5;i++){
		fat=1;
    		for(j=1;j<=num;j++)
        		fat=fat*j;
        	soma=soma+(pow(angulo,num)*sinal)/fat;
		sinal=sinal*-1;
        	num=num+2;
    	}
    	return soma;
}
