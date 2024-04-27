#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *Tachel (void *arg) {
	int i=0;
	while(i<5){
		printf("Execution de Tache 1\n");
		sleep (1);
		i++;
	}
	return NULL;
}


void *Tache2 (void *arg) {
	int j=0;
	while (j<3){
		printf("Execution de Tache 2\n");
		sleep (2);
		j++;
	}
	return NULL;
}

/*
	Test 1, on cree le thread1 et le thread2 et on les execute parallelement, et a l'ordonnonceur de choisir
	comment les ordonnancer
	
	Test 2, on cree le thread1 et on le lance jusqu'a sa fin d'execution,
	puis on cree le thread2 et on le lance jusqu'a sa fin d'execution
*/

//Test 1
// int main(int argc, char *argv[]){
// 	pthread_t thread1, thread2;
// 	pthread_create(&thread1, NULL, Tachel, NULL);
// 	pthread_create(&thread2, NULL, Tache2, NULL);
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
// 	return EXIT_SUCCESS;
// }

//Test 2
int main(int argc, char *argv[]){
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, Tachel, NULL); 
	pthread_join(thread1, NULL);
	pthread_create(&thread2, NULL, Tache2, NULL);
	pthread_join(thread2, NULL);
	return EXIT_SUCCESS;
}




