#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <bits/pthreadtypes.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

//TODO: Nie tylko kwadratowe macierze

#define debug
#define max_random_number 100

sem_t semaforek;
pthread_mutex_t lock;
int **macierzkoncowa;
bool go = false;

//SZEROKOSC|WYSOKOSC
int macierz1_data[2];
int macierz2_data[2];

int **macierz1;
int **macierz2;


void *liczenieMacierzy();

int main(int argc, char *argv[])
{
	pthread_mutex_t lock;

	sem_init(&semaforek, 0, 0);

	int a, i, j;

	if (argc != 6)
	{
		//printf("usage: %s <szerokosc|wysokość macierzy> <liczba wątków>", argv[0]);
		printf("usage: %s <szerokosc 1 macierzy> <wysokosc 1 macierzy> <szerokosc 2 macierzy> <wysokosc 2 macierzy> <liczba wątków>", argv[0]);
		exit(1);
	}

	srand((unsigned int) time(NULL));

	macierz1_data[0] = atoi(argv[1]);
	macierz1_data[1] = atoi(argv[2]);
	macierz2_data[0] = atoi(argv[3]);
	macierz2_data[1] = atoi(argv[4]);
	int watki = atoi(argv[5]);

	macierz1 = malloc(sizeof(int *) * macierz1_data[0]);
	macierz2 = malloc(sizeof(int *) * macierz2_data[0]);
	macierzkoncowa = malloc(sizeof(int *) * macierz2_data[0]);

	if (macierz1_data[0] != macierz2_data[1])
	{
		return 0;
	}


	for (i = 0; i < macierz1_data[0]; i++)
	{
		*(macierz1 + i) = malloc(sizeof(int) * macierz1_data[1]);

		for (j = 0; j < macierz1_data[1]; j++)
		{
			macierz1[i][j] = rand() % max_random_number;
		}

	}

	for (i = 0; i < macierz2_data[0]; i++)
	{
		*(macierz2 + i) = malloc(sizeof(int) * macierz2_data[1]);


		for (j = 0; j < macierz2_data[1]; j++)
		{
			macierz2[i][j] = rand() % max_random_number;
		}

	}

	for (i = 0; i < macierz2_data[0]; i++)
	{
		*(macierzkoncowa + i) = malloc(sizeof(int) * macierz1_data[1]);

		for (j = 0; j < macierz1_data[1]; j++)
		{
			macierzkoncowa[i][j] = rand() % max_random_number;
		}

	}

#ifdef debug

	printf("{");

	for (i = 0; i < macierz1_data[1]; i++)
	{

		printf("{");

		for (j = 0; j < macierz1_data[0]; j++)
		{
			printf("%d", macierz1[j][i]);

			if (j != macierz1_data[0] - 1)
			{
				printf(",");
			}

		}

		printf("}");

		if (i != macierz1_data[1] - 1)
		{
			printf(",");
		}

	}

	printf("}");
	printf("*");
	printf("\n");
	printf("{");

	for (i = 0; i < macierz2_data[1]; i++)
	{

		printf("{");


		for (j = 0; j < macierz2_data[0]; j++)
		{
			printf("%d", macierz2[j][i]);

			if (j != macierz2_data[0] - 1)
			{
				printf(",");
			}

		}

		printf("}");

		if (i != macierz2_data[1] - 1)
		{
			printf(",");
		}

	}
	printf("}");
	printf("\n");


#endif


	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init failed\n");
		return 1;
	}

	pthread_t tid[watki];


	int err;

	for (i = 0; i < watki; i++)
	{
		err = pthread_create(&(tid[i]), NULL, (void *(*)(void *)) liczenieMacierzy, NULL);

		if (err != 0)
		{
			printf("\ncan't create thread :[%s]", strerror(err));
		}

	}

	go = true;

	for (i = 0; i < watki; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&lock);


#ifdef debug

	printf("{");

	for (i = 0; i < macierz1_data[1]; i++)
	{

		printf("{");

		for (j = 0; j < macierz2_data[0]; j++)
		{

			printf("%d", macierzkoncowa[j][i]);

			if (j != macierz2_data[0] - 1)
			{
				printf(",");
			}

		}


		printf("}");


		if (i != macierz1_data[1] - 1)
		{
			printf(",");
		}


	}

	printf("}");
	printf("\n");

#endif


	for (i = 0; i < macierz1_data[1]; i++)
	{
		free(macierz1[i]);
	}

	free(macierz1);

	for (i = 0; i < macierz2_data[1]; i++)
	{
		free(macierz2[i]);
	}

	free(macierz2);


	for (i = 0; i < macierz1_data[1]; i++)
	{
		free(macierzkoncowa[i]);
	}

	free(macierzkoncowa);


	return 0;
}

void *liczenieMacierzy()
{
	while (!go);

	int sem_val, i, a;

	while (true)
	{

		pthread_mutex_lock(&lock);
		sem_getvalue(&semaforek, &sem_val);
		sem_post(&semaforek);
		pthread_mutex_unlock(&lock);

		if (sem_val > macierz1_data[1])
		{
			break;
		}

		for (i = 0; i < macierz2_data[0]; i++)
		{
			macierzkoncowa[i][sem_val] = 0;

			for (a = 0; a < macierz1_data[0]; a++)
			{
				macierzkoncowa[i][sem_val] += macierz1[a][sem_val] * macierz2[i][a];
			}
		}


	}

	return NULL;

}




