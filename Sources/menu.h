#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


void menuPrincipal(int*, int*);
void executionStandard(int*, int*);
void executionParametree(int*, int*);
void aPropos(void);



typedef struct voiture voiture;
struct voiture {
  int depart;
  int arriver;
};
// ajout pour les liste de message
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void erreur(const char *msg);
int creationFile(void*);

typedef struct {
  long type;
  voiture V;
  pid_t numPid;
} message;

void envoitMessage(int msgid,int numeroEchangeur,voiture V);
// fin ajout pour les liste


#endif // MENU_H_INCLUDED
