#ifndef Voiture_H_INCLUDED
#define Voiture_H_INCLUDED


#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "structures.h"
#include "serveur.h"
void* traitantThreadGenerationVoiture(void* param);

#endif
