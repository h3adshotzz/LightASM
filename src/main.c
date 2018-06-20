/**
 * LightASM
 * Copyright (C) 2017, Is This On? 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "console.h"
#include "token.h"
#include "string.h"

void version() {
    printf("AQAAssembly %d.%d [%d]\n\n", AQA_ASM_MAJOR_VERSION, AQA_ASM_MINOR_VERSION, AQA_ASM_BUILD);
}

void help_menu() {
	
	printf("Usage:	AQAAssembly [OPTIONS] [FILE]...\n\n");
	printf("Option			GNU Long Option			Meaning\n");
	printf("-h, -?			--help				Show this message\n");
	printf("-v			--version			Show the version and build\n");
	printf("-a			--console			Run the Console\n");
	
}

int main(int argc, const char **argv) {	

#if DEBUG_MODE
    printf("argc: %d\n", argc);

    if (DEBUG_MODE) {
        for (int i = 0; i < sizeof(argv); i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
#endif

	// See what we are dealing with
    char* main_arg = argv[1];

#if DEBUG_MODE
    printf("main arg: %s\n", main_arg);
#endif

    if (main_arg != NULL) {
        if (!strcmp(main_arg, "-h") || !strcmp(main_arg, "--help")) {
		    help_menu();    // This is called from menu_helper.c
	    } else if (!strcmp(main_arg, "-v") || !strcmp(main_arg, "--version")) {
		    version();  // This is called from menu_helper.c
	    } else if (!strcmp(main_arg, "-a") || !strcmp(main_arg, "--console")) {
            run();   // This is called from console.c
        } else if (!strcmp(main_arg, "--dev")) {
	        testing();
	    } else {
            printf("Unrecognised arg[s]. Please run with -h or --help for options.\n");
        }
    } else {
        printf("No options given. Please run with -h or --help for options.\n");
        exit(0);
    }
    
    return 0;
	
}

