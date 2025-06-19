#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mutex, sem_write, sem_read;
int q_read, q_writers, writers;

void readlock_init() {
  sem_init(&mutex,0,1); 
  sem_init(&sem_write,0,0);
  sem_init(&sem_read,0,0); 
}

void readlock_read() {
  sem_wait(&mutex);
  if (writers > 0 || q_writers > 0) { 
    sem_post(&mutex);
    sem_wait(&sem_read);
    sem_wait(&mutex);
  }
  q_read++;
  sem_post(&mutex);
}

void readlock_stopRead() {
  sem_wait(&mutex);
  q_read--;
  if (q_read == 0 && writers > 0)
    sem_post(&sem_write);
  sem_post(&mutex);
}

void readlock_write() {
  sem_wait(&mutex);
  q_writers++;
  if (q_read > 0 || writers > 0) {
    sem_post(&mutex);
    sem_wait(&sem_write);
    sem_wait(&mutex);
  }
  q_writers--;
  writers = 1;
  sem_post(&mutex);
}

void readlock_stopWrite() {
  sem_wait(&mutex);
  writers == 0;
  if (q_writers > 0)
    sem_post(&sem_write);
  else
    sem_post(&sem_read);
  sem_post(&mutex);
}

void readlock_destroy() {
  sem_destroy(&mutex);
  sem_destroy(&sem_read);
  sem_destroy(&sem_write);
}