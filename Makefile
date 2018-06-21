TARGET 	= lightasm
OBJDIR	= obj/
CORE_SOURCES =						\
	src/main.c 							\
	src/token.c 						\
	src/string.c 						\
	src/console.c						\
	src/array_contains.c 				\
	src/utils/log.c						\
	src/utils/error.c
INTERPRETER_SOURCES =					\
	src/interpreter/interpreter.c	
CC		= gcc
CFLAGS	= -g -Wall -o

all:
	$(CC) $(CORE_SOURCES) $(CFLAGS) $(OBJDIR)lightasmcore.o
	$(CC) $(INTERPRETER_SOURCES) $(CFLAGS) $(OBJDIR)interpreter.o		

	# These two should eventually be linked to form the exec LightASM
	# Also i want to make the terminal output look nicer. IDK how.

core:
	$(CC) $(CORE_SOURCES) $(CFLAGS) $(OBJDIR)lightasmcore.o

interpreter:
	$(CC) $(INTERPRETER_SOURCES) $(CFLAGS) $(OBJDIR)interpreter.o

clean:
	rm -rf obj/*



