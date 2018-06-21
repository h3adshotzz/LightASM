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
#include "utils/log.h"

void testing() {

    warningf("This is experimental. Crashes are expected.");

    TokenStream *tknstr = create_new_token_stream("MOV R5, #22");
    TokenError *err = NULL;
    Token *tkn = NULL;
    
    while ((tkn = create_new_token(tknstr->source, &err))) {
        printf("THERE BE TKN\n");
        if (err != NULL) {
            printf("error there be\n");
            tkn_error_print(err);
        } else {
            printf("No error there be\n");
            if (tkn->type != TOK_COMMAND) {
                errorf("Expected Token Type 'TOK_COMMAND'");
            }

            if (strcmp(tkn->val, "MOV") != 0) {
                errorf("Expected 'MOV'");
            }

        }
    }
    printf("While Done\n");

}

void version() {
    printf("LightASM %d.%d [%d]\n\n", AQA_ASM_MAJOR_VERSION, AQA_ASM_MINOR_VERSION, AQA_ASM_BUILD);
}

void help_menu() {
	
	printf("Usage:	LightASM [OPTIONS] [FILE]...\n\n");
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
    const char* main_arg = argv[1];

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
            errorf("Unrecognised arg[s]. Please run with -h or --help for options.\n");
            //printf("Unrecognised arg[s]. Please run with -h or --help for options.\n");
        }
    } else {
        printf("No options given. Please run with -h or --help for options.\n");
        exit(0);
    }
    
    return 0;
	
}

