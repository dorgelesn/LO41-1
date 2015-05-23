#ifndef MESSAGERIE_H_INCLUDED
#define MESSAGERIE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
// Librairies nécessaires aux files de message
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// lib pour les signaux
#include <signal.h>

// Structure des véhicules
typedef struct vehicule {
  int depart;
  int arrivee;
} vehicule;


// Structure des messages
typedef struct message {
  long type;
  vehicule vehicule;
  pid_t numPid;
} message;


int creationFile(void*);
void envoieMessage(int msgid,int numeroEchangeur,vehicule vehicule);
void erreur(const char *msg);

#endif // MESSAGERIE_H_INCLUDED
