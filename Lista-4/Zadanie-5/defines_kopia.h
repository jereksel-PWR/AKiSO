#define NOT_READY	-1
#define FILLED 		0
#define TAKEN		1

struct memory
{
	int status;
	char data[1024];
};

