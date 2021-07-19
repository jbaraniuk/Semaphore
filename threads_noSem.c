//Justin Baraniuk 

#include <pthread.h>
#include <stdio.h>

int t;

void* thread_adder_nosem(void* arg){ 
  for (int i = 0; i < 20; i++){
	int x = t;
	x = x + 1;
	printf("adding %d time\n", i);
	t = x;
  }
  return &t;
}

void* thread_subtracter_nosem(void* arg){
  for (int i = 0; i < 20; i++){
	int x = t;
	x = x - 1;
	printf("subtracting %d time\n", i);
	t = x;
  }  
  return &t;
}

int main(){
	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, thread_adder_nosem, NULL);
	pthread_create(&t2, NULL, thread_subtracter_nosem, NULL);	
	pthread_create(&t3, NULL, thread_adder_nosem, NULL);
	pthread_create(&t4, NULL, thread_subtracter_nosem, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	printf("Adder01 completed...\n");
	printf("Subtracter01 completed...\n");
	printf("Adder02 completed...\n");
	printf("Subtracter02 completed...\n");
	printf("Value received by parent process from last subtracter thread: %d\n", t);
	
	return 0;
}