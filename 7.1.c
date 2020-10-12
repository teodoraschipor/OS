//Write a program that manages the access to a finite number of resources. Several threads may require some of the resources at the same time which will give them back once they are no longer useful.
//The maximum number of given resources: #define MAXRESOURCES 5
//int available_resources = MAX_RESOURCES;
//The thread calls decrease_count when it wants to obtain a number of resources.
//The thread calls increase_count when the resources are no longer useful. 

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count) {
	pthread_mutex_lock(&mtx);/////CRITICAL ZONE
	if(available_resources >= count) {
		available_resources -= count;
		printf("Got %d resources %d remaining\n", count, available_resources);
	}
	else {
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	pthread_mutex_unlock(&mtx);
	return 0;
}

int increase_count(int count) {
	pthread_mutex_lock(&mtx);
	if( available_resources + count <= MAX_RESOURCES) {
		available_resources += count;
		printf("Released %d resources %d remaining\n", count, available_resources);
	}
	else {
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	pthread_mutex_unlock(&mtx);
	return 0;
}

void* thread(void*arg) {
	if(decrease_count((*(int*)arg)) == -1) {
		printf("Eroare la alocarea de resurse\n");
		return NULL;
	}
	else {
		increase_count((*(int*)arg));
	}
	return NULL;
}

int get_count() {
	return rand() % MAX_RESOURCES + 1;
}

int main(char argc, char *argv[]) {
	printf("MAX_RESOURCES=%d\n", MAX_RESOURCES);
	if(pthread_mutex_init(&mtx, NULL) != 0) {
		perror(NULL);
		return errno;
	}
	int *resources = (int*)malloc(sizeof(int) * MAX_RESOURCES);
	pthread_t* thr = (pthread_t*)malloc(MAX_RESOURCES * sizeof(pthread_t));
	for(int i = 0; i < MAX_RESOURCES; ++i) {
		*(resources + i) = get_count();
		pthread_t t;
		if(pthread_create(&t, NULL, thread, resources + i)) {
			while(--i) {
				pthread_join(thr[i], NULL);
			}
			free(resources);
			free(thr);
			pthread_mutex_destroy(&mtx);
			perror(NULL);
			return errno;
		}
		thr[i] = t;
	}
	for(int i = 0; i < MAX_RESOURCES; ++i) {
		pthread_join(thr[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	free(resources);
	free(thr);
	return 0;
}
