#ifndef ECHANGEUR_H_INCLUDED
#define ECHANGEUR_H_INCLUDED


#include <pthread.h>
#include <stdio.h>
#include "structures.h"
#include <pthread.h>
#include <stdint.h>
void* traitantThreadEchangeur(void* param);
void creationEchangeur(echangeur *c,int Id,int D,int G,int H,int B);
void afficherEchangeur(echangeur* c);
void affichageEchangeur();

#endif //ECHANGEUR_H_INCLUDED
