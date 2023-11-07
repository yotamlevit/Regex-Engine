//
// Created by Yotam Levit on 23/09/2023.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Include/nfa.h"

// Function implementation
NfaPtr initNFA()
{
    // Take memory for the new node
    NfaPtr newState = (NfaPtr)malloc(sizeof(NFA));

    // Set the artibutes of the node
    newState->c = -1;
    newState->out = NULL;
    newState->out1 = NULL;
    newState->lastlist = -1;

    // Return the new node
    return newState;
}

NfaPtr initNFAData(char c, NfaPtr out, NfaPtr out1, int lastlist)
{
    // Take memory for the new node
    NfaPtr newState = (NfaPtr)malloc(sizeof(NFA));

    // Set the artibutes of the node
    newState->c = c;
    newState->out = out;
    newState->out1 = out1;
    newState->lastlist = lastlist;

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
            pNfa->out = initNFAData(c, NULL, NULL,0);
        else if(pNfa->out1 == NULL)
            pNfa->out1 = initNFAData(c, NULL, NULL,0);
        else
            printf("\nThere are already 2 states connnected to this state\n");

    }
}

BOOLEAN isEndState(NfaPtr pNFA)
{
    return pNFA->c == 257;
}

