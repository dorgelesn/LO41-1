/**
* \file linkedList.c
* \brief Fonctions de gestion de listes chainées
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 28 Mai 2015
*/

#include "linkedList.h"
#include "structures.h"

/**
* \fn lliste initalisation()
* \brief Fonction permettant l'initialisation de la liste chainée
*
* \return Renvoi un premier élément servant de base pour la liste chainée
*/
llist initialisation()
{
  llist liste = malloc(sizeof(element));
  liste->val=NULL;
  liste->nxt==NULL;
  return liste;
}

/**
* \fn llist ajouterEnTeteListe(llist liste, vehicule* valeur)
* \brief Fonction permettant l'ajout d'un vehicule en début de la liste chainée
*
* \param liste La liste chainée que l'on manipule
* \param valeur Le véhicule que l'on souhaite placé en tête de la liste
*
* \return Renvoi un pointeur sur le premier élément de la liste
*/
llist ajouterEnTeteListe(llist liste, vehicule* valeur)
{
    /* On crée un nouvel élément */
    llist nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->val = valeur;

    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->nxt = liste;

    /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
    return nouvelElement;
}

/**
* \fn llist ajouterEnFin(llist liste, vehicule* valeur)
* \brief Fonction permettant l'ajout d'un vehicule en fin de la liste chainée
*
* \param liste La liste chainée que l'on manipule
* \param valeur Le véhicule que l'on souhaite placé en fin de la liste
*
* \return Renvoi un pointeur sur le premier élément de la liste
*/
llist ajouterEnFin(llist liste, vehicule* valeur)
{
    /* On crée un nouvel élément */
    element* nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->val = valeur;

    /* On ajoute en fin, donc aucun élément ne va suivre */
    nouvelElement->nxt = NULL;

    if(liste == NULL)
    {
        /* Si la liste est videé il suffit de renvoyer l'élément créé */
        return nouvelElement;
    }
    else
    {
        /* Sinon, on parcourt la liste à l'aide d'un pointeur temporaire et on
        indique que le dernier élément de la liste est relié au nouvel élément */
        element* temp=liste;
        while(temp->nxt != NULL)
        {
            temp = temp->nxt;
        }
        temp->nxt = nouvelElement;
        return liste;
    }
}

