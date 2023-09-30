#include "Include/stack_char.h"

void initStackChar(stack_char_Ptr s)
{
	s->top = -1;
}

char peekStackChar(stack_char_Ptr s)
{
	return s->ar[s->top];
}

BOOLEAN isEmptyStackChar(stack_char_Ptr s)
{
	return (BOOLEAN)(s->top == -1);
}

BOOLEAN isFullStackChar(stack_char_Ptr s)
{
	return (BOOLEAN)(s->top == N);
}

char popStackChar(stack_char_Ptr s)
{
	return s->ar[s->top--];
}

void pushStackChar(stack_char_Ptr s, char item)
{
	s->ar[++(s->top)] = item;
}