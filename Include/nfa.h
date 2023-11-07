//
// Created by Yotam Levit on 23/09/2023.
//

#ifndef REGEX_ENGINE_NFA_H
#define REGEX_ENGINE_NFA_H

#ifndef _BOOLEAN
#define _BOOLEAN
typedef enum { FALSE, TRUE } BOOLEAN;
#endif


typedef struct State
{
    char c; // Represents the char c<256 | c=256 in ascii represents a split | c=256 represents a match
    struct State *out, *out1; // Pointer to one of the next states | Pointer to the second of the next states
    int lastlist; // Lastlist is used during execution and is explained in the next section.
}NFA,* NfaPtr;


// Function declaretion
NfaPtr initNFA();
NfaPtr initNFAData(char c, NfaPtr out, NfaPtr out1, int lastlist);
void setNext(NfaPtr pNfa, char c);
BOOLEAN isEndState(NfaPtr pNFA);



#endif //REGEX_ENGINE_NFA_H
