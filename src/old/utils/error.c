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

/**
 * 
 *  To save commenting space, When a Error or 
 *      Error is used, it's stopping a crash.
 * 
 */

#include "error.h"


/**
 *  Throw the Error
 * 
 *  Returns:
 *      Error      -   The Error thrown
 * 
 *  Params:
 *      char* msg       -   The message to throw with the error
 */
Error* throw_error(char* msg) {

    // Create the Error and allocate memory, set the message
    Error* tknerr = malloc(sizeof(Error));
    tknerr->msg = msg;

    // Return the Error.
    return tknerr;

} 


/** 
 *  Print the Error
 * 
 *  Returns:
 *      void
 * 
 *  Params:
 *      Error* e       -   The Error to the print.
 */
void error_print(Error* e) {
    // Print an error with the msg.
    errorf("Thrown: %s", e->msg);
}