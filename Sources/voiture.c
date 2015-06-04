#include "voiture.h"

void* traitantThreadVoiture(void* param){

  pthread_mutex_lock(&mutex);
  vehicule* ech= (vehicule*) param;
    // Utilisation Mutex ????
    printf("\ncreation d'une voiture");
    printf("\n\n voiture %d",ech->arrivee);
    fflush(stdout);
    printf("\n la voiture envoit le signal");
    pthread_cond_signal (&attendre);
    sleep(2);
    pthread_mutex_unlock(&mutex);
    printf("\nfin du thread voiture");
    pthread_exit(NULL);
}
