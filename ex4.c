#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func1(void *arg) {
	printf("Thread 1: Bonjour !\n");
	return NULL;
}

void *thread_func2(void *arg) {
	printf("Thread 2: Salut !\n");
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t1;
	pthread_t t2;
	
	//creation et lancement du thread 1
	if (pthread_create(&t1, NULL, thread_func1, NULL) != 0) {
		perror("thread creation error");
		return EXIT_FAILURE;
	}
	
	//creation et lancement du thread 2
	if (pthread_create(&t2, NULL, thread_func2, NULL) != 0) {
		perror("thread creation error");
		return EXIT_FAILURE;
	}
	
	//attendre la fin d'execution du thread 1
	if(pthread_join(t1, NULL) !=0){
        perror("Error");
        EXIT_FAILURE;
    }
    
	//attendre la fin d'execution du thread 1
    if(pthread_join(t2, NULL) !=0){
        perror("Error");
        EXIT_FAILURE;
    }
	
	return EXIT_SUCCESS;
}
