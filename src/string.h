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

#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils/log.h"

/*typedef struct {
    char* string;
} String;*/

char *strappend(char *a, char *b);
char *chrappend(char *a, char b);
char *mstrappend(size_t count, ...);

#endif