//
// Created by Yotam Levit on 18/01/2024.
//

#ifndef REGEX_ENGINE_MATCH_H
#define REGEX_ENGINE_MATCH_H


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
#define SPLIT 257
#define MATCH 256

int ismatch(List *l);

void addstate(List *l, NfaPtr s);

List* startlist(NfaPtr s, List *l);

void step(List *currentList, int c, List *nextList);


int match(NfaPtr start, char *s);

#endif //REGEX_ENGINE_MATCH_H
