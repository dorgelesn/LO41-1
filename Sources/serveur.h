#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED

#include <stdio.h>
#include "structures.h"
#include "linkedList.h"
#include <pthread.h>
void* traitantThreadServeurAjout(void* param);
void afficherServeur(serveur* s);
vehicule* ajouterVehicule(serveur* serv,int ech,int dep,int arr);
void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee);
#endif
