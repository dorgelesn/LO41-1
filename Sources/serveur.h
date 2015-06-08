#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED

#include <stdio.h>
#include "structures.h"
#include "linkedList.h"
#include <pthread.h>

void* traitantThreadServeur(void* param);
void afficherServeur(serveur* s);
vehicule* ajouterVehicule(serveur* serv,int id, int ech,int dep,int arr);
void affichageServeur();

#endif
