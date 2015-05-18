/**
* \file messagerie.c
* \brief Liens de communication entre processus
* \author Florian Lacour & Michaël Ayeng
* \version 0.1
* \date 18 Mai 2015
*/

#include "messagerie.h"

void envoieMessage(int msgid,int numeroEchangeur,vehicule vehicule){
  message a;

  a.type = numeroEchangeur;
  a.vehicule = vehicule;
  a.numPid = getpid();

  if(msgsnd(msgid,&a,sizeof(message) - sizeof(long),0)){
    perror("Erreur d'envoit requete");
    exit(1);
  }

}

int creationFile(void *a){
  int msgid;			/* valeur de retour de la creation de la file */
  key_t key;			/* valeur de retour de la creation de la clé */
  /****************************************************************/
  /*  Creation de la clé IPC 					*/
  /****************************************************************/
  if ((key = ftok((char*)a, 'A')) == -1) {
    perror("Erreur de creation de la clé \n");
    exit(1);
  }
  /****************************************************************/
  /* Creation de la file de message 				*/
  /* int msgget(key_t key, int msgflg);				*/
  /****************************************************************/

  if ((msgid = msgget(key, 0750 | IPC_CREAT | IPC_EXCL)) == -1) {
    perror("Erreur de creation de la file\n");
    exit(1);
  }
  return msgid;
}

void erreur(const char *msg)
{
  perror(msg);
  exit(1);
}
