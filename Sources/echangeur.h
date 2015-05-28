#ifndef ECHANGEUR_H_INCLUDED
#define ECHANGEUR_H_INCLUDED
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <stdio.h>

#include "structures.h"

void* traitantThreadEchangeur(void* param);

void creationEchangeur(echangeur *c,int Id,int D,int G,int H,int B);
void afficherEchangeur(echangeur* c);


void creationVehicule(vehicule* v,int IdEchangeur,int depart,int arrivee);
void afficherVehicule(vehicule* v);
#endif //ECHANGEUR_H_INCLUDED
