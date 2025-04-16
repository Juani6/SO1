#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/epoll.h>
#define MAX 10


struct epoll_event ev, events[MAX];
int mem,epollfd,nfds;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t threads[MAX];

void quit(char* s) {
  perror(s);
  abort();
}

int fd_readline(int fd, char *buf)
{
  int rc;
  int i = 0;
  
  /*
  * Leemos de a un caracter (no muy eficiente...) hasta
  * completar una línea.
  */
 while ((rc = read(fd, buf + i, 1)) > 0) {
   if (buf[i] == '\n')
   break;
    i++;
  }
  
  if (rc < 0)
  return rc;
  
  buf[i] = 0;
  return i;
}


void handle_conn(int csock)
{
  char buf[200];
  int rc;
  
  
  while (1) {
    /* Atendemos pedidos, uno por linea */
    rc = fd_readline(csock, buf);
    if (rc < 0)
    quit("read... raro");
    
    if (rc == 0) {
      /* linea vacia, se cerró la conexión */
      close(csock);
    }
    
    if (!strcmp(buf, "hola")) {
      /*si son iguales pasa esto, caso contrario ni idea*/
      char reply[20];
      
      sprintf(reply, "%d\n", mem);
      pthread_mutex_lock(&mutex);
      mem++; 
      pthread_mutex_unlock(&mutex);
      write(csock, reply, strlen(reply));
    } else if (!strcmp(buf, "chau")) {
      close(csock);
    }
    pthread_exit(0);
  } 
}

// struct epollevent* -> handle
/* void handle_threads(struct epoll_event* eventos) {
  for (int i = 0; i < MAX; i++) {
    pthread_create(threads+i,NULL,handle_conn,&(eventos[i].data.fd));
  }
} */

void* wait_for_clients(void* lsock)
{
  int csock;
  csock = accept(*(int*)lsock, NULL, NULL);
  if (csock < 0) 
    quit("accept");
  else {
    handle_conn(csock);
  }
  pthread_exit(0);
}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_lsock()
{
  struct sockaddr_in sa;
  int lsock;
  int rc;
  int yes = 1;

  /* Crear socket */
  lsock = socket(AF_INET, SOCK_STREAM, 0);
  if (lsock < 0)
    quit("socket");

  /* Setear opción reuseaddr... normalmente no es necesario */
  if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
    quit("setsockopt");

  sa.sin_family = AF_INET;
  sa.sin_port = htons(4040);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
  rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
  if (rc < 0)
    quit("bind");

  /* Setear en modo escucha */
  rc = listen(lsock, 10);
  if (rc < 0)
    quit("listen");

  return lsock;
}

int main()
{
  int lsock;
  mem = 0;  
  // printf("Primer valor: %d\n", *num);
  lsock = mk_lsock();

  epollfd = epoll_create1(0);
  if (epollfd == -1) {
      perror("epoll_create1");
      exit(EXIT_FAILURE);
  }

  ev.events = EPOLLIN;
  ev.data.fd = lsock;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, lsock, &ev) == -1) {
      perror("epoll_ctl: listen_sock");
      exit(EXIT_FAILURE);
  }

  for (;;) {
    nfds = epoll_wait(epollfd, events, MAX, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }
    for (int n = 0; n < nfds; ++n) {
        if (events[n].data.fd == lsock) {
            pthread_create(threads+n,NULL,wait_for_clients,&lsock);
        } 
    }
  }

  //wait_for_clients(lsock);
  return 0;
}
