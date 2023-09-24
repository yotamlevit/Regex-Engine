//
// Created by Yotam Levit on 22/09/2023.
//
// C code to convert infix to postfix expression

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "src/data_structures/stack/stack_char.h"

#define END_OF_STR '\0'

// Function to return precedence of operators
int precedence(char operator)
{
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}


BOOLEAN isRegexValidChar(char c)
{
    if (isalpha(c) || isdigit(c))
        return TRUE;
    return FALSE;
}


char* infixToPostfix(char * infix)
{
    int len = strlen(infix);
    char* poststr = (char*)malloc(sizeof(char) * (len + 2));
    char* ppost;
    char* pstr;
    char c;
    stack_char stk;


    initStackChar(&stk);

    ppost = poststr;
    pstr = infix;
    while (*pstr)
    {
        if (isRegexValidChar(*pstr))
        {
            *ppost++ = *pstr;
        }
        else if (*pstr == '(')
        {
            pushStackChar(&stk, *pstr);
        }
        else if (*pstr == ')')
        {
            while (peekStackChar(&stk) != '(' && !isEmptyStackChar(&stk))
            {
                c = popStackChar(&stk);
                *ppost = c;
                ppost++;
            }
            if (peekStackChar(&stk) == '(')
            {
                char c = popStackChar(&stk);
            }
        }
            //If an operator is scanned
        else {
            while (!isEmptyStackChar(&stk) && precedence(*pstr) <= precedence(peekStackChar(&stk)))
            {
                c = popStackChar(&stk);
                *ppost = c;
                ppost++;
            }
            pushStackChar(&stk, *pstr);
        }
        pstr++;
    }
    //Pop all the remaining elements from the stack
    while (!isEmptyStackChar(&stk))
    {
        c = popStackChar(&stk);
        *ppost = c;
        ppost++;
    }
    *ppost = END_OF_STR;
    printf("\nThe post infix is: %s\n", poststr);
    return poststr;
}
