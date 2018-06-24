TARGET	= lightasm
SRCDIR	= src
OBJDIR	= obj

CC		= gcc
CFLAGS	= -g -Wall

LIB_SOURCES =							\
	token.c 							\
	string.c 							\
	console.c							\
	array_contains.c 					\
	utils/log.c							\
	utils/error.c						\
	interpreter/interpreter.c

TEST_SOURCES = 							\
	main.c								

INTERPRETER_SOURCES =					\
	interpreter/interpreter.c			

LIB_OBJECTS=$(LIB_SOURCES:%.c=$(OBJDIR)/%.o)
TEST_OBJECTS=$(TEST_SOURCES:%.c=$(OBJDIR)/%.o)

LIB = $(OBJDIR)/liblightasmcore.a
LIBFLAGS = -L$(OBJDIR) -llightasmcore

all: outdir $(OBJDIR)/lightasmcore_test

outdir:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/utils
	@mkdir -p $(OBJDIR)/interpreter

# Build all the c files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

$(LIB): $(LIB_OBJECTS)
	ar rcs $@ $(LIB_OBJECTS)

$(OBJDIR)/lightasmcore_test: $(TEST_OBJECTS) $(LIB)
	$(CC) $(TEST_OBJECTS) $(CFLAGS) $(LIBFLAGS) -o $@

clean:
	@rm -rf obj/*