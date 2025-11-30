#include "Include/construction.h"
#include "Include/match.h"
#include "Include/nfa.h"
#include "Include/parse.h"
#include <stdio.h>
#include <string.h>

void print_usage(char *prog_name) {
  printf("Usage: %s <pattern> <text>\n", prog_name);
  printf("\nExamples:\n");
  printf("  %s 'a*b' 'aaab'      # Test if 'aaab' matches pattern 'a*b'\n",
         prog_name);
  printf("  %s '(cat|dog)*' 'catdogcat'  # Test alternation and repetition\n",
         prog_name);
  printf("\nSupported operators:\n");
  printf("  *   - Zero or more (e.g., a*)\n");
  printf("  +   - One or more (e.g., a+)\n");
  printf("  ?   - Zero or one (e.g., a?)\n");
  printf("  |   - Alternation/OR (e.g., a|b)\n");
  printf("  ()  - Grouping (e.g., (ab)*)\n");
  printf("  .   - Concatenation (implicit)\n");
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_usage(argv[0]);
    return 1;
  }

  char *pattern = argv[1];
  char *text = argv[2];

  printf("Pattern: '%s'\n", pattern);
  printf("Text:    '%s'\n", text);
  printf("---\n");

  // Process the pattern
  char *concat_exp = insertExplicitConcatOperator(pattern);
  char *postfix_exp = infixToPostfix(concat_exp);

  // Build NFA
  NfaPtr nfa = post2nfa(postfix_exp);

  // Match
  int result = match(nfa, text);

  // Print result
  if (result) {
    printf("✓ MATCH - The text matches the pattern!\n");
  } else {
    printf("✗ NO MATCH - The text does not match the pattern.\n");
  }

  // Cleanup
  free(concat_exp);
  free(postfix_exp);

  return result ? 0 : 1;
}
