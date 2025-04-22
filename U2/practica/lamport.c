#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define N 500
#define X 100000

int arrNums[N] = {0};
int arrEligiendo[N] = {0};
int num;

int maxArr(int *arr, int len) {
  int res = arr[0];
  for(int i = 0; i < len; i++) {
    if(res < arr[i]) {
      res = arr[i];
    }
  }
  return res;
}


void* fun(void *ptr) {
  int indice = *(int*) ptr;
  arrEligiendo[indice] = 1;
  arrNums[indice] = 1 + maxArr(arrNums,N);
  arrEligiendo[indice] = 0;
  /*
  Si el hilo j está calculando su número, espera a que termine
  Si el hilo j tiene más prioridad, espera a que ponga su número a cero 
  j tiene más prioridad si su número de turno es más bajo que el de i
  o bien si es el mismo número y además j es menor que i
  */
  for (int j = 0; j < N; j++) {
    while ( (arrEligiendo[j] == 1) || (arrNums[j] != 0 && 
        ((arrNums[j] < arrNums[indice]) || 
          ((arrNums[j] == arrNums[indice]) && (j < indice))))); // Nada
  }
  
  // Inicio Seccion critica
  for (int i = 0; i < X; i++) {
    num++;
  }
  // Fin seccion critica
  arrNums[indice] = 0;
  return NULL;
}

int main() {
  pthread_t arr[N];
  int indices[N];
  for(int j = 0; j < N; j++) {
    indices[j] = j;
    pthread_create(arr+j,NULL,fun, indices+j);
  } 
  for(int j = 0; j < N; j++) {
    pthread_join(arr[j],NULL);
  } 
  printf("Entraron %d\n", num);
  
  return 0;
}
