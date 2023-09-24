//
// Created by Yotam Levit on 23/09/2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nfa.h"

// Function implementation
NfaPtr initNFA()
{
    // Take memory for the new node
    NfaPtr newState = (NfaPtr)malloc(sizeof(NFA));

    // Set the artibutes of the node
    newState->c = NULL;
    newState->out = NULL;
    newState->out1 = NULL;
    newState->lastlist = NULL;

    // Return the new node
    return newState;
}

NfaPtr initNFAData(char c)
{
    // Take memory for the new node
    NfaPtr newState = (NfaPtr)malloc(sizeof(NFA));

    // Set the artibutes of the node
    newState->c = c;
    newState->out = NULL;
    newState->out1 = NULL;
    newState->lastlist = NULL;

    // Return the new node
    return newState;
}

void setNext(NfaPtr pNfa, char c)
{
    if(pNfa == NULL)
        printf("\n Error - Null NFA\n");
    else
    {
        if(pNfa->out == NULL)
            pNfa->out = initNFAData(c);
        else if(pNfa->out1 == NULL)
            pNfa->out1 = initNFAData(c);
        else
            printf("\nThere are already 2 states connnected to this state\n");

    }
}

BOOLEAN isEndState(NfaPtr pNFA)
{
    return pNFA->c == 3;
}

