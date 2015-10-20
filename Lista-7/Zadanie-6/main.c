#include <stdio.h>

float function1(float); //ln(x)
float function2(float); //e^x
float function3(float); //sinh(x)
float function4(float); //sinh^-1(x)

int main()
{

	printf("%f\n", function1(2.54));
	printf("%f\n", function2(2.54));
	printf("%f\n", function3(2.54));
	printf("%f\n", function4(2.54));

	return 0;

}