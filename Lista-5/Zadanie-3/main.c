#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.h"

int **argumentArray(int iloscZmiennych);

void createArgumentArray(int **tablica, int *malaTablica, int id);

void replaceChars(char *array, char *variables, int *numbers, int numbersNumber);

int calculate(char *array);

int max;

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Składnia: <funkcja boolowska>\n");
		exit(1);
	}


	char *rownanie = argv[1];

	char *czesciRownania[2];

	char *s2 = strtok(rownanie, ":");

	int p = -1;

	//Dzielimy, aby otrzymać listę argumentów
	while (s2 != NULL)
	{
		p++;
		czesciRownania[p] = s2;
		s2 = strtok(NULL, ":");
	}

	//Tymczasowa tablica na argumenty
	char *tablicaZmiennych[100];

	char *zmienne = strtok(czesciRownania[0], ",");

	p = -1;

	while (zmienne != NULL)
	{
		p++;
		tablicaZmiennych[p] = zmienne;
		zmienne = strtok(NULL, ",");
	}

	//Tablica na argumenty
	zmienne = malloc(p * sizeof(char));

	for (int i = 0; i <= p; i++)
	{
		zmienne[i] = tablicaZmiennych[i][0];
	}

	p++;

	int **abc;

	abc = argumentArray(p);

	for (int temp = 0; temp < p; temp++)
	{
		printf("%c ", zmienne[temp]);
	}

	printf("%c\n", 'F');

	for (int a = 0; a < (int) pow((double) 2, p); a++)
	{

		char *backup = malloc(1000 * sizeof(char));
		strcpy(backup, czesciRownania[1]);

		replaceChars(backup, zmienne, abc[a], p);


		for (int temp = 0; temp < p; temp++)
		{
			printf("%d ", abc[a][temp]);
		}

		printf("%d\n", calculate(backup));

		free(backup);

	}

	return 0;
}


int **argumentArray(int iloscZmiennych)
{
	int **tablica;
	tablica = malloc(((int) pow((double) 2, iloscZmiennych)) * sizeof(int *));
	max = iloscZmiennych;
	createArgumentArray(tablica, 0, 0);
	return tablica;
}

int id2 = 0;

//Tworzenie listy z możliwymi kombinacjami argumentów
void createArgumentArray(int **tablica, int *malaTablica, int id)
{

	if (id == max)
	{
		int *temp = malloc((id) * sizeof(int));
		memcpy(temp, malaTablica, id * sizeof(int));

		tablica[id2] = temp;
		id2++;
		return;
	}

	int *temp = malloc((id + 1) * sizeof(int));
	memcpy(temp, malaTablica, id * sizeof(int));
	temp[id] = 0;
	createArgumentArray(tablica, temp, id + 1);
	temp[id] = 1;
	createArgumentArray(tablica, temp, id + 1);

}

//Liczenie wartości funkcji
int calculate(char *array)
{
	int i = 0;
	int temp;
	Stack *stack = malloc(sizeof(Stack));
	stack->next = NULL;
	stack->data = 0;

	while (array[i])
	{
		switch (array[i])
		{
			case ' ':
				break;

			case 'm':
				push(stack, 0);
				break;

			case 'p':
				push(stack, 1);
				break;

			case (char) 39: //Negacja
				temp = pop(stack);
				if (temp == 0)
				{
					push(stack, 1);
				}
				else
				{
					push(stack, 0);
				}
				break;

			case '+':
				temp = pop(stack) + pop(stack);
				if (temp > 1)
				{
					temp = 1;
				}
				push(stack, temp);
				break;

			case '*':
				temp = pop(stack) * pop(stack);
				push(stack, temp);
				break;

			default:
				printf("ERROR");
				exit(0);

		}


		i++;
	}


	return pop(stack);
}

//Zamiana argumentów na zera (m) i jedynki (p)
void replaceChars(char *array, char *variables, int *numbers, int numbersNumber)
{

	for (int i = 0; i < numbersNumber; i++)
	{
		int j = 0;
		char variable = variables[i];

		while (array[j])
		{

			if (array[j] == variable)
			{
				if (numbers[i] == 0)
				{
					array[j] = 'm';
				}
				else
				{
					array[j] = 'p';
				}
			}
			j++;
		}
	}
}