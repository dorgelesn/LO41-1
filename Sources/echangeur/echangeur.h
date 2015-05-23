#ifndef ECHANGEUR_H_INCLUDED
#define ECHANGEUR_H_INCLUDED
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
typedef struct vehicule {
  int depart;
  int arrivee;
} vehicule;

typedef struct message {
  long type;
  vehicule vehicule;
  pid_t numPid;
} message;

void main(int argc, char *argv[]);
void* traitantThread(void* param);
#endif //ECHANGEUR_H_INCLUDED
