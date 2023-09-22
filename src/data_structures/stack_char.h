#pragma once
#ifndef _STACK_CHAR
#define _STACK_CHAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _BOOLEAN
#define _BOOLEAN
typedef enum { FALSE, TRUE } BOOLEAN;
#endif

#ifndef N
#define N 50
#endif

typedef struct
{
	char ar[N];
	int top;
} stack_char, * stack_char_Ptr;
void initStackChar(stack_char_Ptr);
char peekStackChar(stack_char_Ptr);
BOOLEAN isEmptyStackChar(stack_char_Ptr);
BOOLEAN isFullStackChar(stack_char_Ptr);
char popStackChar(stack_char_Ptr);
void pushStackChar(stack_char_Ptr, char);

#endif