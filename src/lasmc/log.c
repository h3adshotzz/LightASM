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

#include "log.h"


/**
 * println is a replacement for printf and acts similar to 
 * gprintf. printf2 removes the need for the new line
 * operator when giving a string to output.
 * 
 *  Returns:
 *      int    
 * 
 *  Params:
 *      msg_type        -   The type of message to print
 *      char* fmt       -   The contents to print
 */
int __printlnf(msg_type msgType, char *fmt, ...) {
    
    // Create arg and done vars
    va_list arg;
    int done;

    // Append what is needed depending on msg_type
    if (msgType == LOG_PRINTLN) {
        fmt = chrappend(fmt, '\n');
    } else if (msgType == LOG_ERROR) {
        fmt = mstrappend(3, ANSI_COLOR_RED "[Error] ", fmt, ANSI_COLOR_RED ANSI_COLOR_RESET "\n");
    } else if (msgType == LOG_WARNING) {
        fmt = mstrappend(3, ANSI_COLOR_YELLOW "[Warning] ", fmt, ANSI_COLOR_YELLOW ANSI_COLOR_RESET "\n");        
    } else if (msgType == LOG_DEBUG) {
        fmt = mstrappend(3, ANSI_COLOR_BLUE "[Debug] ", fmt, ANSI_COLOR_BLUE ANSI_COLOR_RESET "\n");        
    }

    // Initialize a variable argument list with arg & fmt
    va_start(arg, fmt);
        
    // assign the value of vfpritnf to done
    done = vfprintf(stdout, fmt, arg);      // EXEC_BAD_ACCESS here
        
    // End the variable argument list with arg
    va_end(arg);
        
    // Return value of done
    return done;
        
}