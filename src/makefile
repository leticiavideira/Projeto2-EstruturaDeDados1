# Projeto
TARGET = ted
ALUNO  = leticiavg

# Compilador
CC = gcc

CFLAGS = -std=c99 \
          -fstack-protector-all \
          -Wall \
          -Wextra \
          -O0 \
          -g \
          -ggdb \
          -Werror=implicit-function-declaration

LIBS = -lm

# Diretórios
ESTRUTURAS_DIR = estruturas
FORMAS_DIR     = formas
GERAIS_DIR     = gerais

TEST_DIR       = test
UNITY_DIR      = Unity
UNITY_SRC      = $(UNITY_DIR)/src


# Includes
INC_FLAGS = \
-I. \
-I$(ESTRUTURAS_DIR) \
-I$(FORMAS_DIR) \
-I$(GERAIS_DIR) \
-I$(UNITY_SRC)

# Fontes do projeto
SRCS = main.c \
       $(wildcard $(ESTRUTURAS_DIR)/*.c) \
       $(wildcard $(FORMAS_DIR)/*.c) \
       $(wildcard $(GERAIS_DIR)/*.c)

OBJS = $(SRCS:.c=.o)

# Testes
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Targets principais
all: ted

ted: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Compilação dos objetos
%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Testes Unitários (Unity)
tests: $(OBJS)

	@for test in $(TEST_SRCS); do \
		name=`basename $$test .c`; \
		echo "Compilando $$name"; \
		$(CC) $(CFLAGS) $(INC_FLAGS) \
		$$test \
		$(UNITY_SRC)/unity.c \
		$(filter-out main.o,$(OBJS)) \
		$(LIBS) \
		-o $(TEST_DIR)/$$name.out || exit 1; \
	done

run-tests: tests

	@for exe in $(TEST_DIR)/*.out ; do \
		echo ""; \
		echo "=============================="; \
		echo $$exe; \
		echo "=============================="; \
		./$$exe; \
	done

# Limpeza
clean:

	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(TEST_DIR)/*.out

# Empacotamento
pack: ted

	rm -f ../$(ALUNO).zip

	date >> .entrega

	cd .. && zip -r $(ALUNO).zip src Makefile LEIA-ME.txt .entrega


.PHONY: all ted tests run-tests clean pack