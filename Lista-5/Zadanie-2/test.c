#include "myfunctions.h"

int main(int argc, char *argv[])
{

	int test=0;

	myprintf("**** Program testujący do funkcji myprinf i myscanf **** \nProszę wpisać liczbę całkowitą\n");

	myscanf("%d", &test);

	myprintf("Wpisałeś liczbę \n%d (base 10)\n%b (base 2)\n%x (base 16)\n", test, test, test);

	myprintf("Proszę wpisać liczbę binarną\n");

	myscanf("%b", &test);

	myprintf("Wpisałeś liczbę \n%d (base 10)\n%b (base 2)\n%x (base 16)\n", test, test, test);

	myprintf("Proszę wpisać liczbę szestnastkową\n");

	myscanf("%x", &test);

	myprintf("Wpisałeś liczbę \n%d (base 10)\n%b (base 2)\n%x (base 16)\n", test, test, test);

	return 0;
}