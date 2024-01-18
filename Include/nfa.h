//
// Created by Yotam Levit on 23/09/2023.
//

#ifndef REGEX_ENGINE_NFA_H
#define REGEX_ENGINE_NFA_H

#ifndef _BOOLEAN
#define _BOOLEAN
typedef enum { FALSE, TRUE } BOOLEAN;
#endif

/*  Currently, this implementation only implements the repetition metacharacters ('+', '?', '*')
*  And concatenation/alteration ("AND"/"OR")
*  All of which can be represented with a partial NFA that has only two (or less) arrows going out of it
*  i.e only two decisions to make
*  This is the reasoning behind every state having only two pointers to other states.
*
*   `fragment_type` determines the "structure" of the state.
*   If `fragment_type` <= 2^8 - 1 (possible extended ASCII characters), then this state has only one outward transition
*   If `fragment_type` == 2^8, then this state is a split state (has two outward transitions)
*   If `fragment_type` == 2^8 + 1, then this state is an accepting state (a correct match)
*
*                                      __
*         (ASCII char)         |      /   <out_up>   |
*    <S> ==============> <out> | <S> =               |      <AC>
*                              |      \__ <out_down> |
*        f_t <= 2^8 - 1                f_t = 2^8         f_t = 2^8 + 1
*   f_t = fragment_type
    */
typedef struct State
{
    char c; // Represents the char c<256 | c=256 in ascii represents a split | c=257 represents a match
    struct State *out, *out1; // Pointer to one of the next states | Pointer to the second of the next states
    int lastlist; // Lastlist is used during execution and is explained in the next section.
}NFA,* NfaPtr;


// Function declaretion
NfaPtr initNFA();
NfaPtr initNFAData(char c, NfaPtr out, NfaPtr out1, int lastlist);
void setNext(NfaPtr pNfa, char c);
BOOLEAN isEndState(NfaPtr pNFA);



#endif //REGEX_ENGINE_NFA_H
