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

#include "console.h"

/**
 * Start the console
 */
void run() {

    debugf("Starting LightASM Console...");
    warningf("This is still experimental. Errors may occur");

    // We run until we're given the notice.
    int repeat = 1;
    char *curline = NULL;  

    while(repeat) {

        // Get input
        printf("-> ");
        scanf("%[^\n]%*c", curline);

        // Check if the user asked to cancel.
        if (strcmp(curline, "Quit") == 0) {
            printf("You asked to quit!\n");
            repeat = 0;
            exit(0);
        } else {

            // We didn't ask to quit/
            printf("Input: %s\n", curline);

            TokenStream* tokStream = createTokenStream(curline);

        }
    }

}