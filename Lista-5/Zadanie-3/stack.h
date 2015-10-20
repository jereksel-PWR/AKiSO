typedef struct Stack Stack;

struct Stack
{
	int data;
	Stack* next;
};

void push(Stack *S, int val);
int pop(Stack *S);
