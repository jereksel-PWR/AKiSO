#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "defines.h"

int main(int argc, char *argv[])
{
	key_t shmkey;
	int shmid;
	struct memory *shmptr;

	if (argc != 2)
	{

		printf("%s: $l\n", argv[0]);
		exit(1);

	}

	shmkey = ftok(".", 'x');
	shmid = shmget(shmkey, sizeof(struct memory), IPC_CREAT | 0666);

	if (shmid < 0)
	{
		printf("*** shmget błąd (serwer) ***\n");
		exit(1);
	}

	shmptr = (struct memory *) shmat(shmid, NULL, 0);
	if (shmptr == (void *) -1)
	{
		printf("*** shmat błąd (serwer) ***\n");
		exit(1);
	}

	shmptr->status = NOT_READY;
	strcpy(shmptr->data, argv[1]);

	printf("Pamięć współdzielona wypełniona ciągiem znaków '%s'\n", shmptr->data);
	shmptr->status = FILLED;

	printf("Proszę uruchom klienta w drugim oknie\n");

	while (shmptr->status != TAKEN) sleep(1);

	printf("Serwer: ciąg znaków został pobrany\n");
	shmdt((void *) shmptr);

	printf("Serwer: odłącza (detached) pamięć współdzieloną\n");
	shmctl(shmid, IPC_RMID, NULL);

	printf("Serwer: usuwa (removed) pamięć współdzieloną\n");

	printf("Serwer: wyjście\n");

	exit(0);
}