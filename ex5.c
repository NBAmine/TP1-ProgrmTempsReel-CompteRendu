#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_TASKS 4

typedef struct{
    int id;
    int duree;
}PeriodicTask;

void *taskFunction(void *arg){
    PeriodicTask* task = (PeriodicTask*)arg;

    //Configurer le thread pour qu'il soit annulabe
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    while (1){

        sleep(task->duree);
        printf("Execution de la tache %d\n",task->id);

        /*
            Point d'annulation, dans notre exemple, a chaque fois que le thread arrive a ce point
            il verifie si il a recu une demande d'annulation de la part du programme main
        */
        pthread_testcancel();
    }
    return NULL;
}
int main(){

    int periods[NUM_TASKS] = {1,2,3,4};
    PeriodicTask tasks[NUM_TASKS];
    pthread_t threads[NUM_TASKS];
    int i;

    /*
        Creation des threads, en passant comme argument une structure PeriodicTask contenant l'id
        du thread et la duree de suspension du thread (sleep)
    */
    for(i = 0 ;  i < NUM_TASKS ; i++){
        tasks[i].id = i+1;
        tasks[i].duree = periods[i];
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]);
    }

    //Envoyer une demande d'annulation et attendre la fin de l'execution a tous les threads, 
    for(i = 0 ; i < NUM_TASKS ; i++){
        pthread_cancel(threads[i]);
        pthread_join(threads[i],NULL);
    }
    return 0;
}