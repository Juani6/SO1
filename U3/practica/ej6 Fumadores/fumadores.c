#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


sem_t tabaco, papel, fosforos, otra_vez;
sem_t arr[3], mutex;
int cTabaco, cPapel, cFosforos;

void* agente(void*) {
	while (1) {
		sem_wait(&otra_vez);
		int caso = random() % 3;
		switch (caso) {
		case 0:
		    printf("[Agente] Coloca FOSFOROS\n");
			sem_post(&fosforos);
			break;
		case 1:
		    printf("[Agente] Coloca PAPEL\n");
			sem_post(&papel);
			break;
		case 2:
		    printf("[Agente] Coloca TABACO\n");
			sem_post(&tabaco);
			break;
		} 
	}
}

void fumar(int fumador) {
	printf("[FUMADOR] %d: Puf! Puf! Puf!\n", fumador);
	sleep(1);
}

void* incrementar_tabaco(void* arg) {
	while (1) {
		sem_wait(&tabaco);
		sem_wait(&mutex);
		cTabaco++;
		sem_post(&mutex);
	}
}
void* incrementar_fosforos(void* arg) {
	while(1) {
		sem_wait(&fosforos);
		sem_wait(&mutex);
		cFosforos++;
		sem_post(&mutex);
	}
}

void* incrementar_papel(void* arg) {
	while (1){
		sem_wait(&papel);
		sem_wait(&mutex);
		cPapel++;
		sem_post(&mutex);
	}
}

void* controlador(void* arg) {
	/*
	arr[0] -> f1
	arr[1] -> f2
	arr[2] -> f3
	*/
	while (1) {

		sem_wait(&mutex);
		if (cTabaco > 0 && cPapel > 0) {
			cTabaco--; cPapel--;
			sem_post(&arr[0]);
			sem_post(&mutex);
		}
		else if (cFosforos > 0 && cPapel > 0) {
			cFosforos--; cPapel--;
			sem_post(&arr[1]);
			sem_post(&mutex);
		} 
		else if (cTabaco > 0 && cFosforos > 0) {
			cFosforos--; cTabaco--;
			sem_post(&arr[2]);
			sem_post(&mutex);
		}
		else {
			sem_post(&mutex);
			sem_post(&otra_vez);
			sleep(1);
		}	
	}
}


void* f1(void *arg) {
	while (1) {
		sem_wait(&arr[0]);
		fumar(1);
		sem_post(&otra_vez);
	}
}

void* f2(void *arg) {
	while (1) {

		sem_wait(&arr[1]);
		fumar(2);
		sem_post(&otra_vez);
	}
}

void* f3(void *arg) {
	while (1) {
		
		sem_wait(&arr[2]);
		fumar(3);
		sem_post(&otra_vez);
	}
}

int main() {
	srand(time(NULL)); // Inicializar aleatoriedad
	pthread_t s1,s2,s3;
	pthread_t ag, ctrl;

	sem_init(&tabaco,0,0);
	sem_init(&papel,0,0);
	sem_init(&fosforos,0,0);
	sem_init(&otra_vez,0,1);
	sem_init(&mutex,0,1);

	for (int i = 0; i < 3; i++) 
		sem_init(&arr[i],0,0);

	pthread_create(&s1,NULL,f1,NULL);
	pthread_create(&s2,NULL,f2,NULL);
	pthread_create(&s3,NULL,f3,NULL);

	pthread_t c1,c2,c3;

	pthread_create(&c1,NULL,incrementar_fosforos,NULL);
	pthread_create(&c2,NULL,incrementar_papel,NULL);
	pthread_create(&c3,NULL,incrementar_tabaco,NULL);



	pthread_create(&ctrl,NULL,controlador,NULL);
	pthread_create(&ag,NULL,agente,NULL);
	pthread_join(ag,NULL);
	//agente();
	return 0;
}