#include <stdio.h>
#include <stdlib.h>


struct nfa
{
    int h;
} typedef nfa;


nfa* parse_regex(char * regex)
{
  printf("return nfa struct");  
  nfa regex_nfa;
  regex_nfa.h = 1;

  return &regex_nfa;
}


int regcmp(char * string, nfa* regex_nfa)
{
  return 1;
}



int regex_comper(char * string, char* regex)
{
  nfa* regex_nfa = parse_regex(regex);
  
  return regcmp(string, regex_nfa);
}


int main() {
  char * str = "Hello World!";
  char * regex = "^Hello World!$";

  printf("%s", str);
  return 0;
}