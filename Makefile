CC = gcc
CC_OBJ = $(CC) -c

BUILD = build
SRC = src
TEST_SRC = test
TEST_EXE = build/test

.PHONY: clean

clean:
	rm -rf $(BUILD)/*
	rmdir $(BUILD)

argument_parser: $(SRC)/argument_parser.c
	@mkdir -p $(BUILD)
	$(CC_OBJ) $(SRC)/argument_parser.c -o $(BUILD)/$@.o

test_parser: argument_parser $(TEST_SRC)/test_parser.c
	@mkdir -p $(TEST_EXE)
	$(CC_OBJ) $(TEST_SRC)/test_parser.c -o $(TEST_EXE)/$@.o
	$(CC) $(TEST_EXE)/$@.o $(BUILD)/argument_parser.o -o $(TEST_EXE)/$@
	./$(TEST_EXE)/$@