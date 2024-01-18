//
// Created by Yotam Levit on 18/01/2024.
//

#include "Include/nfa.h"
#include <stdlib.h>

typedef struct List
{
    NfaPtr *s;
    int n;
}List;

List list1, list2;
int listId;
NFA matchstate = { 257 };
#define SPLIT 257
#define MATCH 256

int ismatch(List *l)
{
    int i;

    for(i=0; i<l->n; i++)
        if(l->s[i]->c == MATCH) // Match
            return 1;
    return 0;
}

void addstate(List *l, NfaPtr s)
{
    if(s == NULL || s->lastlist == listId)
        return;
    s->lastlist = listId;
    if(s->c == SPLIT){ // Split
        /* follow unlabeled arrows */
        addstate(l, s->out);
        addstate(l, s->out1);
        return;
    }
    l->s[l->n++] = s;
}

List* startlist(NfaPtr s, List *l)
{
    listId++;
    l->n = 0;
    addstate(l, s);
    return l;
}

void step(List *currentList, int c, List *nextList)
{
    int i;
    NfaPtr s;

    listId++;
    nextList->n = 0;
    for(i=0; i<currentList->n; i++){
        s = currentList->s[i];
        if(s->c == c)
            addstate(nextList, s->out);
    }
}


int match(NfaPtr start, char *s)
{
    List *currentList, *nextList, *t;

    /* l1 and l2 are preallocated globals */
    currentList = startlist(start, &list1);
    nextList = &list2;
    for(; *s; s++){
        step(currentList, *s, nextList);
        t = currentList; currentList = nextList; nextList = t;	/* swap currentList, nextList */
    }
    return ismatch(currentList);
}