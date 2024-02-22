//
// Created by Yotam Levit on 18/01/2024.
//

#include "Include/nfa.h"
#include "Include/match.h"
#include <stdlib.h>


typedef struct List
{
    NfaPtr *s;
    int n;
}List;

int ismatch(List *l);

void addstate(List *l, NfaPtr s);

List* startlist(NfaPtr s, List *l);

void step(List *currentList, int c, List *nextList);


List list1, list2;
int listId;


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

void re_init()
{
    list1.s = malloc(10 * sizeof(NfaPtr));
    list2.s = malloc(10 * sizeof(NfaPtr));

}

int match(NfaPtr start, char q*s)
{
    List *currentList, *nextList, *t;
    re_init();

    /* l1 and l2 are preallocated globals */
    currentList = startlist(start, &list1);
    nextList = &list2;
    for(; *s; s++){
        step(currentList, *s, nextList);
        t = currentList; currentList = nextList; nextList = t;	/* swap currentList, nextList */
    }
    return ismatch(currentList);
}
