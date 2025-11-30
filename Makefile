# Regex Engine Makefile
CC = gcc
CFLAGS = -Wall -Wextra -I.
TARGET = regex_engine
CLI_TARGET = regex
LIB_TARGET = libregex.a

# Installation prefix
PREFIX ?= /usr/local

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

# Default target - build both executables
all: $(TARGET) $(CLI_TARGET)

# Build static library
lib: $(LIB_TARGET)

$(LIB_TARGET): $(LIB_OBJS)
	ar rcs $@ $^
	ranlib $@
	@echo "Static library built: $(LIB_TARGET)"

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

# Install library and headers
install: lib
	install -d $(PREFIX)/lib $(PREFIX)/include/regex_engine
	install -m 644 $(LIB_TARGET) $(PREFIX)/lib/
	install -m 644 Include/*.h $(PREFIX)/include/regex_engine/
	@echo "Installed to $(PREFIX)"

# Uninstall library and headers
uninstall:
	rm -f $(PREFIX)/lib/$(LIB_TARGET)
	rm -rf $(PREFIX)/include/regex_engine
	@echo "Uninstalled from $(PREFIX)"

# Clean build artifacts
clean:
	rm -f src/*.o src/common/data_structures/*.o tests/*.o $(TARGET) $(CLI_TARGET) $(LIB_TARGET)
	@echo "Clean complete"

# Run the test suite
test: $(TARGET)
	./$(TARGET)

# Run the program (alias for test)
run: test

.PHONY: all lib install uninstall clean run test
