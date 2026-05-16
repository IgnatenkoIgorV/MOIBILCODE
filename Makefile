CC = gcc
CFLAGS = -Wall -Wextra -Iincludes
LIBS = -lsqlite3
SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o)
TARGET = $(BIN_DIR)/app

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $^ $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) tests/*.c -o $(BIN_DIR)/tests $(LIBS)
	./$(BIN_DIR)/tests

clean:
	rm -f *.o $(TARGET)
	rm -rf $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test
