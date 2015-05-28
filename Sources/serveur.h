#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED
#include "structures.h"
#include "linkedList.h"
#include <stdio.h>
void* traitantThreadServeur(void* param);
void afficherServeur(serveur* s);
void ajouterVoiture(serveur* serv,int ech,int dep,int arr);
#endif
