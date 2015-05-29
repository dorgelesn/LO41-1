#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED

#include <stdio.h>
#include "structures.h"
#include "linkedList.h"

void* traitantThreadServeur(void* param);
void afficherServeur(serveur* s);
void ajouterVehicule(serveur* serv,int ech,int dep,int arr);

#endif
