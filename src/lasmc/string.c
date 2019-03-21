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
#include <string.h>

#include "str.h"

/**
 *  Append the "string" b to a
 * 
 *  Returns:
 *      char*       -   The appended "string"
 * 
 *  Params:
 *      char* a     -   The char which we are appending to
 *      char* b     -   The char being appended.
 * 
 */
char *strappend(char *a, char *b) {
    // Get the length of a & b
    size_t a_len = strlen(a), b_len = strlen(b);
    // Create a string for the length of a + b with
    // an extra byte for NULL termination
    char *result = malloc(a_len + b_len + 1);
    // If result is empty, a & b were probably empty
    if (!result)
        // So return NULL
        return NULL;
    // Copy the length of a bytes of a into result
    memcpy(result, a, a_len);
    // Copy the length of b bytes of b into result
    // Starting at length of a bytes into result plus
    // the null termination of b
    memcpy(result + a_len, b, b_len + 1);
    result[a_len + b_len] = '\0';
    // Return the new string
    return result;
}


/**
 *  Append a char to a string
 * 
 *  Returns:
 *      char*       -   The appended "string"
 * 
 *  Params:
 *      char* a     -   The string we are appending to
 *      char b      -   The char being appended to a
 *  
 */
char *chrappend(char *a, char b) {
    // The result will be long (ch + NULL)
    char *result = malloc(2);
    // Copy 1 byte from a refrence to ch into result
    memcpy(result, &b, 1);
    // NULL termination of the string
    result[1] = '\0';
    // Return the new string
    return strappend(a, result);
}


/**
 * Append multiple strings together
 * 
 * Returns:
 *      char        -   The appended "String"[s]
 * 
 * Params:
 *      size_t count    -   The amount of string we are appending
 *      ...             -   The va_list of string to append to eachother.
 */
char *mstrappend(size_t count, ...) {
    
    // Create a va_list, char* and size_t
    va_list arg;                        // va_list arguments
    char *rt;                           // string to return
    size_t len = 0;                     // length of all the parameters together
    char *content[count];               // array to hold each parameter from va_arg()
    
    // Initialise the va list
    va_start(arg, count);     
            
    // If there are enough args to continue
    if (count > 1) {
        for (int i = 0; i < count; i++) {
            // assign va_arg to a temp var
            char *tmp = va_arg(arg, char*);
            /* assign len as the current value + length of current value of tmp
                this is to get the full amount of characters in the final
                appended string */
            len = len + strlen(tmp);
            // set i on content to value of tmp
            content[i] = tmp;
        }
    
        // allocated enough bytes in rt for all contents values + a null byte
        rt = malloc(len + 1);
        for (int i = 0; i < count; i++) {
            // append content at i to rt
            rt = strappend(rt, content[i]);
        }
    
    } else {
        // Not enough args to continue, present error
        errorf("Not enough args given");
        // Return with NULL to prevent continuation and SEGFAULT
        return NULL;
    }
    
    // append a Null byte to the end of rt
    rt = strappend(rt, "\0");
    
    // Stop the va_list
    va_end(arg);
            
    // Return the newly appended string
    return rt;
        
}