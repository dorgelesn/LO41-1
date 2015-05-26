/**
* \file main.c
* \brief Simulation de carrefours routiers intelligents
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 13 Mai 2015
*/

#include <stdio.h>
#include <stdlib.h>

#include "messagerie.h"
#include "menu.h"

int msgid;
void traitantInt(int num){
  printf("\nInterruption avec suppression de la file de messages");
  msgctl(msgid,IPC_RMID,NULL);
  exit(1);
}
/**
* \fn int main(int argc, char *argv[])
* \brief Programme principal de la simulation
*
*
* \param argc Valeur représentant le nombre d'argument passés lors de l'appel du binaire exécutable
* \param argv Tableau de char* contenant le nombre d'échangeur gérer
* \return Renvoi 0 si le programme s'est déroulé normalement
*/
int main(int argc,char *argv[]) {

  int nbEchangeurs, nbVehicules, i;
  char arguments[3][3];

  msgid = creationFile(argv[0]);  // Creation de la file de message
  signal(SIGINT,traitantInt);     // Nettoyage de la file de message nouvellement crééé
  printf("\nCreation de la file de message %d",msgid);
//  menuPrincipal(&nbEchangeurs,&nbVehicules);

  // Pour une execution, passage d'argument via char* uniquement
//  sprintf(arguments[2],"%d",nbVehicules);   // Converti le nombre de vehicules en char*
  //sprintf(arguments[3],"%d",nbEchangeurs);  // Converti le nombre d'échangeur en char*




  // Execution des échangeurs

    if (fork() == 0){
      sprintf(arguments[0],"%d",msgid); // Converti la file de message en char*
         // Converti le numéro d'échangeur en char*
      //sprintf(arguments[2],"%d",nbVehicules);   // Converti le nombre de vehicules en char*
      //sprintf(arguments[3],"%d",nbEchangeurs);  // Converti le nombre d'échangeur en char
      sprintf(arguments[2],"%d",0);   // TEMP: Nb vehicule
      sprintf(arguments[3],"%d",4);  //  TEMP: Nb echangeurs


      // Execute un échangeur en lui passant la file de message, le numéro d'échangeur et le nombre de véhicules
      execlp("./echangeur/echangeur","echangeur",arguments[0],arguments[1],arguments[2],arguments[3],NULL);
      perror("execl()");  // Affiche une eventuelle erreur
      sleep(1); // Temps de repos pour fluidifier l'affichage
    }
    printf("\n\n");


  // Execution du serveur
  if (fork() == 0) {
    printf("\nExecution du serveur");
    // Execute le serveur en lui passant le nombre d'échangeurs
    execl("./serveur/serveur","serveur",arguments[3],arguments[0],NULL);
    perror("execl()");
  }

  sleep(1); // Temps de repos pour fluidifier l'affichage


  /*
  Juste pour teste
  */
  vehicule voit;

  voit.depart = 1;
  voit.arrivee = 0;
  message a;


 envoieMessage(msgid,3,voit,&a);


  sleep(1);


  printf("\nSuppresion de la file de message\n ");
  sleep(10);
  msgctl(msgid,IPC_RMID,NULL);

}
