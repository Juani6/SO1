#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define B 2
#define K (B*2)

volatile int s,r, buf[B];

// s mantiene la cantidad de elementos escritos 
// y r los leidos

static inline int diff() { 
	return (K + s - r) % K;
}

void *prod(void *arg) {
	int cur = 0;
	while (1) {
		while (diff() == B);
		buf[s % B] = cur++;
		s = (s+1) % K;
	}
}

void* cons(void* arg) {
	int cur;
	while (1) {
		while(diff() == 0);
		cur = buf[r%B];
		r = (r+1) % K;
		printf("Lei %d\n", cur);
		sleep(1);
	}
}

int main() {
	
	pthread_t productor,consumidor;
	pthread_create(&productor, NULL, prod,NULL);
	pthread_create(&consumidor, NULL, cons,NULL);

	pthread_join(productor,NULL);
	return 0;
}

/*
Este programa funciona por que :
1) No acceden a los mismos recursos, prod a s y cons a r 
2) la condicion del while que contiene a diff es un busy waiting que permite que ambos hilos se alternen el proceso
*/