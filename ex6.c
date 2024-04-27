#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_TAB 19
#define NUM_THREADS 5

int sum = 0;
pthread_mutex_t lock;

typedef struct
{
    int *debut;
    int *fin;
} PartialSumArgs;

void *sum_partial(void *args)
{

    PartialSumArgs *partialArgs = (PartialSumArgs *)args;
    int partialSum = 0;
    int *p;

    //on calcule la somme partiel de notre section du tableau definit par les pointeurs debut et fin.
    for (p = partialArgs->debut; p < partialArgs->fin; p++)
    {
        partialSum += *p;
    }

    /*
        mutex, primitive de synchronization permet a un seul thread d'acceder a une ressource critique
        a la fois, la fonction pthread_mutex_lock permet d'acquerir le mutex qui nous permet d'ajouter
        notre somme partiel a la somme total, si le mutex est encore d'utilisation par un autre thread
        on attend jusqu'a sa liberation puis on le saisie. 
    */
    pthread_mutex_lock(&lock);

    sum += partialSum;

    pthread_mutex_unlock(&lock);
}

int main()
{
    //creation de la table des nombres
    int nombres[TAILLE_TAB];
    int i;
    for (i = 0; i < TAILLE_TAB; ++i)
    {
        nombres[i] = i + 1;
    }

    /* 
        creation de les tables de threads et structue(PartialSumArgs) contenant deux pointeurs sur le
        debut et la fin d'une section du tableau que le thread va en calculer la somme
        int range : le nombre des nombres du tableau affecter a chaque thread (sauf la derniere thread 
        dans des cas speciales)
        cas speciale : (10 nombres dans le tableau et 3 thread), le thread 1 et 2 vont calculer la
        somme de trois nombre du tableau et le thread 3 va calculer la somme des quatres dernier elements
    */
    pthread_t threads[NUM_THREADS];
    PartialSumArgs partialSumArgs[NUM_THREADS];
    int range = TAILLE_TAB / NUM_THREADS;

    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < NUM_THREADS; i++)
    {
        partialSumArgs[i].debut = nombres + i * range;
        partialSumArgs[i].fin = nombres + ((i == NUM_THREADS - 1) ? TAILLE_TAB : (i+1) *range);
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&partialSumArgs[i]) != 0)
        {
            perror("Erreur");
            return EXIT_FAILURE;
        }
    }

    //attendre la fin d'execution de tous les threads
    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Somme totale : %d\n", sum);

    pthread_mutex_destroy(&lock);

    return 0;
}