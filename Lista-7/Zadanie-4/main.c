#include <stdio.h>

float atof(char*);
char* ftoa(float);

int main()
{

	printf("%f\n", atof("15.54"));
	printf("%s\n", ftoa(1.12234));

	return 0;

}