#pragma once
#ifndef _NFANODE
#define _NFANODE

#include <stdio.h>
#include <stdlib.h>

#ifndef _BOOLEAN
#define _BOOLEAN
typedef enum { FALSE, TRUE }BOOLEAN;
#endif

#define MAX_CHARS 100
#define MAX_SYMBOLS 26//# all abc


//--------------  TYPES  ----------

typedef struct NfaNode_Type
{
    char ch;
    struct NfaNode_Type* next[MAX_SYMBOLS];
    int egde_count;
    BOOLEAN is_end_node;
}  NfaNode, * NfaNodePtr;

//--------------  Functions Prototyp (API)  ----------
void nfaInit(NfaNodePtr nfa);
void nfaBuild(NfaNodePtr* nfa,char ch, BOOLEAN is_end_node);
void setNext(NfaNodePtr nfa, char ch, BOOLEAN isis_end_nodeEndNode);
void setNfaEnd(NfaNodePtr nfa, BOOLEAN is_end_node);

NfaNodePtr nfaNext(NfaNodePtr nfa);
void nfaDelete(NfaNodePtr* nfa);
char nfaGetChar(NfaNode nfa);
void nfaModifyChar(NfaNodePtr* nfa, char ch);
int nfaEmpty(NfaNodePtr nfa);
#endif