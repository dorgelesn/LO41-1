#include "voiture.h"

void* traitantThreadGenerationVoiture(void* param){
  sleep(3);
  vehicule* vehic;
  int i=0;
  int d,a,id;
  srand(time(NULL));
  while(i!=2){
    id=rand()%4+1;
    d=id;
    do{
      a=rand()%4+1;
    }while(a==d);
    pthread_mutex_lock(&mutex);
  //  printf("\ncreation d'une voiture qui part de l'echangeur : %d et arrive a %d",d,a);
    vehic = ajouterVehicule(&serv,id,d,a);
    //printf("\n la voiture envoit le signal");
    pthread_cond_signal (&attendre);
    pthread_mutex_unlock(&mutex);
    sleep(1);
    i++;
    }

    printf("\nfin du thread voiture");

}
