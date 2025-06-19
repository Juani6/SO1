#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "readlock.h"

sem_t mutex, sem_write, sem_read;
int q_read, q_writers, writer; // Si hay un escritor activo



Queue* q_create() {
	Queue* q = malloc(sizeof(struct _Queue));
	if (q) {
		q->tail = NULL;
		q->head = NULL;
	}
	return q;
}

int q_empty(Queue* q) {
	return q->head == NULL;
}

void q_enqueue(Queue* q, int type) {
	Node* new = malloc(sizeof (struct _Node));
	if (!new) return;
	new->type = type;
	new->next = NULL;
	if (q_empty(q)) {
		q->tail = new;
		q->head = new;
	}
	else {
		q->tail->next = new;
		q->tail = new;
	}
}

Type q_dequeue(Queue* q) {
	if (q_empty(q)) return -1;
	Node* n = q->head;
	Type data = n->type;
	q->head = n->next;

	if (q->head == NULL) 
		q->tail = NULL;
	free(n);
	return data;
}


Queue* readlock_init() {
  sem_init(&mutex,0,1);
  sem_init(&sem_write,0,0);
  sem_init(&sem_read,0,0);
  return q_create();
}

void readlock_read(Queue* q) {
  sem_wait(&mutex);
  /* encolar lector */
  q_enqueue(q,READER); // Encolamos un lector
    if ((q->head && q->head->type != READER) || writer) { // Si la cabeza no es un lector o no hay escritores activos
    sem_post(&mutex);
    sem_wait(&sem_read);
    sem_wait(&mutex);
  }
  q_read++;
  q_dequeue(q);

  Node* temp = q->head;
    while(temp && temp->type == READER) {
		sem_post(&sem_read);
		temp = temp->next;
	  }

  sem_post(&mutex);
}

void readlock_stopRead(Queue* q) {
  sem_wait(&mutex);
  q_read--;
  if (q_read == 0 && q->head && q->head->type == WRITER)
    sem_post(&sem_write);
  sem_post(&mutex);
}

void readlock_write(Queue* q) {
	sem_wait(&mutex);
	q_enqueue(q,WRITER);
	q_writers++;
	if ((q->head && q->head->type != WRITER) || q_read > 0 || writer > 0) {
    sem_post(&mutex);
    sem_wait(&sem_write);
    sem_wait(&mutex);
  }
  q_writers--;
  writer = 1;
  q_dequeue(q);
  sem_post(&mutex);
}

void readlock_stopWrite(Queue* q) {
  sem_wait(&mutex);
  writer = 0;
  if (q->head && q->head->type == WRITER)
    sem_post(&sem_write);
  else {
	Node* temp = q->head;
    while(temp && temp->type == READER) {
		sem_post(&sem_read);
		temp = temp->next;
	  }
	}
  sem_post(&mutex);
}

void readlock_destroy() {
  sem_destroy(&mutex);
  sem_destroy(&sem_read);
  sem_destroy(&sem_write);
}