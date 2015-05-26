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

/**
*\struct vehicule
*\brief Objet representant une voiture
*
* depart represente l'Id de l'echangeur de depart de la voiture
* arrivee represente l'Id de l'echangeur d'arrivée de la voiture
**/
typedef struct vehicule {
  int depart;
  int arrivee;
} vehicule;


/**
*\struct message
*\brief Objet representant un message
*
* type represente le type du message
* vehicule represente le vehicule emetteur du message
* numPid represente le PID du processus dont fait partie le vehicule
**/
typedef struct message {
  long type;
  vehicule vehicule;
  pid_t numPid;
} message;


int creationFile(void*);
void envoieMessage(int msgid,int numeroEchangeur,vehicule vehicule, message* a;);
void erreur(const char *msg);

#endif // MESSAGERIE_H_INCLUDED
