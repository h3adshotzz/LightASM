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

LIB_OBJECTS=$(LIB_SOURCES:%.c=$(OBJDIR)/%.o)
TEST_OBJECTS=$(TEST_SOURCES:%.c=$(OBJDIR)/%.o)

LIB = $(OBJDIR)/liblightasmcore.a
LIBFLAGS = -L$(OBJDIR) -llightasmcore

all: $(OBJDIR)/lightasmcore_test

# Build all the c files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "   CC  $@\n"
	@# Make sure the output dir exists
	@mkdir -p $(@D)
	@# Build the file
	@$(CC) -c $< $(CFLAGS) -o $@

$(LIB): $(LIB_OBJECTS)
	@printf "   AR  $@\n"
	@ar rcs $@ $(LIB_OBJECTS)

$(OBJDIR)/lightasmcore_test: $(TEST_OBJECTS) $(LIB)
	@printf " LINK  $@\n"
	@$(CC) $(TEST_OBJECTS) $(CFLAGS) $(LIBFLAGS) -o $@

clean:
	@rm -rf obj/*