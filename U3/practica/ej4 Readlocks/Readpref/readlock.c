#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem_read, sem_write;
volatile int q_read;
// sem_read = 1 indica que pueden entrar lectores
// sem_write = 1 indica que pueden entrar escritores
/*
En el caso read-prefering lo que buscamos es que no se bloquee la lectura
pero la escritura espere a que este 
*/
int readlock_init() {
  return sem_init(&sem_read,0,1) || sem_init(&sem_write,0,1); 
}

int readlock_read() {
  q_read++;
	if (q_read == 1) 
    return sem_wait(&sem_write);
  return 0;
}

int readlock_stopRead() {
  q_read--;
  if (q_read == 0)
    return sem_post(&sem_write);
  return 0;
}

int readlock_write() {
  return sem_wait(&sem_read);
}

int readlock_stopWrite() {
  return sem_wait(&sem_write);
}

int readlock_destroy() {
  return sem_destroy(&sem_read) || sem_destroy(&sem_write);
}