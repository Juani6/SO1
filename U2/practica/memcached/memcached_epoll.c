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

#define MAX 2
#define DIR 3942

struct epoll_event ev, events[MAX];
int mem,epollfd,nfds;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t threads[MAX];

char* tabla[MAX];
volatile int cantElems;

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned KRHash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 31 * hashval;
  }
  return hashval;
}

int parser(char* buff,char** tokensArr, char* div) {
  int i = 0;
  char* token;
  for(token = strtok(buff,div); token != NULL || i < 3; i++) {
          tokensArr[i] = token;
          token = strtok(NULL,div);
      }
      tokensArr[i] = NULL;
  return i;
}

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
/* 
PUT k v: introduce al store el valor v bajo la clave k. El valor viejo para k, si exist´ıa, es pisado. El
servidor debe responder con OK.
DEL k: Borra el valor asociado a la clave k. El servidor debe responder con OK.
GET k: Busca el valor asociado a la clave k. El servidor debe contestar con OK v si el valor es v, o
con NOTFOUND si no hay valor asociado a k
*/

void handle_conn(int csock)
{
  char buf[200];
  int rc;
  char* parsedArr[2];
  int resParse;
  unsigned indice;
  int iterador = 1;
  char reply[20];
  

  //while (1) {
    /* Atendemos pedidos, uno por linea */
    rc = fd_readline(csock, buf);
    if (rc < 0)
    quit("read... raro");
    
    if (rc == 0) {
      /* linea vacia, se cerró la conexión */
      //close(csock);
      return;
    }
    resParse = parser(buf,parsedArr," ");
      if(parsedArr[1])
        indice = KRHash(parsedArr[1]) % MAX;
      if (!strcmp(parsedArr[0],"DEL") && cantElems > 0) {
        // Eliminar k de la hash
        pthread_mutex_lock(&mutex);
        tabla[indice] = NULL;
        pthread_mutex_unlock(&mutex);
        cantElems--;
        sprintf(reply,"%s\n", "OK");
        write(csock,reply,strlen(reply));
      }
      else if (!strcmp(parsedArr[0],"GET")) {
        
        sprintf(reply, "%s\n", tabla[indice]); 
        write(csock, reply, strlen(reply));
          
      }
      else if (!strcmp(parsedArr[0],"PUT")) {
        //almacena parsedArr[2] en hash(parsedArr[1])
        if (tabla[indice] == NULL)
          cantElems++;
        
        pthread_mutex_lock(&mutex);
        
        tabla[indice] = parsedArr[2];
        
        pthread_mutex_unlock(&mutex);
        
        
          sprintf(reply,"%s\n", "OK");
          write(csock,reply,strlen(reply));
      }
      else if (!strcmp(parsedArr[0],"CANT") || cantElems >= MAX) {
        sprintf(reply,"%d\n", cantElems);
        write(csock,reply,strlen(reply));
      }
      else {
        sprintf(reply,"Error :%s\n",parsedArr[0]);
        write(csock,reply,strlen(reply));
      }
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
  sa.sin_port = htons(DIR);
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
  int csock;
  int flags;
  // printf("Primer valor: %d\n", *num);
  lsock = mk_lsock();
  
  flags = fcntl(lsock, F_GETFL , 0);
  if (flags == -1) {
    perror("FLAGS GET");
    exit(EXIT_FAILURE);
  }
  if (fcntl(lsock, F_SETFL , flags | O_NONBLOCK) == -1) {
    perror("FLAGS SET");
    exit(EXIT_FAILURE);
  }

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
          if ((csock = accept(lsock,NULL,NULL)) == -1) {
            perror("ACCEPT");
            exit(EXIT_FAILURE);
          }
          
          ev.events = EPOLLIN | EPOLLONESHOT; 
          ev.data.fd = csock;
          flags = fcntl(csock, F_GETFL , 0);
          if (flags == -1) {
            perror("FLAGS GET");
            exit(EXIT_FAILURE);
          }
          if (fcntl(csock, F_SETFL , flags | O_NONBLOCK) == -1) {
            perror("FLAGS SET");
            exit(EXIT_FAILURE);
          }
          if (epoll_ctl(epollfd, EPOLL_CTL_ADD, csock, &ev) == -1) {
            perror("epoll_ctl: listen_sock");
            exit(EXIT_FAILURE);
          }
        } 
        else {

          handle_conn(events[n].data.fd);
          ev.events = EPOLLIN | EPOLLONESHOT; 
          ev.data.fd = events[n].data.fd;

          if (epoll_ctl(epollfd, EPOLL_CTL_MOD, events[n].data.fd, &ev) == -1) {
            perror("epoll_ctl: listen_sock");
            exit(EXIT_FAILURE);
          }
        }
    }
  }

  //wait_for_clients(lsock);
  return 0;
}
