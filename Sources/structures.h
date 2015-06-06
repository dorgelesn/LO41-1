#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
#define maxiVoiture 100
#define maxiEchangeur 4
#include <stdbool.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_cond_t attendre;
pthread_cond_t dispoEchangeur[maxiEchangeur];
/*
pour la syncro des voiture avec le serveur :
thread_cond_t attendre[maxiVoiture]=> initialisation !! ctrl+c
quand l'echangeur est cispo (bool) alors l'echangeur envoit un signal au thread qui est en attente et se mais lui méme




*/
/**
*\struct vehicule
*\brief Objet representant un vehicule
*
* depart Represente l'Id de l'echangeur de depart de la voiture
* arrivee Represente l'Id de l'echangeur d'arrivée de la voiture
**/
typedef struct vehicule {
  //int precedent; ????
  int IdEchangeur;
  int depart;
  int arrivee;
} vehicule;

/**
*\struct element
*\brief Objet representant un élément de liste chainée
*
* val Pointeur sur un vehicule
* nxt Pointeur sur l'élément suivant
**/
typedef struct element
{
    vehicule* val;
    struct element* nxt;
} element;

typedef element* llist;

/**
*\struct echangeur
*\brief Objet represenatant un echangeur
*
* numId represente l'identifiant de l'echangeur
* haut est l'ID de l'echangeur au dessus du notre
* bas est l'ID de l'echangeur en bas du notre
* droite est l'ID de l'echangeur a droite du notre
* gauche est l'ID de l'echangeur a gauche du notre
* occuper sert a savoir si un vehicule utilise le carrefour
*         Schema des connexions :
*            0        0
*           ||       ||
*    0== |  1  |== | 4 | == 0
*           ||       ||
*    0 == | 2  | == | 3 | == 0
*           ||        ||
*            0         0
*
*
**/
typedef struct echangeur {
  int numId;
  int haut;
  int bas;
  int droite;
  int gauche;
  bool occuper;
} echangeur;

/**
*\struct serveur
*\brief Objet representant le serveur
*
* NbVoiture Représente le nombre de véhicules gérés par le serveur
* NbEchangeur Représente le nombre d'échangeurs gérés par le serveur
* liste Contient la liste chainée
**/
typedef struct serveur{
  int NbVoiture;
  int NbEchangeur;
  llist liste;
} serveur;
serveur serv;
#endif
