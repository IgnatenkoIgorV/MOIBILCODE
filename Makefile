CC = gcc
CFLAGS = -Wall -Wextra -Iincludes
LIBS = -lsqlite3
SRC_DIR = src
BIN_DIR = bin

# Все исходники, КРОМЕ main.c (для тестов)
SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/test_all

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Основное приложение (с main.c)
$(TARGET): $(SRCS) $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)

# Запуск всех тестов (без main.c)
test: $(BIN_DIR) $(SRCS) tests/test_all.c
	$(CC) $(CFLAGS) tests/test_all.c $(SRCS) -o $(TEST_TARGET) $(LIBS)
	./$(TEST_TARGET)

# Запуск тестов с покрытием (gcov)
test-coverage: $(BIN_DIR) $(SRCS) tests/test_all.c
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage tests/test_all.c $(SRCS) -o $(TEST_TARGET) $(LIBS)
	./$(TEST_TARGET)
	gcov -b $(SRC_DIR)/*.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov $(TARGET) $(TEST_TARGET)
	rm -rf $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test test-coverage
