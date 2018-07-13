/**
 * LightASM
 * Copyright (C) 2018, Is This On? 
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

#include "consts.h"
#include "console.h"
#include "string.h"

#include "node.h"

#include "interpreter/memory.h"

void testing() {

    warningf("This is experimental. Crashes are expected.");
    
    address_space_t* spc = malloc(sizeof(address_space_t));
    spc = address_space_new(SPACE_TYPE_VAL);
    _tst_spc_dump(spc);

    address_space_push(spc, (void*)(long)22);
    address_space_push(spc, (void*)(long)34);
    address_space_push(spc, (void*)(long)12);
    address_space_push(spc, (void*)(long)45);
    address_space_push(spc, (void*)(long)234);
    address_space_push(spc, (void*)(long)2);
    address_space_push(spc, (void*)(long)44);


    _tst_spc_dump(spc);

}


/**
 *  Just some version information
 * 
 */
void version() {
    // Print the version information. Use the consts in consts.h
    printf("LightASM %d.%d [%d]\n\n", AQA_ASM_MAJOR_VERSION, AQA_ASM_MINOR_VERSION, AQA_ASM_BUILD);
}


/**
 *  The help menu. 
 * 
 */
void help_menu() {
	
    // Print usage information.
	printf("Usage:	LightASM [OPTIONS] [FILE]...\n\n");
	printf("Option			GNU Long Option			Meaning\n");
	printf("-h, -?			--help				Show this message\n");
	printf("-v			--version			Show the version and build\n");
	printf("-a			--console			Run the Console\n");
	
}


/**
 *  The main function of all this gloriousness... maybe that's spelt right idk.
 * 
 *  Return:
 *      int             -   idek
 * 
 *  Param:
 *      int - argc      -   The amount of args given
 *      char - argv     -   The args given.
 * 
 */
int main(int argc, const char **argv) {	


#if DEBUG_MODE

    // If debug mode is active we print argc and argv
    printf("argc: %d\n", argc);

    if (DEBUG_MODE) {
        for (int i = 0; i < sizeof(argv); i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
#endif

	// See what we are dealing with
    // This will be replaced soon.
    const char* main_arg = argv[1];

#if DEBUG_MODE
    // Again, if debug mode is active, print the main arg. 
    printf("main arg: %s\n", main_arg);
#endif

    /**
     *  The joy that is determaining what the user entered.
     */
    if (main_arg != NULL) {
        if (!strcmp(main_arg, "-h") || !strcmp(main_arg, "--help")) {
		    help_menu();    // This is called from menu_helper.c
	    } else if (!strcmp(main_arg, "-v") || !strcmp(main_arg, "--version")) {
		    version();  // This is called from menu_helper.c
	    } else if (!strcmp(main_arg, "-a") || !strcmp(main_arg, "--console")) {
            console_run();   // This is called from console.c
        } else if (!strcmp(main_arg, "--dev")) {
	        testing();
	    } else {
            // Oh dear.
            errorf("Unrecognised arg[s]. Please run with -h or --help for options.\n");
            exit(1);
        }
    } else {
        // Oh dear again.
        printf("No options given. Please run with -h or --help for options.\n");
        exit(1);
    }
    
    // Return 0
    return 0;
}
