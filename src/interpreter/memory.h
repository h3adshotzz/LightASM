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

#include "../utils/log.h"

typedef enum {
    PAGE_TYPE_NODE,
    PAGE_TYPE_VAL
} page_type;

typedef struct {
    void* value;
    page_type type;             // The type of page
} address_page_t;

typedef struct {
    int elements;               // The amount of allocated elements, minimum 128
    int allocated;              // The ammount of elements allocated, again minimum 128
    address_page_t **pages;     // The pages of the address space
} address_space_t;


// Functions
address_space_t* address_space_new(int pages);
void address_space_dump(address_space_t* spc);

#endif