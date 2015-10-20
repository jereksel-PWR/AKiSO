#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *create_thread_from_thread()
{
	printf("Wątek z wątku\n");
	return NULL;
}


void *create_thread()
{

	pthread_t tcb2;
	void *status2;

	if (pthread_create(&tcb2, NULL, create_thread_from_thread, NULL) != 0)
	{
		perror("thread create");
		exit(1);
	}


	if (pthread_join(tcb2, &status2) != 0)
	{
		perror("thread join");
		exit(1);
	}

	return NULL;

}


int main(void)
{

	pthread_t tcb;
	void *status;


	if (pthread_create(&tcb, NULL, create_thread, NULL) != 0)
	{
		perror("thread create");
		exit(1);
	}


	if (pthread_join(tcb, &status) != 0)
	{
		perror("thread join");
		exit(1);
	}

	return 0;

}
