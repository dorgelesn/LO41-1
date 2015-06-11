#ifndef Voiture_H_INCLUDED
#define Voiture_H_INCLUDED


#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include "structures.h"
#include "serveur.h"
#include <fcntl.h>
#include <semaphore.h>
void* traitantThreadGenerationVoiture(void* param);
void* traitantThreadVehicule(void* param);
void creationVehicule(vehicule* v,int idVehicule,int idEchangeur,int depart,int arrivee);
void afficherVehicule(vehicule* v);
void affichageVehicule();
bool dejaParcourus(vehicule* v,int ech);

#endif
