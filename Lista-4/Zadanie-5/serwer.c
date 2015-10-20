#define _POSIX_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "defines.h"

int shmid;
struct memory *shmptr;

void sig_handler(int signo)
{
	printf("Usuwanie pamięci współdzielonej\n");
	shmdt((void *) shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}

int main(int argc, char *argv[])
{
	shmid = shmget(MEMORY_LOCATION, sizeof(struct memory), IPC_CREAT | 0666);

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

	signal(SIGINT, sig_handler);

	shmptr->is_ready = false;
	shmptr->time_miliseconds = 0;
	shmptr->time_seconds = 0;
	strncpy(shmptr->data, "", MESSAGE_SIZE);
	shmptr->is_ready = true;

	printf("Klienci już mogą się podłączać\n");

	while (true)
	{
		sleep(100000);
	}

	exit(0);
}