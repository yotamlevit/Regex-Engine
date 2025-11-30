# Regex Engine - CLI Tool Usage Guide

## Overview

The regex engine now includes two executables:

- **`regex_engine`** - Comprehensive automated test suite
- **`regex`** - Interactive CLI tool for manual testing

## Building

```bash
make          # Build both executables
make clean    # Remove build artifacts
make test     # Run the automated test suite
```

## CLI Tool Usage

### Basic Syntax

```bash
./regex '<pattern>' '<text>'
```

### Examples

**Simple patterns:**

```bash
./regex 'hello' 'hello'
# ✓ MATCH

./regex 'abc' 'abd'
# ✗ NO MATCH
```

**Zero or more (\*):**

```bash
./regex 'a*b' 'aaab'
# ✓ MATCH

./regex '0*1' '000001'
# ✓ MATCH
```

**One or more (+):**

```bash
./regex 'a+' 'aaa'
# ✓ MATCH

./regex 'a+b' 'b'
# ✗ NO MATCH (missing required 'a')
```

**Zero or one (?):**

```bash
./regex 'colou?r' 'color'
# ✓ MATCH

./regex 'colou?r' 'colour'
# ✓ MATCH
```

**Alternation (|):**

```bash
./regex 'cat|dog' 'cat'
# ✓ MATCH

./regex 'yes|no' 'maybe'
# ✗ NO MATCH
```

**Complex patterns:**

```bash
./regex '(cat|dog)+' 'catdogcat'
# ✓ MATCH

./regex '(0|1)*' '01010'
# ✓ MATCH (binary string)

./regex 'a(b|c)*d' 'abbbcd'
# ✓ MATCH

./regex '((a|b)c)*' 'acbc'
# ✓ MATCH (nested grouping)
```

**Multi-character patterns:**

```bash
./regex 'hello' 'hello'
# ✓ MATCH

./regex '(test)+' 'testtesttest'
# ✓ MATCH

./regex 'x*y*z' 'xxyyyz'
# ✓ MATCH
```

## Test Suite

Run the comprehensive test suite:

```bash
./regex_engine
```

### Test Coverage (68 Tests Total)

- ✅ **Basic Literals** - Exact string matching
- ✅ **Zero or More (\*)** - Including edge cases with empty strings
- ✅ **One or More (+)** - Ensuring at least one occurrence required
- ✅ **Zero or One (?)** - Optional character matching
- ✅ **Alternation (|)** - OR logic between patterns
- ✅ **Complex Patterns** - Nested grouping and combinations
- ✅ **Intentional Failures** - Edge cases that should NOT match
- ✅ **Multi-Character** - Word-level patterns (hello, cat, dog, test)
- ✅ **Numeric/Mixed** - Alphanumeric patterns (0\*1, a1b2, binary strings)
- ✅ **Nested Grouping** - Deep nesting like ((a|b)c)\*
- ✅ **Stress Tests** - Long patterns with many alternatives

## Supported Operators

| Operator | Description      | Example | Matches             |
| -------- | ---------------- | ------- | ------------------- |
| Literal  | Exact character  | `abc`   | "abc"               |
| `*`      | Zero or more     | `a*`    | "", "a", "aaa"      |
| `+`      | One or more      | `a+`    | "a", "aaa" (not "") |
| `?`      | Zero or one      | `a?`    | "", "a" (not "aa")  |
| `\|`     | Alternation (OR) | `a\|b`  | "a" or "b"          |
| `()`     | Grouping         | `(ab)*` | "", "ab", "abab"    |
| `.`      | Concatenation    | `ab`    | "ab" (implicit)     |

## Exit Codes

The CLI tool returns:

- **0** - Match found
- **1** - No match or invalid usage

This allows for shell scripting:

```bash
if ./regex 'pattern' 'text'; then
    echo "Matched!"
else
    echo "No match"
fi
```

## Tips

1. **Use quotes** around patterns and text to prevent shell interpretation
2. **Test incrementally** - start with simple patterns, add complexity
3. **Check edge cases** - empty strings, single characters, long repetitions
4. **Escape special characters** in the shell if needed (though quotes usually suffice)

## Limitations

- No character classes like `[a-z]` or `\d`
- No anchors like `^` (start) or `$` (end)
- No escape sequences like `\n` or `\t`
- No backreferences or lookahead/lookbehind
- Exact match only (not substring searching)

These are intentional - this is a minimal implementation of Thompson's NFA construction algorithm designed for educational purposes.
