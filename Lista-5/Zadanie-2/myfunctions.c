#include "myfunctions.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

//Przechowujemy tutaj wielkośc tablicy (przy inpucie < 6 pojawiają się dziwne znaki w tablicy, które niszczą konwersję na liczby).
int arraySizeValue = 0;

int *charArrayToIntArray(char *array);

int *cleanIntArray(int *array, int base);

int intArrayToInt(int *array, int base);

char *hexFix(char *array);

int arraySize(char *array);

void decToBase(int number, int base);

int myscanf(const char *format, ...)
{

	char test[1024];
	char *source;
	int i, n = 0;
	int *number;
	va_list vl;

	if (read(0, test, 1024) < 0)
	{
		write(2, "An error occurred in the read.\n", 31);
	}


	va_start(vl, n);

	switch (format[1])
	{

		case 's':
			//String
			source = va_arg(vl, char*);

			//Działa tylko dla tablic zadeklarowanych mallokiem

			memcpy(source, test, sizeof(source));

			break;


		case 'd':
			//Base 10

			number = va_arg(vl, int*);

			int integer = intArrayToInt(cleanIntArray(charArrayToIntArray(test), 10), 10);

			memcpy(number, &integer, sizeof(int));

			break;


		case 'b':
			//Base 2

			number = va_arg(vl, int*);

			int binary = intArrayToInt(cleanIntArray(charArrayToIntArray(test), 2), 2);

			memcpy(number, &binary, sizeof(int));

			break;

		case 'x':
			//Base 16

			arraySizeValue = arraySize(test);

			number = va_arg(vl, int*);

			int hex = intArrayToInt(cleanIntArray(charArrayToIntArray(hexFix(test)), 16), 16);

			memcpy(number, &hex, sizeof(int));

			break;

		default:
			break;

	}
	va_end(vl);
	return 0;
}

int myprintf(const char *format, ...)
{

	int i = 0;
	int n = 0;
	va_list vl;
	char *source;
	int number;

	char test[1];

	va_start(vl, n);

	while (format[i])
	{
		test[0] = format[i];
		if (test[0] == '%')
		{
			i++;
			test[0] = format[i];

			switch (test[0])
			{

				case 's':
					//String
					source = va_arg(vl, char*);

					write(1, source, arraySize(source));

					break;


				case 'd':
					//Base 10

					number = va_arg(vl, int);

					decToBase(number, 10);

					break;


				case 'b':
					//Base 2

					number = va_arg(vl, int);

					decToBase(number, 2);

					break;

				case 'x':
					//Base 16

					number = va_arg(vl, int);

					decToBase(number, 16);

					break;

				default:
					break;

			}


		}
		else
		{
			write(1, test, 1);
		}
		i++;
	}

	va_end(vl);
	return 0;
}

int arraySize(char *array)
{
	int i = 0;

	while (array[i])
	{
		i++;
	}

	return i;
}

int *charArrayToIntArray(char *array)
{

	int i = 0;

	i = arraySize(array);

	int *intArray = malloc(i * sizeof(int));

	for (int a = 0; a < i; a++)
	{
		intArray[a] = array[a] - 48;
	}

	arraySizeValue = i;

	return intArray;
}

int *cleanIntArray(int *array, int base)
{

	int i = arraySizeValue;

	int *cleanedArray = malloc(i * sizeof(int));

	int a = 0;

	//Kopiujemy tylko liczby od 0 do (base - 1)
	for (int p = 0; p < i; p++)
	{
		if (array[p] >= 0 && array[p] < base)
		{
			cleanedArray[a] = array[p];
			a++;
		}

	}

	arraySizeValue = a;

	cleanedArray = realloc(cleanedArray, a * sizeof(int));

	return cleanedArray;

}

int intArrayToInt(int *array, int base)
{
	int size = arraySizeValue;

	int number = 0;

	for (int i = 0; i < size; i++)
	{
		number += pow(base, i) * array[size - 1 - i];
	}

	return number;

}

char *hexFix(char *array)
{

	int size = arraySizeValue;

	for (int i = 0; i < size; i++)
	{


		if (array[i] >= 97 && array[i] <= 102)
		{
			array[i] = (char) (array[i] - (97 - 58));

		}


		if (array[i] >= 65 && array[i] <= 70)
		{
			array[i] = (char) (array[i] - (65 - 58));

		}

	}


	return array;

}

void decToBase(int number, int base)
{

	int temp;

	int i = 0;

	int array[100];

	int arrayTemp[1];

	while (number)
	{
		array[i] = (number % base) + 48;
		i++;
		number = number / base;
	}

	array[i] = 0;

	for (temp = i; temp >= 0; temp--)
	{

		arrayTemp[0] = array[temp];

		if (arrayTemp[0] > 58)
		{
			arrayTemp[0] += (65 - 58);
		}

		write(1, arrayTemp, 1);

	}

}