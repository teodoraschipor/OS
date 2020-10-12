//Write a program that synchronizes the execution of N threads by creating a barrier object. The barrier will be initialized using init(N) and each thread will call barrier_point() when it will arrive at barrier.It will start the execution of all threads that are waiting, when the function is called for the Nth time.
//Verify your results with a program that starts several threads that use the barrier to synchronize their execution.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NTHRS 5

pthread_mutex_t mtx;
sem_t sem;
int count;

void barrier_point() {
	pthread_mutex_lock(&mtx);//critical zone
	count++;
	if(count == NTHRS) {
		for(int i = 0; i < NTHRS - 1; ++i)
			sem_post(&sem);
		count = 0;
		pthread_mutex_unlock(&mtx);
		return;
	}
	pthread_mutex_unlock(&mtx);
	sem_wait(&sem);
}

void* thr_job(void* arg) {
	int tid = (int)arg;
	printf("%d reached the barrier\n", tid);
	barrier_point();
	printf("%d passed the barrier\n", tid);
	return NULL;
}

int main(char argc, char *argv[]) {
	printf("NTHRS=%d\n", NTHRS);
	if(pthread_mutex_init(&mtx, NULL) != 0) {
		perror(NULL);
		return errno;
	}
	if(sem_init(&sem, 0, 0)) {
		perror(NULL);
		return errno;
	}
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * NTHRS);
	for(int i = 0; i < NTHRS; ++i) {
		pthread_t tid;
		if(pthread_create(&tid, NULL, thr_job, i)) {
			while(--i) {
				pthread_join(threads[i], NULL);
			}
			free(threads);
			pthread_mutex_destroy(&mtx);
			sem_destroy(&sem);
			perror(NULL);
			return errno;
		}
		threads[i] = tid;
	}
	for(int i = 0; i < NTHRS; ++i) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	return 0;
}
