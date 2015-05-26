#ifndef ECHANGEUR_H_INCLUDED
#define ECHANGEUR_H_INCLUDED
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdio.h>
/**
*\struct vehicule
*\brief Objet represenatant une voiture
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


/**
*\struct echangeur
*\brief Objet represenatant un echangeur
*
* numId represente l'identifiant de l'echangeur
* haut est l'ID de l'echangeur au dessus du notre
* bas est l'ID de l'echangeur en bas du notre
* droite est l'ID de l'echangeur a droite du notre
* gauche est l'ID de l'echangeur a gauche du notre
*         Schema des connexions :
*            0        0
*           ||       ||
*    0== |  1  |== | 4 | == 0
*           ||       ||
*    0 == | 2  | == | 3 | == 0
*           ||        ||
*            0         0
*
**/
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
