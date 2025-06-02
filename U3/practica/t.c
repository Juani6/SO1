#include <stdio.h>
#include <stdlib.h>

int main() {
  int arr[5] = {1,2,3,4,5};
  void* j;

  for(int i = 0; i < 5; i++) {
    j = i + (void*)0;
    
    printf("i = %d, j = %p, k = %d\n", i,j,j-(void*)0);
  }
}
