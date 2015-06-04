#ifndef ECHANGEUR_H_INCLUDED
#define ECHANGEUR_H_INCLUDED


#include <pthread.h>
#include <stdio.h>
#include "structures.h"
#include <pthread.h>
void* traitantThreadEchangeur(void* param);

void creationEchangeur(echangeur *c,int Id,int D,int G,int H,int B);
void afficherEchangeur(echangeur* c);

void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee);
void afficherVehicule(vehicule* v);
#endif //ECHANGEUR_H_INCLUDED
