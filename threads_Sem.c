//Justin Baraniuk 

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t mutex;
int t;

void* thread_adder_wsem(void* arg){
  sem_wait(&mutex);    
  for (int i = 0; i < 20; i++){
	int x = t;
	x = x + 1;
	printf("adding %d time\n", i);
	t = x;
  }
  sem_post(&mutex);
  return &t;
}

void* thread_subtracter_wsem(void* arg){
  sem_wait(&mutex);
  for (int i = 0; i < 20; i++){
	int x = t;
	x = x - 1;
	printf("subtracting %d time\n", i);
	t = x;
  }  
  sem_post(&mutex);
  return &t;
}

int main(){
	pthread_t t1, t2, t3, t4;
	sem_init(&mutex, 0, 1);	
	pthread_create(&t1, NULL, thread_adder_wsem, NULL);
	pthread_create(&t2, NULL, thread_subtracter_wsem, NULL);	
	pthread_create(&t3, NULL, thread_adder_wsem, NULL);
	pthread_create(&t4, NULL, thread_subtracter_wsem, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	printf("Adder01 completed...\n");
	printf("Subtracter01 completed...\n");
	printf("Adder02 completed...\n");
	printf("Subtracter02 completed...\n");
	printf("Value received by parent process from last subtracter thread: %d\n", t);
	
	sem_destroy(&mutex);
	
	return 0;
}