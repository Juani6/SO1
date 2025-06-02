#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem_read, sem_write;

/* Inicializamos el semaforo de escritura en 1 (Se puede escribir)
   y el de lectura en 0
*/
int readlock_init() { 
  return sem_init(&sem_read,1,0) || sem_init(&sem_write,1,1); 
}

int readlock_read() {
  return sem_post(&sem_read);
}

int readlock_stopRead() {
  return sem_wait(&sem_read);
}

int readlock_write() {
  int sem_value;
  
  if (sem_getvalue(&sem_read,&sem_value)) // Obtenemos el valor del semaforo de lectura
    return -1;

  if (sem_value != 0) // Si es distinto de 0 (Estan leyendo) bloqueamos la escritura
    return sem_wait(&sem_write);
  else // Caso contrario escribimos
    return sem_post(&sem_write);
}

int readlock_stopWrite() {
  return sem_wait(&sem_write);
}

int readlock_destroy() {
  return sem_destroy(&sem_read) || sem_destroy(&sem_write);
}