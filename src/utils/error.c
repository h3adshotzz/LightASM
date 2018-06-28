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

#include "error.h"


/**
 *  Throw the TokenError
 * 
 *  Returns:
 *      TokenError      -   The TokenError thrown
 * 
 *  Params:
 *      char* msg       -   The message to throw with the error
 */
TokenError* throw_token_error(char* msg) {

    // Create the TokenError and allocate memory, set the message
    TokenError* tknerr = malloc(sizeof(TokenError));
    tknerr->msg = msg;

    // Return the TokenError.
    return tknerr;

} 


/** 
 *  Print the TokenError
 * 
 *  Returns:
 *      void
 * 
 *  Params:
 *      TokenError* e       -   The TokenError to the print.
 */
void tkn_error_print(TokenError* e) {
    // Print an error with the msg.
    errorf("Thrown: %s", e->msg);
}


/**
 *  Throw the RuntimeError
 * 
 *  Returns:
 *      RuntimeError      -   The RuntimeError thrown
 * 
 *  Params:
 *      char* msg       -   The message to throw with the error
 */
RuntimeError* throw_runtime_error(char* msg) {

    // Create the RuntimeError and allocate memory, set the message
    RuntimeError* rterr = malloc(sizeof(RuntimeError));
    rterr->msg = msg;

    // Return the RuntimeError.
    return rterr;

} 


/** 
 *  Print the RuntimeError
 * 
 *  Returns:
 *      void
 * 
 *  Params:
 *      RuntimeError* e       -   The RuntimeError to the print.
 */
void rt_error_print(RuntimeError* e) {
    // Print an error with the msg.
    errorf("Thrown: %s", e->msg);
}