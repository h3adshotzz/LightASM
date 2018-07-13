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

#ifndef ERROR_H
#define ERROR_H

#include "log.h"

/**
 *  The TokenError struct
 * 
 *  char* msg   -   The message to throw
 */
typedef struct {
    char* msg;
} TokenError;


/**
 *  The RuntimeError struct
 * 
 *  char* msg   -   The message to throw
 */
typedef struct {
    char* msg;
} RuntimeError;

#define error_thrown(err) if (*err) return;


// Error Functions
void tkn_error_print(TokenError* e);
TokenError* throw_token_error(char* msg);

void rt_error_print(RuntimeError* e);
RuntimeError* throw_runtime_error(char* msg);

#endif