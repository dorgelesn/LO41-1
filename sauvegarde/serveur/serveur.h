#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED
#include <stdlib.h>


typedef struct vehicule {
  int depart;
  int arrivee;
} vehicule;

typedef struct message {
  long type;
  vehicule vehicule;
  pid_t numPid;
} message;


typedef struct element element;
struct element
{
  vehicule val;
    struct element *nxt;
};

typedef element* llist;


llist ajouterEnTete(llist liste, vehicule valeur);

llist ajouterEnFin(llist liste, vehicule valeur);

int estVide(llist liste);

llist supprimerElementEnTete(llist liste);

llist supprimerElementEnFin(llist liste);

llist rechercherElement(llist liste, vehicule valeur);

llist element_i(llist liste, int indice);

int nombreElements(llist liste);

llist effacerListe(llist liste);
#endif //SERVEUR_H_INCLUDED
