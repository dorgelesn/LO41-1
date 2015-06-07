#ifndef Voiture_H_INCLUDED
#define Voiture_H_INCLUDED


#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "structures.h"
#include "serveur.h"

void* traitantThreadGenerationVoiture(void* param);
void* traitantThreadVehicule(void* param);
void creationVehicule(vehicule* v,int idVehicule,int idEchangeur,int depart,int arrivee);
void afficherVehicule(vehicule* v);
void affichageVehicule();

#endif