//
// Created by Yotam Levit on 24/09/2023.
//

#include "Include/construction.h"
#include "Include/nfa.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StateList {
  struct StateList *next;
  NfaPtr currState;
} StateList, *StateListPtr;

StateListPtr initList(NfaPtr *outp) {
  StateListPtr newList = (StateListPtr)outp;
  newList->next = NULL;

  return newList;
}

typedef struct Frag {
  NfaPtr start;
  StateListPtr out;
} Frag, *FragPtr;

Frag *initFrag(NfaPtr start, StateListPtr out) {
  // Take memory for the new node
  FragPtr newFrag = (FragPtr)malloc(sizeof(Frag));

  // Set the artibutes of the node
  newFrag->start = start;
  newFrag->out = out;

  // Return the new node
  return newFrag;
}

// Append concatenates two pointer lists, returning the result.
StateList *append(StateList *list1, StateList *list2) {
  StateList *tmp = list1;
  // traverse till the linked list's end and set the end item's next to the
  // second_list's start
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = list2;

  return list1;
}

// Patch connects the dangling arrows in the pointer list l to the state s: it
// sets *outp = s for each pointer outp in l.
void patch(StateList *list, NfaPtr state) {
  StateList *next;
  for (; list; list = next) {
    next = list->next;
    *(NfaPtr *)list = state;
  }
}

/*  Converts the postfix regular expression returned by re_infix2postfix into
 * the equivalent NFA. At the end of the compilation loop only one fragment
 * remains, this fragment is patched to a matching state and the NFA is then
 * complete
 */

/*  This is an implementation of Thompson's Construction algorithm
 * (https://en.wikipedia.org/wiki/Thompson%27s_construction) Thompson's
 * Construction algorithm, briefly described:
 *      -> Parse postfix expressions from left to right
 *      -> Build an NFA (in this case, an `nfa_fragment`) for each character
 * read
 *      -> Each NFA built will require an initial state and an accepting state
 *      -> NFA pushed to stack (the nfa_fragment stack)
 *      -> When a "special" character (operator) is processed, stack will be
 * popped and push accordingly
 *      -> NFA fragments will keep merging, creating bigger NFA fragments, until
 * the compilation process is over
 *      -> Then the last NFA fragment will be popped and patched to the matching
 * state, and the NFA is completed.
 */
NfaPtr post2nfa(char *postfix) {
  char *p;
  Frag stack[1024], *stackp, e1, e2, e;
  NfaPtr s;
  stackp = stack;

#define PUSH(f) *stackp++ = f
#define POP() *--stackp

  for (p = postfix; *p; p++) {
    switch (*p) {
    /* compilation cases, described below */
    case '.':
      e2 = POP();
      e1 = POP();
      patch(e1.out, e2.start);
      PUSH(*initFrag(e1.start, e2.out));
      break;
    case '|':
      e2 = POP();
      e1 = POP();
      s = initNFAData(SPLIT, e1.start, e2.start, 0);
      PUSH(*initFrag(s, append(e1.out, e2.out)));
      break;
    case '?':
      e = POP();
      s = initNFAData(SPLIT, e.start, NULL, 0);
      PUSH(*initFrag(s, append(e.out, initList(&s->out1))));
      break;
    case '*':
      e = POP();
      s = initNFAData(SPLIT, e.start, NULL, 0);
      patch(e.out, s);
      PUSH(*initFrag(s, initList(&s->out1)));
      break;
    case '+':
      e = POP();
      s = initNFAData(SPLIT, e.start, NULL, 0);
      patch(e.out, s);
      PUSH(*initFrag(e.start, initList(&s->out1)));
      break;
    default:
      s = initNFAData(*p, NULL, NULL, 0);
      PUSH(*initFrag(s, initList(&s->out)));
      break;
    }
  }

  e = POP();

  if (stackp != stack)
    return NULL;

  NfaPtr matchstate = initNFA();
  matchstate->c = MATCH;

  patch(e.out, matchstate);

  return e.start;
}