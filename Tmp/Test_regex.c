#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STATES 12
#define NUM_ALPHABET 3 //#define NUM_ALPHABET 26

struct NFA {
    int states[MAX_STATES];
    int num_states;
    char alphabet[NUM_ALPHABET];
    int num_alphabets;
    int start_state;
    int final_states[MAX_STATES];
    int num_final_states;
    int*** pTransitions;
    int transitions[MAX_STATES][NUM_ALPHABET + 1][MAX_STATES];
};

struct REGEX_RESPONSE {
    int match;
    char* match_pointer;
};

void init_nfa(struct NFA *nfa) {
    int i;
    nfa->num_states = 0;
    nfa->num_final_states = 0;
    nfa->start_state = 0;
    nfa->num_alphabets = NUM_ALPHABET;
    for (i = 0; i < NUM_ALPHABET; i++)
    {
        nfa->alphabet[i] = (char)i+'a';
    }

    for (i = 0; i < MAX_STATES; i++)
    {
        nfa->final_states[i] = 0;
    }
    
    //memset(nfa->final_states, 0, MAX_STATES)
    //nfa->final_states[MAX_STATES] = { 0 };

    //nfa->pTransitions = new 

    memset(nfa->transitions, 0, sizeof(nfa->transitions));
}


void add_transition(struct NFA *nfa, int current_state, char input_char, int next_state) {
    int input_index = input_char - 'a';
    nfa->transitions[current_state][input_index][next_state] = 1;
}

void add_epsilon_transition(struct NFA *nfa, int current_state, int next_state) {
    nfa->transitions[current_state][nfa->num_alphabets][next_state] = 1;
}

void add_range_transition(struct NFA *nfa, int current_state, char start_char, char end_char, int next_state) {
    for (char c = start_char; c <= end_char; c++) {
        add_transition(nfa, current_state, c, next_state);
    }
}

void add_star_transition(struct NFA *nfa, int origin_state, int last_start_state) {
    add_epsilon_transition(nfa, origin_state, last_start_state);
}

void add_or_transition(struct NFA *nfa, int current_state, int next_state1, int next_state2) {
    add_epsilon_transition(nfa, current_state, next_state1);
    add_epsilon_transition(nfa, current_state, next_state2);
    add_epsilon_transition(nfa, next_state1, nfa->num_states);
    add_epsilon_transition(nfa, next_state2, nfa->num_states);
    nfa->final_states[nfa->num_final_states++] = nfa->num_states++;
}

void add_concat_transition(struct NFA *nfa, int current_state, int next_state) {
    add_epsilon_transition(nfa, current_state, next_state);
}

