#include "Nfa1111.h"


#define IS_MAX_EGDES(nfa) (*nfa)->egde_count < MAX_SYMBOLS-1 // TODO change name

/********************** Function prototypes **************/

void nfaInit(NfaNodePtr nfa);
void nfaBuild(NfaNodePtr* nfa, char ch, BOOLEAN is_end_node);
void setNext(NfaNodePtr nfa, char ch, BOOLEAN is_end_node);
void setNfaEnd(NfaNodePtr nfa, BOOLEAN is_end_node);

NfaNodePtr nfaNext(NfaNodePtr nfa);
void nfaDelete(NfaNodePtr* nfa);
char nfaGetChar(NfaNode nfa);
void nfaModifyChar(NfaNodePtr* nfa, char ch);
int nfaEmpty(NfaNodePtr nfa);
/*********************** Function bodies **************/
void nfaInit(NfaNodePtr* nfa)
{
	*nfa = NULL;
}

void nfaBuild(NfaNodePtr* nfa, char ch, BOOLEAN is_end_node)
{
	*nfa = (NfaNodePtr)malloc(sizeof(NfaNode));
	(*nfa)->ch = ch;
	(*nfa)->egde_count = 0;
	(*nfa)->is_end_node = is_end_node;

	for (int i = 0; i < MAX_SYMBOLS; i++)
		(*nfa)->next[i] = NULL;
}


BOOLEAN has_free_edge(NfaNodePtr nfa)
{
	return nfa->egde_count < MAX_SYMBOLS - 1;
}

void setNext(NfaNodePtr* nfa, char ch, BOOLEAN is_end_node)
{
	NfaNodePtr ptr;
	nfaInit(&ptr);
	if (*nfa == NULL)
		printf("\n Error - Null nfa \n");
	else
		if (IS_MAX_EGDES(nfa) && (*nfa)->next[(*nfa)->egde_count] == NULL)
		{
			nfaBuild(&ptr, ch, is_end_node);
			(*nfa)->next[(*nfa)->egde_count++] = ptr;

		}
		else printf("\n Error - maximum edges reached \n");
}


void setNfaEnd(NfaNodePtr nfa, BOOLEAN is_end_node)
{
	nfa->is_end_node = is_end_node;
}

NfaNodePtr nfaNext(NfaNodePtr nfa)
{
	if (nfa->next != NULL)
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
	free(*nfa);
}

char nfaGetChar(NfaNode nfa)
{
	return nfa.ch;
}

void nfaModifyChar(NfaNodePtr* nfa, char ch)
{
	(*nfa)->ch = ch;
}

int nfaEmpty(NfaNodePtr nfa)
{
	if (nfa == NULL)
		return 1;
	return 0;
}
