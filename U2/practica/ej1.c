#include <stdio.h>
#include <stdlib.h>
#define LEN 10

void enc1(int* flag, int arr[]) {
  for(int i = 0; i < LEN; i++) {
    if (arr[i] == 42) 
      *flag = 1;
  }
}

void enc2(int* flag, int arr[]) {
  for(int i = 0; i < LEN; i++) {
    *flag = *flag || (arr[i] == 42); 
  }
}

int main() {
  int arr[LEN] = {1,2,3,4,42,5,6,7,8,9};
  int arr2[LEN] = {1,2,3,4,0,5,6,7,8,9};
  int f1 = 7,
      f2 = 7;
  printf("[f1] %d\n[f2] %d\n",f1,f2);
  enc1(&f1,arr2);
  enc2(&f2,arr2);
  printf("[f1] %d\n[f2] %d\n",f1,f2);
  return 0;
}

/*enc2 puede generar una condicion de carrera debido a que la flag esta siendo modificada en cada iteracion.*/

