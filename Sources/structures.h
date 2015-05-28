#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef int bool;
#define true 1
#define false 0
/**
*\struct vehicule
*\brief Objet represenatant une voiture
*
* depart represente l'Id de l'echangeur de depart de la voiture
* arrivee represente l'Id de l'echangeur d'arrivée de la voiture
**/
typedef struct vehicule {
  int IdEchangeur;
  int depart;
  int arrivee;
} vehicule;


/**
*\struct echangeur
*\brief Objet represenatant un echangeur
*
* numId represente l'identifiant de l'echangeur
* haut est l'ID de l'echangeur au dessus du notre
* bas est l'ID de l'echangeur en bas du notre
* droite est l'ID de l'echangeur a droite du notre
* gauche est l'ID de l'echangeur a gauche du notre
*         Schema des connexions :
*            0        0
*           ||       ||
*    0== |  1  |== | 4 | == 0
*           ||       ||
*    0 == | 2  | == | 3 | == 0
*           ||        ||
*            0         0
*
**/
typedef struct echangeur {
  int numId;
  int haut;
  int bas;
  int droite;
  int gauche;
} echangeur;


#endif
