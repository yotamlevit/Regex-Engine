# Regex Engine Makefile
CC = gcc
CFLAGS = -Wall -Wextra -I.
TARGET = regex_engine
CLI_TARGET = regex

# Core library source files (shared between test suite and CLI)
LIB_SRCS = src/parse.c \
           src/construction.c \
           src/match.c \
           src/common/data_structures/nfa.c \
           src/common/data_structures/stack_char.c

# Test suite source
TEST_SRCS = tests/test_suite.c $(LIB_SRCS)

# CLI source
CLI_SRCS = tests/regex_cli.c $(LIB_SRCS)

# Object files
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Default target - build both
all: $(TARGET) $(CLI_TARGET)

# Link the test suite executable
$(TARGET): tests/test_suite.o $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Test suite built: ./$(TARGET)"

# Link the CLI executable
$(CLI_TARGET): tests/regex_cli.o $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "CLI tool built: ./$(CLI_TARGET)"

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f src/*.o src/common/data_structures/*.o tests/*.o $(TARGET) $(CLI_TARGET)
	@echo "Clean complete"

# Run the test suite
test: $(TARGET)
	./$(TARGET)

# Run the program (alias for test)
run: test

.PHONY: all clean run test