// Helper function to check if an array contains a value
int contains(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int match(struct NFA *nfa, char *input) {
    int current_states[MAX_STATES];
    int num_current_states = 1;
    current_states[0] = nfa->start_state;

    // Loop through the input string
    int i = 0;
    while (input[i] != '\0') {
        char c = input[i];

        // Compute the next set of states based on the current set and the input character
        int next_states[MAX_STATES];
        int num_next_states = 0;
        for (int j = 0; j < num_current_states; j++) {
            int state = current_states[j];
            for (int k = 0; k < nfa->num_states; k++) {
                if (nfa->transitions[state][nfa->num_alphabets][k] == 1) {
                    // Epsilon transition
                    if (!contains(next_states, num_next_states, k)) {
                        next_states[num_next_states++] = k;
                    }
                } else if (nfa->transitions[state][c - 'a'][k] == 1) {
                    // Character transition
                    if (!contains(next_states, num_next_states, k)) {
                        next_states[num_next_states++] = k;
                    }
                }
            }
        }

        // If there are no next states, the input is invalid
        if (num_next_states == 0) {
            return 0;
        }

        // Update the current set of states
        num_current_states = num_next_states;
        memcpy(current_states, next_states, num_current_states * sizeof(int));

        // Move to the next character in the input string
        i++;
    }

    // Check if any of the current states are final states
    for (int j = 0; j < num_current_states; j++) {
        int state = current_states[j];
        for (int k = 0; k < nfa->num_final_states; k++) {
            if (state == nfa->final_states[k]) {
                return 1;
            }
        }
    }

    return 0;
}


int in_array(int value, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

void epsilon_closure(struct NFA *nfa, int state, int *closure_states, int *num_closure_states) {
    // Initialize the closure_states array with the current state
    closure_states[*num_closure_states] = state;
    (*num_closure_states)++;
    
    // Iterate through the epsilon transitions from the current state
    for (int i = 0; i < nfa->num_states; i++) {
        if (nfa->transitions[state][nfa->num_alphabets][i] && !in_array(i, closure_states, *num_closure_states)) {
            // Recursively call the epsilon_closure function on the next state
            epsilon_closure(nfa, i, closure_states, num_closure_states);
        }
    }
}


int myMatch(struct NFA* nfa, char* input, int currentState) {
    printf("Current state: %d \n", currentState);

    int input_index = *input - 'a';

    if (nfa->final_states[currentState] && *input == '\0')
        return 1;

    if (*input == '\0')
        return 0;

    for (int i = 0; i < MAX_STATES; i++)
    {
        //Epsilon transition
        if (nfa->transitions[currentState][nfa->num_alphabets][i] == 1)
        {
            printf("\nEpsilon\n");
            return myMatch(nfa, input+1, i);
        }
    }

    for (int i = 0; i < MAX_STATES; i++)
    {

        //Character transition
        if (nfa->transitions[currentState][input_index][i] == 1)
        {
            return myMatch(nfa, input + 1, currentState + 1);
        }
    }

    return 0;
}


int match_regex(struct NFA *nfa, char *input) {
    int current_states[MAX_STATES];
    int num_current_states = 1;
    current_states[0] = nfa->start_state;

    int closure_states[MAX_STATES];
    int num_closure_states = 0;
    epsilon_closure(nfa, current_states[0], closure_states, &num_closure_states);
    memcpy(current_states, closure_states, num_closure_states * sizeof(int));
    num_current_states = num_closure_states;

    for (int i = 0; input[i] != '\0'; i++) {
        int next_states[MAX_STATES];
        int num_next_states = 0;
        char c = input[i];
        for (int j = 0; j < num_current_states; j++) {
            int state = current_states[j];
            for (int k = 0; k < nfa->num_states; k++) {
                if (nfa->transitions[state][NUM_ALPHABET][k] && !in_array(k, next_states, num_next_states)) {
                    next_states[num_next_states++] = k;
                }
            }
            for (int k = 0; k < nfa->num_alphabets; k++) {
                if (nfa->alphabet[k] == c) {
                    for (int l = 0; l < nfa->num_states; l++) {
                        if (nfa->transitions[state][k][l] && !in_array(l, next_states, num_next_states)) {
                            next_states[num_next_states++] = l;
                        }
                    }
                }
            }
        }
        num_closure_states = 0;
        for (int j = 0; j < num_next_states; j++) {
            epsilon_closure(nfa, next_states[j], closure_states, &num_closure_states);
        }
        memcpy(current_states, closure_states, num_closure_states * sizeof(int));
        num_current_states = num_closure_states;
    }

    for (int i = 0; i < num_current_states; i++) {
        int state = current_states[i];
        for (int j = 0; j < nfa->num_final_states; j++) {
            if (state == nfa->final_states[j]) {
                return 1;
            }
        }
    }
    return 0;
}



void regex_to_nfa(struct NFA *nfa, char *regex) {
    // add the alphabet to the NFA
    int i = 0;

    printf("Regex is: %s\n", regex);
    int current_state = nfa->start_state;
    i = 0;
    while (regex[i] != '\0') {
        char c = regex[i];
        printf("Char is: %c\n", c);
        if (c == '|') {
            // add an or transition
            int next_state1 = nfa->num_states++;
            int next_state2 = nfa->num_states++;
            add_or_transition(nfa, current_state, next_state1, next_state2);
            current_state = nfa->num_states++;
        } else if (c == '*') {
            // add a star transition
            //int next_state = nfa->num_states++;
            add_star_transition(nfa, current_state, current_state);
            //current_state;// = next_state;
        } else {
            // add a character transition
            int next_state = nfa->num_states++;
            add_transition(nfa, current_state, c, next_state);
            current_state = next_state;
        }
        i++;
    }
    // add the final state
    nfa->final_states[nfa->num_final_states++] = current_state;
}

void my_regex_to_nfa(struct NFA* nfa, char* regex) {
    // add the alphabet to the NFA
    int i = 0;

    printf("Regex is: %s\n", regex);
    int current_state = nfa->start_state;

    char* c = regex;
    while (*c != '\0') {
        //printf("Char is: %c\n", c);
        if (*c == '|') {
            // add an or transition
            int next_state1 = nfa->num_states++;
            int next_state2 = nfa->num_states++;
            add_or_transition(nfa, current_state, next_state1, next_state2);
            current_state = nfa->num_states++;
        }
        else if (*c == '*') {
            // add a star transition
            //int next_state = nfa->num_states - 1;
            current_state = nfa->num_states++;
            add_transition(nfa, current_state, *c++, current_state);
            nfa->final_states[current_state] = 1;
            c++;
            //add_star_transition(nfa, current_state, next_state);
            //current_state = next_state;
        }
        else {
            // add a character transition
            int next_state = ++nfa->num_states;
            add_transition(nfa, current_state, *c++, next_state);
            current_state = next_state;
        }

    }
    // add the final state
    nfa->final_states[current_state] = 1;
}

void print_nfa(struct NFA *nfa) {
    printf("Number of states: %d\n", nfa->num_states);
    printf("Start state: %d\n", nfa->start_state);
    printf("Number of final states: %d\n", nfa->num_final_states);
    printf("Final states: ");
    for (int i = 0; i < nfa->num_final_states; i++) {
        printf("%d ", nfa->final_states[i]);
    }
    printf("\n");
    printf("Transitions:\n");
    for (int i = 0; i < nfa->num_states; i++) {
        printf("State %d:\n", i);
        for (int j = 0; j <= nfa->num_alphabets; j++) {
            printf("  On %c: ", j == nfa->num_alphabets ? '-' : nfa->alphabet[j]);
            for (int k = 0; k < nfa->num_states; k++) {
                if (nfa->transitions[i][j][k]) {
                    printf("%d ", k);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    //struct NFA nfa;
    //nfa.num_states = 2;
    //nfa.states[0] = 0;
    //nfa.states[1] = 1;
//
    //nfa.alphabet[0] = 'a';
    //nfa.alphabet[1] = 'b';
    //nfa.num_alphabets = 2;
//
    //nfa.start_state = 0;
//
    //nfa.final_states[0] = 1;
    //nfa.num_final_states = 1;
//
    //add_transition(&nfa, 0, 'a', 1);
    // 
    //char * regex = "a*b*c*d*e*f*g*h*i*j*k*";
    char* regex = "a*b*";
    struct NFA* nfa;
    nfa = NULL;
    nfa = (struct NFA *)malloc(sizeof(struct NFA));
    printf("NFA alocated in the memory.\n");
    init_nfa(nfa);
    printf("NFA INITIALIZED .\n");
    //nfa->start_state=0;
    //nfa->num_states=0;
    //regex_to_nfa(nfa, regex);

    regex_to_nfa(nfa, regex);
    printf("NFA was built.\n");
    

    //printf("\nasdasd\n");
    //print_nfa(nfa);

    printf("\nMatch\n");
    clock_t start_clk = clock();
    printf("the answer is: %d\n", match(nfa, "cdb"));//aaabbbcccdddeeefffggghhhiiijk
    printf("Processor time used by program: %lg sec.\n", \
    (clock() - start_clk) / (long double) CLOCKS_PER_SEC);
    //clock_t start_clk = clock();

    start_clk = clock();
    printf("the answer is: %d\n", myMatch(nfa, "cdb", 0));
    printf("Processor time used by program: %lg sec.\n", \
    (clock() - start_clk) / (long double)CLOCKS_PER_SEC);

    //start_clk = clock();
    //printf("the answer is: %d\n", match_regex(nfa, "aaabbbcccdddeeefffggghhhiiijk"));
    //printf("Processor time used by program: %lg sec.\n", \
    //(clock() - start_clk) / (long double) CLOCKS_PER_SEC);
    free(nfa);
    return 0;
}
