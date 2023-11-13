//
// Created by Yotam Levit on 24/09/2023.
//

#include "construction.h"

#include "Include/nfa.h"
#include <stdlib.h>

#define PUSH(stackp, s) *stackp++ = s
#define POP()   *--stackp
#define SPLIT 256


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


//List1 creates a new pointer list containing the single pointer outp.
// Append concatenates two pointer lists, returning the result.
//
// Patch connects the dangling arrows in the pointer list l to the state s: it sets *outp = s for each pointer outp in l.


NfaPtr* *list1(NfaPtr* outp)
{
    NfaPtr* * NfaListPtr = (NfaPtr**)malloc(sizeof(NfaPtr*));
    *NfaListPtr = outp;

    return NfaListPtr;
}

NfaPtr* *append(NfaPtr* *l1, NfaPtr* *l2)
{
    return NULL;
}

void patch(NfaPtr* *l, NFA *s){

}

void push(FragPtr stackp, FragPtr s)
{
    *stackp++ = *s;
}

NFA* post2nfa(char *postfix)
{
    char *p;
    Frag stack[1000], *stackp, e1, e2, e;
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
            default:
                s = initNFAData(*p, NULL, NULL,0);
                push(stackp, initFrag(s, list1(&s->out)));
                break;
        }
    }

    e = POP();
    //patch(e.out, matchstate);
    return e.start;
}