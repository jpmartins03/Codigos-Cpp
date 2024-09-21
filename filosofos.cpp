#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int n;
pthread_t *filosofos;
sem_t *garfos;

int dir(int id){
	return id;
}

int esq(int id){
	return id -1 < 0 ? n - 1 : id - 1;
}

void comer(int id){
	printf("Filosofo %d esta comendo... \n", id);
}

void pega_garfo(int id){
	sem_wait(&garfos[id]);
}

void libera_garfo(int id){
	sem_post(&garfos[id]);
}




void *filosofo(void *argumentos){
	int id = *((int*)argumentos);
	while(1){
		printf("Pensando..\n");
		pega_garfo(esq(id));
		printf("Filosofo %d pegou o garfo da esquerda(%d)\n", id, esq(id));
		pega_garfo(dir(id));
		printf("Filosofo %d pegou o garfo da direita(%d)\n", id, dir(id));
		comer(id);
		libera_garfo(esq(id));
		printf("Filosofo %d liberou o garfo da esquerda(%d)\n", id, esq(id));
		libera_garfo(dir(id));
		printf("Filosofo %d liberou o garfo da direita(%d)\n", id, dir(id));


	}
}

int main(int argc, char **argv){
	n = atoi(argv[1]);

	garfos = (sem_t*)malloc(n*sizeof(sem_t));
	filosofos = (pthread_t*)malloc(n*sizeof(pthread_t));

	for(int i = 0; i < n; i ++){
		sem_init(&garfos[i], 0, 1);
	}
	int *ids = (int *)malloc(n*sizeof(int));
	for(int i = 0; i < n; i ++){
		ids[i] = i;
		pthread_create(&filosofos[i], NULL, filosofo, (void*)&(ids[i]));
	}
}













