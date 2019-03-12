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

#ifndef MEMORY_H
#define MEMORY_H

#include "../node.h"

#include "../utils/log.h"

typedef enum {
    SPACE_TYPE_NODE,
    SPACE_TYPE_VAL
} space_type;

typedef struct address_space_t {
    space_type type;
    void** pages;
    int elements;
    int allocated;
} address_space_t;


address_space_t* address_space_new(space_type type);
void _tst_spc_dump(address_space_t* spc);
int address_space_push(address_space_t* spc, void* elm);
int address_space_get_ref(address_space_t* spc, int ref);
void address_space_set_ref(address_space_t* spc, int ref, int value);

#endif