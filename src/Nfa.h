#pragma once
#ifndef _NFANODE
#define _NFANODE
//--------------  TYPES  ----------

typedef struct NfaNode_Type
{
    char ch;
    struct NfaNode_Type* next;
    int is_end_node;
}  NfaNode, * NfaNodePtr;

//--------------  Functions Prototyp (API)  ----------
void nfaInit(NfaNodePtr* nfa);
NfaNodePtr nfaBuild(char ch);
void setNext(NfaNodePtr nfa, char ch);
void setEnd(NfaNodePtr nfa);

NfaNodePtr nfaSub(NfaNodePtr nfa);
void nfaDelete(NfaNodePtr* nfa);
char nfaRetrieve(NfaNode nfa);
void nfaModify(NfaNodePtr* nfa, char ch);
int nfaEmpty(NfaNodePtr nfa);
#endif