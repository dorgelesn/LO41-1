/**
* \file echangeur.c
* \brief Programme de simulation des échangeurs
* \author Florian Lacour & Michaël Ayeng
* \version 0.2
* \date 13 Mai 2015
*/

#include "echangeur.h"

/**
* \fn void* traitantThread(void* param)
* \brief Fonction gerant un thread "Echangeur"
*
* \param param Pointeur contenant un echangeur
*
*/
void* traitantThreadEchangeur(void* param){

  int numEchangeur, i;
  numEchangeur  = (int) param;
  while(true){
    // Section critique
    pthread_mutex_lock(&mutex);
    affichageEchangeur();
    printf("[Echangeur n°%d] : En attente",numEchangeur+1);
    ech[numEchangeur].dispo = true;
    pthread_cond_wait (&BarriereEchangeur[numEchangeur],&mutex); // Attend le signal d'ouverture du serveur
    ech[numEchangeur].dispo = false;
    affichageEchangeur();
    printf("[Echangeur n°%d] : Ouverture de la barriere",numEchangeur+1);
    pthread_mutex_unlock(&mutex);
    // Fin de section critique
  }
  fflush(stdout);
  pthread_exit(NULL);
}


/**
* \fn void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B)
* \brief Fonction permettant le paramètrage d'un echangeur
*
* \param c Structure de l'échangeur
* \param Id Numéro d'identification de l'échangeur
* \param D Numéro de l'échangeur se trouvant à droite
* \param G Numéro de l'échangeur se trouvant à gauche
* \param H Numéro de l'échangeur se trouvant en haut
* \param B Numéro de l'échangeur se trouvant en bas
*
*/
void creationEchangeur(echangeur* c,int Id,int D,int G,int H,int B){
  c->numId = Id;
  c->haut = H;
  c->bas = B;
  c->droite = D;
  c->gauche = G;
  c->dispo = true;
}

/**
* \fn void afficherEchangeur(echangeur* c)
* \brief Fonction permettant l'affichage d'informations concernant un échangeur
*
* \param c Structure de l'échangeur
*
*/
void afficherEchangeur(echangeur* c){
  printf("\n-----------------------");
  printf("\nInformations echangeur n°%d",c->numId);
  printf("\n-----------------------");
  printf("\n\tConnexion haute: %d\n\tConnexion basse: %d\n\tConnexion gauche: %d\n\tConnexion droite: %d\n\tBlocage: %d",c->haut,c->bas,c->gauche,c->droite,c->dispo);
}

void affichageEchangeur(){
  int i;
  printf("\n");
  for (i = 0; i < 2; i++){
    printf("\t");
  }
}
