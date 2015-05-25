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


typedef struct echangeur {
  int numId;
  int haut;
  int bas;
  int droite;
  int gauche;
} echangeur;




void creationEchangeur(echangeur *c,int Id,int D,int G,int H,int B);
void afficherEchangeur(echangeur* c);
#endif //ECHANGEUR_H_INCLUDED
