//
// Created by Yotam Levit on 24/09/2023.
//

#include "construction.h"

#include "Include/nfa.h"
#include <stdlib.h>

#define PUSH(stackp, s) *stackp++ = s
#define POP()   *--stackp
#define SPLIT 256

NFA matchstate = { 256 };

typedef struct Frag
{
    NfaPtr start;
    NfaPtr* out;
}Frag, * FragPtr;

Frag* initFrag(NfaPtr start, NfaPtr** out){
    // Take memory for the new node
    FragPtr newFrag = (FragPtr)malloc(sizeof(Frag));

    // Set the artibutes of the node
    newFrag->start = start;
    newFrag->out = *out;

    //for (int i = 0; i < sizeof(newFrag->out)/sizeof(NfaPtr);++i) {
    //}

    // Return the new node
    return newFrag;
}

typedef union StateList
{
    union StateList* next;
    NfaPtr curr_state;
} StateList;

//List1 creates a new pointer list containing the single pointer outp.
StateList* list1(NfaPtr* outp)
{
    StateList* stateList =  (StateList*)outp; //(ptr_list*)malloc(sizeof(NfaPtr*));
    //*NfaListPtr = outp;
    stateList->next = NULL;

    return stateList;
}


// Append concatenates two pointer lists, returning the result.
StateList* append(StateList* list1, StateList* list2)
{
    StateList* tmp = list1;
    // traverse till the linked list's end and set the end item's next to the second_list's start
    while(list1->next)
        list1 = list1->next;
    list1->next = list2;

    return tmp;
}

// Patch connects the dangling arrows in the pointer list l to the state s: it sets *outp = s for each pointer outp in l.
void patch(StateList* list, NfaPtr state){
    StateList* next;

    while(list)
    {
        next = list->next;
        list->curr_state = state;
        list = next;
    }
}

void push(FragPtr stackp, FragPtr s)
{
    *stackp++ = *s;
}


/*  Converts the postfix regular expression returned by re_infix2postfix into the equivalent NFA.
 *  At the end of the compilation loop only one fragment remains, this fragment is patched to a matching state
 *  and the NFA is then complete
 */

/*  This is an implementation of Thompson's Construction algorithm (https://en.wikipedia.org/wiki/Thompson%27s_construction)
 *  Thompson's Construction algorithm, briefly described:
 *      -> Parse postfix expressions from left to right
 *      -> Build an NFA (in this case, an `nfa_fragment`) for each character read
 *      -> Each NFA built will require an initial state and an accepting state
 *      -> NFA pushed to stack (the nfa_fragment stack)
 *      -> When a "special" character (operator) is processed, stack will be popped and push accordingly
 *      -> NFA fragments will keep merging, creating bigger NFA fragments, until the compilation process is over
 *      -> Then the last NFA fragment will be popped and patched to the matching state, and the NFA is completed.
 */
NFA* post2nfa(char *postfix)
{
    char *p;
    Frag stack[1024], *stackp, e1, e2, e;
    int stp = 0;
    NfaPtr s;

    stackp = stack;
    for(p=postfix; *p; p++){
        switch(*p){
            /* compilation cases, described below */
            case '.':
                e2 = POP();
                e1 = POP();
                patch(e1.out, e2.start);
                push(stackp, initFrag(e1.start, e2.out));
                break;
            case '|':
                e2 = POP();
                e1 = POP();
                s = initNFAData(SPLIT, e1.start, e2.start, 0);
                push(stackp, initFrag(s, append(e1.out, e2.out)));
                break;
            case '?':
                e = POP();
                s = initNFAData(SPLIT, e.start, NULL, 0);
                push(stackp, initFrag(s, append(e.out, list1(&s->out1))));
                break;
            case '*':
                e = POP();
                s = initNFAData(SPLIT, e.start, NULL, 0);
                patch(e.out, s);
                push(stackp,initFrag(s, list1(&s->out1)));
                break;
            case '+':
                e = POP();
                s = initNFAData(SPLIT, e.start, NULL, 0);
                patch(e.out, s);
                push(stackp ,initFrag(e.start, list1(&s->out1)));
                break;
            default:
                s = initNFAData(*p, NULL, NULL,0);
                push(stackp, initFrag(s, list1(&s->out)));
                break;
        }
    }

    e = POP();
    patch(e.out, &matchstate);
    return e.start;
}