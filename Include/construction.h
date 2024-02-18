//
// Created by Yotam Levit on 24/09/2023.
//

#ifndef REGEX_ENGINE_CONSTRUCTION_H
#define REGEX_ENGINE_CONSTRUCTION_H


#include "construction.h"

#include "Include/nfa.h"
#include <stdlib.h>



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
NfaPtr post2nfa(char *postfix);


#endif //REGEX_ENGINE_CONSTRUCTION_H
