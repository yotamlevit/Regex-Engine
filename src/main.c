#include "Include/construction.h"
#include "Include/match.h"
#include "Include/nfa.h"
#include "Include/parse.h"
#include <stdio.h>
#include <string.h>

void test_regex(char *pattern, char *text, int expected) {
  char *concat_exp = insertExplicitConcatOperator(pattern);
  char *postfix_exp = infixToPostfix(concat_exp);
  NfaPtr nfa = post2nfa(postfix_exp);
  int result = match(nfa, text);

  printf("Pattern: %-15s Text: %-15s Expected: %s, Got: %s -> %s\n", pattern,
         text, expected ? "MATCH" : "NO MATCH", result ? "MATCH" : "NO MATCH",
         (result == expected) ? "✓ PASS" : "✗ FAIL");

  free(concat_exp);
  free(postfix_exp);
}

int main() {
  printf("=== Regex Engine Test Suite ===\n\n");

  printf("--- Basic Literal Tests ---\n");
  test_regex("abc", "abc", 1); // Should match
  test_regex("abc", "ab", 0);  // Should not match
  test_regex("abc", "abcd",
             0); // Should not match (we match exact, not substring)

  printf("\n--- Zero or More (*) Tests ---\n");
  test_regex("a*", "", 1);      // Zero 'a's
  test_regex("a*", "a", 1);     // One 'a'
  test_regex("a*", "aaa", 1);   // Multiple 'a's
  test_regex("a*b", "b", 1);    // Zero 'a's followed by 'b'
  test_regex("a*b", "aaab", 1); // Multiple 'a's followed by 'b'

  printf("\n--- One or More (+) Tests ---\n");
  test_regex("a+", "", 0);      // Zero 'a's - should fail
  test_regex("a+", "a", 1);     // One 'a'
  test_regex("a+", "aaa", 1);   // Multiple 'a's
  test_regex("a+b", "ab", 1);   // One 'a' followed by 'b'
  test_regex("a+b", "aaab", 1); // Multiple 'a's followed by 'b'

  printf("\n--- Zero or One (?) Tests ---\n");
  test_regex("a?", "", 1);    // Zero 'a's
  test_regex("a?", "a", 1);   // One 'a'
  test_regex("a?", "aa", 0);  // Two 'a's - should fail
  test_regex("a?b", "b", 1);  // Zero 'a's followed by 'b'
  test_regex("a?b", "ab", 1); // One 'a' followed by 'b'

  printf("\n--- Alternation (|) Tests ---\n");
  test_regex("a|b", "a", 1);    // Match 'a'
  test_regex("a|b", "b", 1);    // Match 'b'
  test_regex("a|b", "c", 0);    // No match
  test_regex("ab|cd", "ab", 1); // Match first alternative
  test_regex("ab|cd", "cd", 1); // Match second alternative

  printf("\n--- Complex Pattern Tests ---\n");
  test_regex("(a|b)*", "", 1);         // Zero characters
  test_regex("(a|b)*", "ababab", 1);   // Mix of 'a' and 'b'
  test_regex("(a|b)*c", "aabbc", 1);   // Mix followed by 'c'
  test_regex("a(b|c)*d", "ad", 1);     // 'a', zero (b|c)s, 'd'
  test_regex("a(b|c)*d", "abcd", 1);   // 'a', one 'b', one 'c', 'd'
  test_regex("a(b|c)*d", "abbbcd", 1); // 'a', multiple b/c, 'd'

  printf("\n--- Intentional Failure Tests (Edge Cases) ---\n");
  test_regex("abc", "abd", 0);    // Similar but different
  test_regex("a+b", "b", 0);      // Missing required 'a'
  test_regex("a*b", "a", 0);      // Missing required 'b'
  test_regex("(a|b)", "c", 0);    // No alternation matches
  test_regex("a?a?a", "aaaa", 0); // Too many 'a's (max 3)
  test_regex("(ab)+", "aba", 0);  // Incomplete last repetition
  test_regex("x|y|z", "w", 0);    // None of the options match

  printf("\n--- Multi-Character Patterns ---\n");
  test_regex("hello", "hello", 1);  // Full word match
  test_regex("hello", "hell", 0);   // Prefix doesn't match
  test_regex("cat|dog", "cat", 1);  // First alternative
  test_regex("cat|dog", "dog", 1);  // Second alternative
  test_regex("cat|dog", "bird", 0); // Neither alternative
  test_regex("x*y*z", "z", 1);      // Zero x's and y's
  test_regex("x*y*z", "xxyyyz", 1); // Multiple x's and y's
  test_regex("x*y*z", "xyz", 1);    // One of each
  test_regex("x*y*z", "xz", 1);     // Zero y's

  printf("\n--- Numeric and Mixed Character Tests ---\n");
  test_regex("0*1", "1", 1);        // Zero 0's followed by 1
  test_regex("0*1", "0001", 1);     // Multiple 0's followed by 1
  test_regex("a1b2", "a1b2", 1);    // Alphanumeric pattern
  test_regex("a1b2", "a2b1", 0);    // Wrong order
  test_regex("(0|1)*", "01010", 1); // Binary string
  test_regex("(0|1)*", "012", 0);   // Invalid binary (contains 2)

  printf("\n--- Nested Grouping Tests ---\n");
  test_regex("((a|b)c)*", "", 1);     // Zero repetitions of (a|b)c
  test_regex("((a|b)c)*", "ac", 1);   // One repetition of ac
  test_regex("((a|b)c)*", "bcac", 1); // Two repetitions
  test_regex("((a|b)c)*", "abc", 0);  // Incomplete - 'ab' without 'c'
  test_regex("(x(y|z))*", "xyxz", 1); // Nested alternation
  test_regex("(x(y|z))*", "xyx", 0);  // Incomplete last group

  printf("\n--- Stress Tests (Longer Patterns) ---\n");
  test_regex("(a|b|c|d|e)*", "abcdeabcde", 1); // Many alternatives
  test_regex("x*y*z*w*", "xxyyyyzzwww", 1);    // Multiple sequential wildcards
  test_regex("(test)+", "testtesttest", 1);    // Word repetition
  test_regex("(test)+", "testestest", 0);      // Broken repetition

  printf("\n=== Test Suite Complete ===\n");
  printf("\nResults: See above for pass/fail status\n");
  return 0;
}
