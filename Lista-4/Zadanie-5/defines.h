#define MEMORY_LOCATION        666
#define MESSAGE_SIZE            1024

#include <stdbool.h>

struct memory
{
	bool is_ready;
	unsigned long int time_seconds;
	unsigned int time_miliseconds;
	char nick[60];
	char data[MESSAGE_SIZE];
};

