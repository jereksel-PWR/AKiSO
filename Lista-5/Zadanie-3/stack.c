#include <stdlib.h>
#include "stack.h"

void push(Stack *s, int val)
{

	Stack *stack = malloc(sizeof(Stack));
	stack->data = s->data;
	stack->next = s->next;

	s->data = val;
	s->next = stack;

}

int pop(Stack *s)
{

	int number = s->data;

	if (s->next == NULL)
	{
		free(s);
		return number;
	}

	Stack* tempStack = s->next;

	s->data = s->next->data;
	s->next = s->next->next;

	free(tempStack);

	return number;

}