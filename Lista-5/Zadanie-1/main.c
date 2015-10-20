#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int arraySize(char *array);

int *charArrayToIntArray(char *array);

int main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("Składnia: <liczba> <liczba cyfr po przecinku>\n");
		exit(1);
	}

	char *czesciRownania[2];

	char *s2 = strtok(argv[1], ".");

	int p = -1;

	//Dzielimy, aby otrzymać liczby po przecinku
	while (s2 != NULL)
	{
		p++;
		czesciRownania[p] = s2;
		s2 = strtok(NULL, ".");
	}

	printf("0.");

	int a, i, temp;

	int *numbers;

	numbers = charArrayToIntArray(czesciRownania[1]);

	for (i = 0; i < atoi(argv[2]); i++)
	{

		temp = 0;

		for (a = sizeof(numbers)/sizeof(int); a >= 0; a--)
		{
			numbers[a] = 2 * numbers[a] + temp;
			temp = numbers[a] / 10;
			numbers[a] = numbers[a] % 10;
		}


		printf("%d", temp);


	}


	return 0;

}

//Konwersja tablicy charów na tablicę intów
int *charArrayToIntArray(char *array)
{

	int *intArray = malloc(arraySize(array) * sizeof(int));

	int temp = 0;

	for (int i = 0; i <= arraySize(array) - 1; i++)
	{
		intArray[i] = array[i] - 48;
		temp++;
	}

	return intArray;
}

//Rozmiar tablicy charów
int arraySize(char *array)
{
	int i = 0;

	while (array[i])
	{
		i++;
	}

	return i;
}