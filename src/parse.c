//
// Created by Yotam Levit on 22/09/2023.
//
// C code to convert infix to postfix expression

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Include/stack_char.h"

#define END_OF_STR '\0'
#define NOT_AN_OPERATOR -1


// Function to return precedence of operators
int precedence(char operator)
{
    switch (operator) {
        case '|':
            return 0;
        case '.':
            return 1;
        case '?':
        case '*':
        case '+':
            return 2;
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


char* insertExplicitConcatOperator(char* exp) {
    int len = strlen(exp);
    char* output= (char*)malloc(sizeof(char) * (len + 2) * 2 +1);
    char* pexp;
    char* poutput;
    char c;

    pexp = exp;
    poutput = output;
    while(*pexp)
    {
        *poutput++ = *pexp;

        if (*pexp == '(' || *pexp == '|'){
            pexp++;
            continue;
        }

        if (*(pexp+1) != END_OF_STR)
        {
           c = *(pexp+1);

           if (c == '*' || c == '?' || c == '+' || c == '|' || c == ')'){
               pexp++;
               continue;
           }

           *poutput++ = '.';
        }

        pexp++;
    }
    *poutput = '\0';

    //output = (char*) realloc(output, strlen(output)+1);

    return output;
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
        else if (precedence(*pstr) != NOT_AN_OPERATOR) {
            while (!isEmptyStackChar(&stk) && precedence(*pstr) <= precedence(peekStackChar(&stk)))
            {
                c = popStackChar(&stk);
                *ppost = c;
                ppost++;
            }
            pushStackChar(&stk, *pstr);
        }
        else {
            printf("\n Not a supported character %c \n", *pstr);
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
