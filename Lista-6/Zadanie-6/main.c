#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{

	char *opcodeArray[] = {"INS", "LOAD", "STORE", "ADD", "SUBT", "INPUT", "OUTPUT", "HALT", "SKIPCOND", "JUMP", "CLEAR", "ADDI", "JUMPI"};
	FILE *program;
	short int ac = 0;
	unsigned short int pc;
	unsigned short int pcEnd;
	int first;
	int second;
	bool debug = false;

	if (argc < 2)
	{
		printf("usage: %s (-v) <nazwa pliku z programem>\n", argv[0]);
		exit(1);
	}

	if (strcmp(argv[1], "-v") == 0)
	{
		debug = true;
	}

	char *fileName = argv[argc - 1];

	unsigned short int array[16 * 16 * 16];


	for (int i = 0; i < 16 * 16 * 16; i++)
	{
		array[i] = 0;
	}


	//Wrzucamy zawartość programu do tablicy

	program = fopen(fileName, "rb");
	if (program == NULL)
	{
		printf("Plik nie istnieje\n");
		exit(EXIT_FAILURE);
	}

	if (fgetc(program) != 255 || fgetc(program) != 255)
	{
		printf("Błędny plik\n");
		exit(EXIT_FAILURE);
	}

	//pc = (unsigned short) (fgetc(program) + 16*16*fgetc(program));

	pc = (unsigned short) (fgetc(program) | fgetc(program) << 8);
	pcEnd = (unsigned short) (fgetc(program) | fgetc(program) << 8);


	unsigned short pcBackup = pc;

	do
	{
		first = fgetc(program);
		second = fgetc(program);

		array[pcBackup] = (unsigned short) (second << 8 | first);

		pcBackup++;

		if (feof(program))
		{
			break;
		}

	} while (1);


	//Execute stuff

	unsigned short int command;
	unsigned short int opcode;
	unsigned short int address;

	while (1)
	{

		command = array[pc];

		address = command;
		address = (unsigned short) (address & 0xFFF);

		opcode = (unsigned short) (command >> (4 + 4 + 4) & 0xF);

		if (debug)
		{
			printf("\nPC:%-7xAC:%-8x %-8s %-12x  %-4x", pc, ac, opcodeArray[opcode], address, command);
		}

		pc++;

		int number;
		char new_ac;

		switch (opcode)
		{

			case 0:
				array[address] = pc;
				pc = (unsigned short) (address + 1);
				break;

			case 1:

				ac = address;
				break;

			case 2:

				array[address] = (unsigned short) ac;
				break;

			case 3:

				ac += address;
				break;

			case 4:
				ac -= address;
				break;

			case 5:
				scanf("%c", &new_ac);
				ac = new_ac;
				break;

			case 6:
				if (debug)
				{
					printf("\n");
				}
				printf("%c", (char) ac);
				//printf("%d", ac);
				break;

			case 7:

				exit(0);
				break;

			case 8:
				number = address;
				number = (number >> 10);
				number &= 0x3;
				//printf("\nNUMBER : %d\n\n", number);


				if (number == 0 && ac < 0)
				{
					pc++;
					break;
				}
				if (number == 1 && ac == 0)
				{
					pc++;
					break;
				}
				if (number == 2 && ac > 0)
				{
					pc++;
					break;
				}

				break;

			case 9:
				pc = address;
				break;

			case 10:
				ac = 0;
				break;

			case 11:
				ac += array[address];
				break;

			case 12:
				pc = array[address];
				break;

			default:
				printf("\nNIEZNANY OPCODE: %d\n", opcode);
				break;
		}

	}


	return 0;
}
