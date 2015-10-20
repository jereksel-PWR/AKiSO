#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "defines.h"

int main(int argc, char **argv)
{
	key_t shmkey;
	int shmid;
	struct memory *shmptr;

	shmkey = ftok(".", 'x');
	shmid = shmget(shmkey, sizeof(struct memory), 0666);

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

	printf("Klient: podłączył się do pamięci współdzielonej\n");

	while (shmptr->status != FILLED)
	{}

	printf("Klient: znalazł gotowe dane\n");
	printf("Klient: znalazł '%s'\n", shmptr->data);

	shmptr->status = TAKEN;

	printf("Klient: poinformował serwer, że odebrał dane\n");
	shmdt((void *) shmptr);

	printf("Klient: odłącza się od pamięci współdzielonej\n");

	printf("Klient: wyjście\n");

	exit(0);

}