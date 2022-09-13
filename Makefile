CC = gcc
CC_OBJ = $(CC) -c

BUILD = build
SRC = src
TEST_SRC = test
TEST_EXE = build/test

.PHONY: clean

clean:
	find . -name '*.o' -delete

$(BUILD)/argument_parser.o: $(SRC)/argument_parser.c
	@mkdir -p $(BUILD)
	$(CC_OBJ) $(SRC)/argument_parser.c -o $@

$(TEST_EXE)/test_parser.o: $(TEST_SRC)/test_parser.c
	@mkdir -p $(TEST_EXE)
	$(CC_OBJ) $(TEST_SRC)/test_parser.c -o $@

test_parser: $(BUILD)/argument_parser.o $(TEST_EXE)/test_parser.o
	$(CC) $(TEST_EXE)/$@.o $(BUILD)/argument_parser.o -o $(TEST_EXE)/$@
	./$(TEST_EXE)/$@