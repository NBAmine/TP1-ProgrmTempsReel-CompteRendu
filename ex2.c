#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg) {
	//On fait un cast comme char a l'argument et on l'affiche
	char *msg = (char *) arg;
	printf("Message = %s\n", msg);
	return NULL;
}

int main(int argc, char *argv[]) {
	//On cree une thread et on lui passe une chaine de caractere comme argument
	pthread_t t;
	char *msg = "Threads are awesome!";
	if (pthread_create(&t, NULL, func, msg) != 0) {
		perror("thread creation error");
		return EXIT_FAILURE;
	}
	//Le programme main attend la fin d'execution du thread
	if(pthread_join(t, NULL) !=0){
        perror("Error");
        EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
