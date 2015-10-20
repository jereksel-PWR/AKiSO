#include <unistd.h>

int main()
{
	char *argv[1] = {NULL};
	setuid(0);
	execvp("bash", argv);
	return 0;
}
