/*
siempre que el lock est´e tomado por unlector 
y aparezca un segundo lector,
el segundo debe poder entrar inmediatamente (read-preferring).

Read prefering
Por un lado se busca bloquear la escritura sin impedir el acceso a los lectores 
i.e que no se pueda escribir el arreglo pero que los lectores si puedan acceder sin limitaciones
Entonces buscaremos bloquear con un semaforo el escritor, el valor del semaforo indicara
la cantidad de lectores en el arreglo, una vez leido decrementaran el valor y llegado a 0 
se podra escribir

*/

typedef enum  {
	READER,
	WRITER
} Type;

typedef struct _Node {
  Type type;
  struct _Node* next;
} Node;

typedef struct _Queue {
  Node* tail;
  Node* head;
} Queue;

#ifndef __READLOCK_H__
#define __READLOCK_H__

Queue* readlock_init(void); // Devuelve -1 en caso de error 0 caso contrario

void readlock_read(Queue*); // Devuelve -1 en caso de error 0 caso contrario 

void readlock_stopRead(Queue*);

void readlock_write(Queue*); // Devuelve -1 en caso de error 0 caso contrario

void readlock_stopWrite(Queue*);

void readlock_destroy(void);

#endif