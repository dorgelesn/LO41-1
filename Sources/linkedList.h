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

void afficherListe(llist liste);

llist element_i(llist liste, int indice);

int nombreElements(llist liste);

llist effacerListe(llist liste);
#endif //SERVEUR_H_INCLUDED
