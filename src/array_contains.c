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

#include "array_contains.h"


/**
 *  Check whether an array contains a given string
 * 
 *  Returns:
 *      int             -   true or false
 * 
 *  Params:
 *      char* val       -   The value we are checking
 *      char** arr      -   The array
 * 
 */
int array_contains(char* val, char** arr) {
    int i = 0;
    while (arr[i]) {
        if (strcmp(arr[i], val) == 0) {     // We get a BAD ACCESS if you type something that isn't a command
            return 1;
        }
        i++;
    }
    return 0;
}