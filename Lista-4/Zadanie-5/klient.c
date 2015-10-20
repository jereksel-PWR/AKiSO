#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "defines.h"
#include <sys/timeb.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

struct memory *shmptr;

unsigned int last_miliseconds = 0;
unsigned long int last_seconds = 0;
char *nick;

void *wypisywanieNowychWiadomosci()
{
	while (true)
	{
		if (!(shmptr->time_miliseconds == last_miliseconds && shmptr->time_seconds == last_seconds))
		{
			printf("%s: %s\n", shmptr->nick, shmptr->data);
			last_miliseconds = shmptr->time_miliseconds;
			last_seconds = shmptr->time_seconds;
		}

		sleep(1);
	}


	return NULL;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s <nick>\n", argv[0]);
		exit(1);
	}

	nick = argv[1];

	struct timeb tmb;

	char str[MESSAGE_SIZE];

	int shmid;

	shmid = shmget(MEMORY_LOCATION, sizeof(struct memory), 0666);

	if (shmid < 0)
	{
		printf("*** shmget błąd (klient) ***\n");
		exit(1);
	}

	shmptr = (struct memory *) shmat(shmid, NULL, 0);

	if (shmptr == (void *) -1)
	{
		printf("*** shmat błąd (klient) ***\n");
		exit(1);
	}

	pthread_t tcb;

	if (pthread_create(&tcb, NULL, (void *(*)(void *)) wypisywanieNowychWiadomosci, NULL) != 0)
	{
		perror("thread create");
		exit(1);
	}

	while (!(shmptr->is_ready));

	printf("Klient: podłączył się do pamięci współdzielonej\n");

	while (true)
	{
		scanf(" %99[^\n]", str);

		ftime(&tmb);

		last_miliseconds = shmptr->time_miliseconds = tmb.millitm;
		last_seconds = shmptr->time_seconds = (unsigned long) tmb.time;
		strncpy(shmptr->data, str, MESSAGE_SIZE);
		strncpy(shmptr->nick, nick, 60);
	}
}

