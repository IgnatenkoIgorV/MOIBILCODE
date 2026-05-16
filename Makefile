CC = gcc
CFLAGS = -Wall -Wextra -Iincludes
LIBS = -lsqlite3
SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o)
TARGET = $(BIN_DIR)/app

# Список всех тестов
TESTS = test_auth test_db test_workshop test_car test_repair test_report

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $^ $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Запуск всех тестов
test: $(BIN_DIR) $(SRCS)
	@echo "=========================================="
	@echo "Running all tests..."
	@echo "=========================================="
	@for test in $(TESTS); do \
		echo "Compiling tests/$$test.c..."; \
		$(CC) $(CFLAGS) tests/$$test.c $(SRCS) -o $(BIN_DIR)/$$test $(LIBS) 2>/dev/null; \
		if [ -f $(BIN_DIR)/$$test ]; then \
			./$(BIN_DIR)/$$test; \
		else \
			echo "  FAILED to compile $$test"; \
		fi \
	done
	@echo "=========================================="
	@echo "All tests completed!"
	@echo "=========================================="

# Запуск отдельных тестов
test-auth: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_auth.c $(SRCS) -o $(BIN_DIR)/test_auth $(LIBS)
	./$(BIN_DIR)/test_auth

test-db: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_db.c $(SRCS) -o $(BIN_DIR)/test_db $(LIBS)
	./$(BIN_DIR)/test_db

test-workshop: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_workshop.c $(SRCS) -o $(BIN_DIR)/test_workshop $(LIBS)
	./$(BIN_DIR)/test_workshop

test-car: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_car.c $(SRCS) -o $(BIN_DIR)/test_car $(LIBS)
	./$(BIN_DIR)/test_car

test-repair: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_repair.c $(SRCS) -o $(BIN_DIR)/test_repair $(LIBS)
	./$(BIN_DIR)/test_repair

test-report: $(BIN_DIR)
	$(CC) $(CFLAGS) tests/test_report.c $(SRCS) -o $(BIN_DIR)/test_report $(LIBS)
	./$(BIN_DIR)/test_report

clean:
	rm -f *.o $(TARGET)
	rm -rf $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test test-auth test-db test-workshop test-car test-repair test-report
