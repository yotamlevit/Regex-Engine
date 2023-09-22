# Regex-Engine
A C lang regex engine using NFA




## Regex Engine Steps:

- Parse
- Construction
- Match

--------


### Parse
Using the Shunting-Yard Algorithm. we convert the regex expression from infix to postfix

###### What is the Shunting-Yard Algorithm?
This algorithm is an operator-precedence parser that is specifically designed to parse mathematical expressions into postfix notation for computation. Postfix notation (Reverse Polish notation) is a mathematical notation in which the operators follow the numbers.

######  Code: /src/parse.c

---------------------------------


### Construction
Using Thomapson`s construction Algorithm we convert the postfix expression into a NFA structure

----------

### Match
Then using the nfa that represents the regex we can run our input string and return if the input maches the regex or not


----------------