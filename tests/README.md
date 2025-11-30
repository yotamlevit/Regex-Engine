# Tests Directory

This directory contains all test files for the Regex Engine project.

## Files

### `test_suite.c`

Comprehensive automated test suite with 61 test cases covering:

- Basic literal matching
- Repetition operators (`*`, `+`, `?`)
- Alternation (`|`)
- Complex nested patterns
- Edge cases and intentional failures
- Multi-character patterns
- Numeric and mixed patterns

**Run:** `make test` or `./regex_engine`

### `regex_cli.c`

Interactive command-line tool for manual testing.

**Usage:** `./regex 'pattern' 'text'`

**Examples:**

```bash
./regex 'hello' 'hello'
./regex '(cat|dog)+' 'catdogcat'
./regex '(0|1)*' '01010'
```

## Test Coverage

**61 tests total** covering:

- 3 basic literal tests
- 5 zero-or-more (`*`) tests
- 5 one-or-more (`+`) tests
- 5 zero-or-one (`?`) tests
- 5 alternation (`|`) tests
- 6 complex pattern tests
- 7 intentional failure tests
- 9 multi-character pattern tests
- 6 numeric/mixed tests
- 6 nested grouping tests
- 4 stress tests

**Current Status:** 61/61 PASSING ✅

## Why Tests Are Here

Tests are in a dedicated `tests/` directory rather than mixed with source code (`src/`) or hidden in a temporary folder (`Tmp/`). This keeps the codebase organized:

```
src/           # Core implementation
  parse.c
  construction.c
  match.c
  ...

tests/         # All test files
  test_suite.c
  regex_cli.c
```

This is a common pattern in C projects and makes it clear where to find tests vs. implementation.
