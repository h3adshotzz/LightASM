all:
	gcc -g -Wall -Werror `pkg-config --libs --cflags glib-2.0 gio-2.0` main.c token.c log.c string.c node.c parser.c -o lasmc

clean:
	rm lasmc
