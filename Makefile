# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CFLAGS_USER ?=

# Тип сборки и финальные флаги компилятора
ifeq ($(BUILD_TYPE),shared)
CFLAGS_FINAL = $(CFLAGS) -fPIC $(CFLAGS_USER)
else
CFLAGS_FINAL = $(CFLAGS) $(CFLAGS_USER)
endif

# Флаги линкера
LDFLAGS =
LDFLAGS_USER ?=
LDFLAGS_FINAL = $(LDFLAGS) $(LDFLAGS_USER)

# Директория для сборки и цель по умолчанию
BUILD_DIR ?= build
TARGET = $(BUILD_DIR)/program
STATIC_TARGET = $(BUILD_DIR)/libmylib.a
SHARED_TARGET = $(BUILD_DIR)/libmylib.so
OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(wildcard src/*.c))

# Создание директории для сборки
$(shell mkdir -p $(BUILD_DIR))

# Сборка цели
ifeq ($(BUILD_TYPE),shared)
$(TARGET): $(OBJS) $(SHARED_TARGET)
	$(CC) $(CFLAGS_FINAL) -o $@ $(OBJS) -L$(BUILD_DIR) -lmylib $(LDFLAGS_FINAL)
else
$(TARGET): $(OBJS) $(STATIC_TARGET)
	$(CC) $(CFLAGS_FINAL) -static -o $@ $(OBJS) -L$(BUILD_DIR) -lmylib $(LDFLAGS_FINAL)
endif

# Создание shared библиотеки
$(SHARED_TARGET): $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	$(CC) -shared -o $@ $^

# Создание static библиотеки
$(STATIC_TARGET): $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	ar rcs $@ $^

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS_FINAL) -c -o $@ $<

# Статический анализ кода
check:
	./checkpatch.pl --no-tree -f --showfile --fix src/*.c

# Очистка файлов сборки
clean:
ifeq ($(KEEP_LIBS), 1)
	rm -rf $(BUILD_DIR)/*.o
	rm -rf $(TARGET)
else
	rm -rf $(BUILD_DIR)
endif

# Установка
install: $(TARGET)
ifndef DESTDIR
	@echo "Error: Destination directory is not specified. Usage: make install DESTDIR=<directory>"
else
	mkdir -p $(DESTDIR)
	cp $(TARGET) $(DESTDIR)/program
endif

# Помощь
help:
	@echo "Usage: make [target] [OPTIONS]"
	@echo ""
	@echo "Targets:"
	@echo "  all           - Build the project (default target)"
	@echo "  check         - Perform static code analysis with checkpatch.pl"
	@echo "  clean         - Remove all generated files or only object files if KEEP_LIBS=1"
	@echo "  install       - Install the program to the specified DESTDIR"
	@echo "  help          - Display this help message"
	@echo ""
	@echo "Options:"
	@echo "  BUILD_DIR     - Directory for build files (default: build)"
	@echo "  BUILD_TYPE    - Build type (shared or static, default: static)"
	@echo "  CFLAGS_USER   - Additional compiler flags"
	@echo "  LDFLAGS_USER  - Additional linker flags"
	@echo "  DESTDIR       - Destination directory for 'make install'"
	@echo "  KEEP_LIBS     - Keep library files during clean (default: 0)"

.PHONY: check clean install help