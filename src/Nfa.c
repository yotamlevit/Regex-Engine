#include "Nfa.h"
#include <stdio.h>
#include <stdlib.h>

/********************** Function prototypes **************/

void nfaInit(NfaNodePtr* nfa);
NfaNodePtr nfaBuild(char ch);
void setNext(NfaNodePtr nfa, char ch);
void setEnd(NfaNodePtr nfa);

NfaNodePtr nfaSub(NfaNodePtr nfa);
void nfaDelete(NfaNodePtr* nfa);
char nfaRetrieve(NfaNode nfa);
void nfaModify(NfaNodePtr* nfa, char ch);
int nfaEmpty(NfaNodePtr nfa);
/*********************** Function bodies **************/
void nfaInit(NfaNodePtr* nfa)
{
	*nfa= NULL;
}

NfaNodePtr nfaBuild(char ch)
{
	NfaNodePtr ptr;
	ptr = (NfaNodePtr)malloc(sizeof(NfaNode));
	ptr->ch = ch;
	ptr->next = NULL;
    ptr->is_end_node = 0;
	return(ptr);
}

void setNext(NfaNodePtr nfa, char ch)
{
	NfaNodePtr ptr;
	if (nfa == NULL)
		printf("\n Error - Null nfa \n");
	else
		if (nfa->next == NULL)
		{
			ptr = nfaBuild(ch);
			nfa->next= ptr;
		}
		else printf("\n Error - there is already next node \n");
}


void setEnd(NfaNodePtr nfa)
{
	nfa->is_end_node = 1;
}

NfaNodePtr nfaSub(NfaNodePtr nfa)
{
	if (nfa->next!= NULL)
	{
		return nfa->next;
	}
	else
	{
		printf("\nNo next node for nfa\n");
		return;
	}
}

void nfaDelete(NfaNodePtr* nfa)
{
	if ((*nfa)->next != NULL)
		nfaDelete(&(*nfa)->next);
	free(nfa);
}

char nfaRetrieve(NfaNode nfa)
{
	return nfa.ch;
}

void nfaModify(NfaNodePtr* nfa, char ch)
{
	(*nfa)->ch = ch;
}

int nfaEmpty(NfaNodePtr nfa)
{
	if (nfa == NULL)
		return 1;
	return 0;
}
