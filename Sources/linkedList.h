#ifndef LINKED_H_INCLUDED
#define LINKED_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"


llist initialisation();

llist ajouterEnTeteListe(llist liste, vehicule* valeur);

llist ajouterEnFin(llist liste, vehicule* valeur);

bool estVide(llist liste);

llist supprimerElementEnTete(llist liste);

llist supprimerElementEnFin(llist liste);

llist supprimerElementById(llist liste, int id);

llist rechercherElement(llist liste, vehicule valeur);

int rechercherPlaceById(llist liste, int valeur);

int rechercherPlaceByReady(llist liste, bool valeur);

void afficherListe(llist liste);

llist element_i(llist liste, int indice);

int nombreElements(llist liste);

llist effacerListe(llist liste);

bool resteVoiture(llist liste,int numroEchan);

int rechercherPlaceByReadyPriority(llist liste, bool valeur);


void reinitialiserPrioEchan(llist liste,int numEchan);
#endif //SERVEUR_H_INCLUDED
