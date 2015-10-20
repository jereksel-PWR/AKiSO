#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char buffer[256];

	if (argc > 1) {
		strcpy(buffer, argv[1]);
	}

	printf("%p\n", buffer);

	return 0;
}