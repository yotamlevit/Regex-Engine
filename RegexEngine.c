#include "Nfa.h"


#define IS_STR_END(ch) ch[1] == '\0' ? TRUE : FALSE
#define IS_REGEX_END(ch) *ch == '$' ? TRUE : FALSE



NfaNodePtr generate_regex_nfa(char* regex)
{
    NfaNodePtr regex_nfa;
    NfaNodePtr regex_nfa_ptr;
    //if (*regex++ == '^')
    //{
    nfaInit(&regex_nfa);
    nfaBuild(&regex_nfa, *regex++, IS_REGEX_END(regex));
    regex_nfa_ptr = regex_nfa;

    // Genereate basic nfs
    for (char* ch = regex; *ch != '\0'; ch++)
    {
        if (*ch == '[')
        {
            do {
                setNext(&regex_nfa_ptr, *++ch, IS_REGEX_END(ch));
            } while (*ch != ']');
        }
        else
            setNext(&regex_nfa_ptr, *ch, IS_REGEX_END(ch));

        regex_nfa_ptr = regex_nfa_ptr->next;
    }

    return regex_nfa;
    //}
    
}


BOOLEAN regex_check(NfaNodePtr regex, char* str)
{
    if (regex->egde_count == 1 && regex->next[0]->is_end_node)
        return TRUE;

    //if (regex->next->ch == *str)
      //  return regex_check(regex->next, ++str);

    return FALSE;
}


void print_nfa(NfaNodePtr nfa)
{
    while (!(nfa->is_end_node))
    {
        printf("%c", nfa->ch);
        printf("%d", nfa->is_end_node);
        nfa = nfa->next;
        printf("\n");
    }
    printf("%c", nfa->ch);

    printf("\n");
}



int main() {
    char* str = "Hello World!";
    char* regex = "^Hello World!$";
    NfaNodePtr regex_nfa;
    NfaNodePtr regex_nfa_ptr;
    BOOLEAN is_valid;
    regex_nfa = generate_regex_nfa(regex);
    regex_nfa_ptr = regex_nfa;
    //is_valid = regex_check(regex_nfa_ptr, str);
    //printf("%d", is_valid);
    //printf("\n");


    regex_nfa_ptr = regex_nfa;
    print_nfa(regex_nfa_ptr);
    
    
    

    nfaDelete(&regex_nfa);
    return 0;
}