#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define max_random_number 100

#define bardzo_szybko

int **macierzkoncowa;

int **macierz1;
int **macierz2;
int **macierztemp;


int main(int argc, char *argv[])
{
	struct timeval przed;
	struct timeval po;

	gettimeofday(&przed, 0);

	int a, i, j;

	if (argc != 2)
	{
		printf("usage: %s <wielkosc macierzy>", argv[0]);
		exit(1);
	}

	srand((unsigned int) time(NULL));

	int wielkosc = atoi(argv[1]);

	macierz1 = malloc(sizeof(int *) * wielkosc);
	macierz2 = malloc(sizeof(int *) * wielkosc);
	macierzkoncowa = malloc(sizeof(int *) * wielkosc);


	for (i = 0; i < wielkosc; i++)
	{
		*(macierz1 + i) = malloc(sizeof(int) * wielkosc);
		*(macierz2 + i) = malloc(sizeof(int) * wielkosc);
		*(macierzkoncowa + i) = malloc(sizeof(int) * wielkosc);

		for (j = 0; j < wielkosc; j++)
		{
			macierz1[i][j] = rand() % max_random_number;
			macierz2[i][j] = rand() % max_random_number;
		}

	}


#if defined bardzo_szybko


#define SM (64 / sizeof (double))

	int N = wielkosc;
	int k;
	int **mul1 = macierz1;
	int **mul2 = macierz2;
	int **res = macierzkoncowa;

	int *rres, *rmul1, i2, k2, *rmul2, j2;

	for (i = 0; i < N; i += SM)
		for (j = 0; j < N; j += SM)
			for (k = 0; k < N; k += SM)
				for (i2 = 0, rres = &res[i][j],
							 rmul1 = &mul1[i][k]; i2 < SM;
					 ++i2, rres += N, rmul1 += N)
					for (k2 = 0, rmul2 = &mul2[k][j];
						 k2 < SM; ++k2, rmul2 += N)
						for (j2 = 0; j2 < SM; ++j2)
							rres[j2] += rmul1[k2] * rmul2[j2];


#elif defined szybko

	macierztemp = malloc(sizeof(int *) * wielkosc);

	for (i = 0; i < wielkosc; i++)
	{
		*(macierztemp + i) = malloc(sizeof(int) * wielkosc);
	}


	for (int i = 0; i < wielkosc; i++)
		for (int j = 0; j < wielkosc; j++)
			macierztemp[i][j] = macierz2[j][i];

	for (int i = 0; i < wielkosc; i++)
		for (int j = 0; j < wielkosc; j++)
			for (int k = 0; k < wielkosc; k++)
				macierzkoncowa[i][j] += macierz1[i][k] * macierztemp[j][k];


#else

	for (int i = 0; i < wielkosc; i++)
		for (int j = 0; j < wielkosc; j++)
			for (int k = 0; k < wielkosc; k++)
				macierzkoncowa[i][j] += macierz1[i][k] * macierz2[k][j];


#endif

	gettimeofday(&po, 0);

	long long int czasDzialania = po.tv_sec - przed.tv_sec;


	printf("Czas w sekundach: %qi", czasDzialania);

	return 0;

}


