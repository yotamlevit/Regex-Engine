# Regex-Engine
A C lang regex engine using NFA based on Ken Thompson`s paper
It was introduced in his 1968 CACM paper.
This implementation compiles Regular Expressions to Non-Deterministic Finite Automatas (NFA)

Currently, this implementation only implements the repetition metacharacters ('+', '?', '*') and concatenation/alteration ("AND"/"OR")
# <ins>This is a work in progress!!!
# <ins>This is a work in progress!!!
# <ins>This is a work in progress!!!
# <ins>This is a work in progress!!!




## Regex Engine Steps:

1. [Parse](#parse)
2. [Construction](#construction)
3. [Match](#match)

--------


### Parse
In thompson`s paper the compiler builds an NFA from a regular expression in postfix notation with dot (.) added as an explicit concatenation operator.

Therefor the parser steps are:
1. Adding an explicit concatenation operator - the '.' character will be used as in thompson\`s paper. The implementation is in the `insertExplicitConcatOperator` function.


2. Converting the expression from infix notation to postfix notation. The implementation is in the `infixToPostfix` function.
The convertion itself is sing the Shunting-Yard Algorithm.

###### What is the Shunting-Yard Algorithm?
This algorithm is an operator-precedence parser that is specifically designed to parse mathematical expressions into postfix notation for computation. Postfix notation (Reverse Polish notation) is a mathematical notation in which the operators follow the numbers.

######  Code: /src/parse.c

---------------------------------


### Construction
Using Thomapson`s construction Algorithm we convert the postfix expression into a NFA structure

###### What is Thomapson`s construction Algorithm?

Thompson's Construction is a method in which we transform a regular expression
into a (NFA) non-deterministic finite automaton.
This can further be used to match strings against the expression.

###### NFA representation:
In /src/data_structures/nfa.c there is a structure that represent the NFA
```angular2html
typedef struct State
{
    char c; // Represents the char c<256 | c=256 in ascii represents a split | c=256 represents a match
    struct State *out, *out1; // Pointer to one of the next states | Pointer to the second of the next states
    int lastlist; // Lastlist is used during execution and is explained in the next section.
}NFA,* NfaPtr;
```

State can represent three types of NFA fragments, depending on c values:

![State Types Photo](relative%20path/../Images/StateStatus.png?raw=true "State Status")







###### Code:
* construction: /src/construction.c
* NFA structure: /src/data_structures/nfa.c

----------

### Match
Then using the nfa that represents the regex we can run our input string and return if the input maches the regex or not


----------------