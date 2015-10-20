#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

int lastCharacterLocation(char array[]);

void clearArray(char array[]);

void obslugaRury(char str[]);

void executePipe(char ***cmd);

int MAX = 100;
bool ampersand = false;

int main()
{
	char str[MAX];
	char *s;
	char *test[MAX];
	bool rura_bool;
	int charLocation;
	char location[1024];
	char c;
	int line_length;
	getcwd(location, 1024);

	while (1)
	{

		rura_bool = false;
		clearArray(str);
		//	clearPipe(rura);

		line_length = 0;
		printf("%s > ", location);

		while ((c = getchar()) != EOF && c != '\n' && line_length < MAX - 1)
		{
			if (c == '|')
			{
				rura_bool = true;
			}

			str[line_length] = c;
			line_length++;
		}

		if (line_length == 0)
		{
			if (c == EOF)
			{
				exit(0);
			}

			continue;
		}

		charLocation = lastCharacterLocation(str);

		if (str[charLocation] == '&')
		{
			ampersand = true;
			str[charLocation] = ' ';
		}

		if (rura_bool)
		{
			obslugaRury(str);
			continue;
		}


		s = strtok(str, " ");

		int i = -1;

		while (s != NULL)
		{
			i++;
			test[i] = s;
			s = strtok(NULL, " ");
		}

		i++;
		test[i] = NULL;

		if (strcmp(test[0], "exit") == 0)
		{
			exit(0);
		}

		int status;

		if (fork() == 0)
		{
			if (execvp(test[0], test) == -1)
			{
				printf("%s\n", strerror(errno));
			}
			exit(0);
		}
		else
		{
			if (!ampersand)
			{
				wait(&status);
			}
		}

		ampersand = false;

	}

	return 0;

}

void obslugaRury(char str[])
{

	char **rura[MAX];
	char *temp[MAX];

	int i = -1;

	char *s = strtok(str, "|");
	char *s2;

	while (s != NULL)
	{
		i++;
		temp[i] = s;
		s = strtok(NULL, "|");
	}

	for (int a = 0; a <= i; a++)
	{

		char **pipePart;
		pipePart = malloc(sizeof(char *) * MAX);

		s2 = strtok(temp[a], " ");

		int p = -1;

		while (s2 != NULL)
		{
			p++;
			pipePart[p] = s2;
			s2 = strtok(NULL, " ");
		}

		p++;
		pipePart[p] = NULL;
		rura[a] = pipePart;

	}

	rura[i + 1] = NULL;

	executePipe(rura);

	for (int a = 0; a <= i; a++)
	{
		free(rura[a]);
	}

}

int lastCharacterLocation(char array[])
{
	int i = 0;

	while (array[i] != '\0')
	{
		i++;
	}

	return i - 1;
}

void clearArray(char array[])
{
	for (int i = 0; i < MAX; i++)
	{
		array[i] = '\0';
	}
}

void executePipe(char ***cmd)
{
	int p[2];
	pid_t pid;
	int fd_in = 0;
	int status;

	while (*cmd != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
		{
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(fd_in, 0); //Wczytujemy dane z pipe'a (został już użyty, jeśli nie czytamy ze standardowego wejścia)
			if (*(cmd + 1) != NULL)
			{
				dup2(p[1], 1); //Wyjście ustawiamy na pipe
			}
			close(p[0]); //Zamykamy wejście
			execvp((*cmd)[0], *cmd);
			exit(0);
		}
		else
		{
			wait(&status); //Czekamy na skończenie pracy dziecka
			close(p[1]);  //Zamykamy wyjście
			fd_in = p[0]; //Ustawiamy wejście na pipe
			cmd++;
		}
	}
}