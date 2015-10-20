#define _POSIX_SOURCE

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void catch(int dummy)
{
	printf("Złapano:%d\n", dummy);
}


int main(void)
{

	int i;

	for (i = 1; i <= 62; i++)
	{
		signal(i, catch);
	}


	int mojpid = getpid();


	for (i = 1; i <= 62; i++)
	{
		printf("Wysyłanie sygnału: %d\n", i);

		kill(mojpid, i);

		sleep(1);

	}

	return 0;

}
