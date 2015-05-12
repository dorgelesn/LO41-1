/**
 * \file main.c
 * \brief Simulation de carrefours routiers intelligents
 * \author Florian Lacour & Michaël Ayeng
 * \version 0.1
 * \date 12 Mai 2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

/**
 * \fn int main(int argc, char *argv[])
 * \brief Fonction de base du programme
 * 
 * \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
 * \param argv Tableau de caractère contenant les arguments de la ligne de commande
 * \return Renvoi 0 si le programme s'est déroulé normalement 
 */
int main(int argc, char *argv[])
{
    menuPrincipal();

    return 0;
}
