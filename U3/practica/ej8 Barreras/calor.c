#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "barreras.h"

#define N 1000
#define W 4
#define ITERS 3

float arr1[N];
float arr2[N];

barrier_t b;

static inline int min(int x, int y) { return x < y ? x : y; }

void calor(float *in, int lo, int hi, float *out)
{
	int i;
	for (i = lo; i < hi; i++) {
		int m = in[i];
		int l = i > 0   ? in[i-1] : m;
		int r = i < N-1 ? in[i+1] : m;
		out[i] = m + (l - m)/1000.0 + (r - m)/1000.0;
	}
}

/* Dado un array de [n], devuelve el punto de corte [i] de los [m] totales. */
static inline int cut(int n, int i, int m)
{
	return i * (n/m) + min(i, n%m);
}

void * thr(void *arg)
{
	int id = arg - (void*)0;
	int lo = cut(N, id, W);
	int hi = cut(N, id+1, W);
	int i;

	for (i = 0; i < ITERS; i++) {
		calor(arr1, lo, hi, arr2);
		printf("[%d]Entro a calor1\n",id);
		barrier_wait(&b);
		calor(arr2, lo, hi, arr1);
		printf("[%d]Entro a calor2\n",id);
		barrier_wait(&b);
	}
}

int main()
{
	pthread_t w[W];
	float f,f2;
	int i;

	barrier_init(&b,W);

	/*
	 * No cambiamos la semilla, por lo que este programa
	 * debería ser determinista
	 */
	
	for (i = 0; i < N; i++)
		arr1[i] = rand() / 10000.0;

	for (i = 0; i < W; i++)
		pthread_create(&w[i], NULL, thr, i + (void*)0);

	for (i = 0; i < W; i++)
		pthread_join(w[i], NULL);

	f = 0;
	for (i = 0; i < N; i++)
		f += arr1[i];
	f /= N;
	f2 = 0;
	for (i = 0; i < N; i++)
		f2 += arr2[i];
	f2 /= N;

	/* Imprimimos temperatura promedio, siempre debería dar igual */
	printf("[ARR1] Temp promedio : %f\n", f);
	printf("[ARR2] Temp promedio : %f\n", f2);
	return 0;
}