/**
* \fn int estVide(llist liste)
* \brief Fonction permettant de savoir si la liste chainée est vide
*
* \param liste La liste chainée que l'on manipule
* \return Renvoi true ou false
*/
bool estVide(llist liste)
{
    if(liste == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
* \fn llist supprimerElementEnTete(llist liste)
* \brief Fonction permettant de supprimant l'élément en tête de la liste chainée
*
* \param liste La liste chainée que l'on manipule
* \return Renvoi le nouveau premier élément de la liste chainée
*/
llist supprimerElementEnTete(llist liste)
{
    if(liste != NULL)
    {
        /* Si la liste est non vide, on se prépare à renvoyer l'adresse de
        l'élément en 2ème position */
        element* aRenvoyer = liste->nxt;
        /* On libère le premier élément */
        free(liste);
        /* On retourne le nouveau début de la liste */
        return aRenvoyer;
    }
    else
    {
        return NULL;
    }
}

void afficherListe(llist liste){
  printf("\n [Liste] actuellemnt present : ");
  if(liste == NULL)
  {

  }
  else
  {

      element* temp=liste;

      while(temp->nxt != NULL)
      {
        printf("%d ",temp->val->idEchangeur);
          temp = temp->nxt;
      }

  }

}

llist supprimerElementById(llist liste, int id){

  if(liste != NULL)
  { int place;

    place=rechercherPlaceById(liste,id);
    if(place==-1){
      return NULL;
    }
    if(place==0){
      return supprimerElementEnTete(liste);
    }
    if(place==nombreElements(liste)){
      supprimerElementEnFin(liste);
    }
    int i;
    element* tmp = liste;
    element* ptmp = liste;
    for(i=0;i<place;i++){
      /* ptmp stock l'adresse de tmp */
      ptmp = tmp;
      /* On déplace tmp (mais ptmp garde l'ancienne valeur de tmp */
      tmp = tmp->nxt;
    }
    element* ntmp = tmp->nxt;
    free(tmp);
    ptmp->nxt=ntmp;
    return liste;
  }
  else
  {
      return NULL;
  }
}




/**
* \fn llist supprimerElementEnFin(llist liste)
* \brief Fonction permettant de supprimant l'élément à la fin de la liste chainée
*
* \param liste La liste chainée que l'on manipule
* \return Renvoi le premier élément de la liste chainée
*/
llist supprimerElementEnFin(llist liste)
{
    /* Si la liste est vide, on retourne NULL */
    if(liste == NULL)
        return NULL;

    /* Si la liste contient un seul élément */
    if(liste->nxt == NULL)
    {
        /* On le libère et on retourne NULL (la liste est maintenant vide) */
        free(liste);
        return NULL;
    }

    /* Si la liste contient au moins deux éléments */
    element* tmp = liste;
    element* ptmp = liste;
    /* Tant qu'on n'est pas au dernier élément */
    while(tmp->nxt != NULL)
    {
        /* ptmp stock l'adresse de tmp */
        ptmp = tmp;
        /* On déplace tmp (mais ptmp garde l'ancienne valeur de tmp */
        tmp = tmp->nxt;
    }
    /* A la sortie de la boucle, tmp pointe sur le dernier élément, et ptmp sur
    l'avant-dernier. On indique que l'avant-dernier devient la fin de la liste
    et on supprime le dernier élément */
    ptmp->nxt = NULL;
    free(tmp);
    return liste;
}


int rechercherPlaceByReady(llist liste, bool valeur){

  element *tmp=liste;
  int i=0;
  /* Tant que l'on n'est pas au bout de la liste */
  while(tmp != NULL)
  {
      if(tmp->val->ready == valeur)
      {
          /* Si l'élément a la valeur recherchée, on renvoie son adresse */
          return i;
      }
      tmp = tmp->nxt;
      i++;
  }
  return -1;
}


int rechercherPlaceById(llist liste, int valeur){
  element *tmp=liste;
  int i=0;
  /* Tant que l'on n'est pas au bout de la liste */
  while(tmp != NULL)
  {
      if(tmp->val->idVehicule == valeur)
      {
          /* Si l'élément a la valeur recherchée, on renvoie son adresse */
          return i;
      }
      tmp = tmp->nxt;
      i++;
  }
  return -1;
}

/**
* \fn llist rechercherElement(llist liste, vehicule valeur)
* \brief Fonction permettant de trouvant l'élément de la liste possédant un véhicule particulière
*
* \param liste La liste chainée que l'on manipule
* \param valeur Le véhicule à trouver dans la liste
*
* \return Renvoi l'élément contenant la valeur cherchée
*/
llist rechercherElement(llist liste, vehicule valeur)
{
    element *tmp=liste;
    /* Tant que l'on n'est pas au bout de la liste */
    while(tmp != NULL)
    {
        if(tmp->val->depart == valeur.depart &&tmp->val->arrivee == valeur.arrivee)
        {
            /* Si l'élément a la valeur recherchée, on renvoie son adresse */
            return tmp;
        }
        tmp = tmp->nxt;
    }
    return NULL;
}

/**
* \fn llist element_i(llist liste, int indice)
* \brief Fonction permettant d'accéder au n-ième élément de la liste
*
* \param liste La liste chainée que l'on manipule
* \param indice Numéro de l'élément que l'on souhaite obtenir
*
* \return Renvoi l'élément à l'indice demandé
*/
llist element_i(llist liste, int indice)
{
    int i;
    /* On se déplace de i cases, tant que c'est possible */
    for(i=0; i<indice && liste != NULL; i++)
    {
        liste = liste->nxt;
    }

    /* Si l'élément est NULL, c'est que la liste contient moins de i éléments */
    if(liste == NULL)
    {
        return NULL;
    }
    else
    {
        /* Sinon on renvoie l'adresse de l'élément i */
        return liste;
    }
}

/**
* \fn int nombreElements(llist liste)
* \brief Fonction permettant d'obtenir le nombre d'élément de la liste chainée
*
* \param liste La liste chainée que l'on manipule
*
* \return Renvoi le nombre d'élément que contient la liste
*/
int nombreElements(llist liste)
{
    /* Si la liste est vide, il y a 0 élément */
    if(liste == NULL)
        return 0;

    /* Sinon, il y a un élément (celui que l'on est en train de traiter)
    plus le nombre d'éléments contenus dans le reste de la liste */
    return nombreElements(liste->nxt)+1;
}

/**
* \fn llist effacerListe(llist liste)
* \brief Fonction permettant d'effacer le contenu d'une liste chainée
*
* \param liste La liste chainée que l'on manipule
*
* \return Renvoi un pointeur NULL
*/
llist effacerListe(llist liste)
{
    if(liste == NULL)
    {
        /* Si la liste est vide, il n'y a rien à effacer, on retourne
        une liste vide i.e. NULL */
        return NULL;
    }
    else
    {
        /* Sinon, on efface le premier élément et on retourne le reste de la
        liste effacée */
        element *tmp;
        tmp = liste->nxt;
        free(liste);
        return effacerListe(tmp);
    }
}

bool resteVoiture(llist liste,int ready){
  element *tmp=liste;
  /* Tant que l'on n'est pas au bout de la liste */
  while(tmp != NULL)
  {
      if(tmp->val->ready == ready)
      {
          /* Si l'élément a la valeur recherchée, on renvoie son adresse */
          return true;
      }
      tmp = tmp->nxt;
  }
  return false;
}
