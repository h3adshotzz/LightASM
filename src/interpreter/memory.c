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

/*

    Memory layout/idea

    |-----|-------
    |  0  |  Memory pos 0
    |  1  |  Memory pos 1
    |  2  |  Memory pos 2
    | ... |  The rest of memory
    | 128 |  Memory pos 128
    | 129 |  The first node in the nodearray
    | ... |  The rest of the nodes
    |-----|------

    Details:

        - The user is given 128 bytes for their program which can be modified
        - After pos 128, the memory address are used to reference nodes.
        - The nodearray struct will have a base_address attribute.  

        typedef struct nodearray {
            node **value;
            int elements;
            int allocated;
            int base_address;
        } nodearray;

        The base address is retrieved from memory.c, where the address will be given
        depending on where data ends in the address space.

        To work out the addres of a instruction, You add the position of the node
        in the array onto the base address.

*/

#include "memory.h"

void address_space_dump(address_space_t* spc) {

    // Debugging message
    debugf("Dumping address_space...");

    // Print array information
    printlnf("=== ADDRESS SPACE DUMP ===");
    printlnf("Elements:             %d", spc->elements);
    printlnf("Allocated:            %d", spc->allocated);
    printlnf("");

}

int address_space_push(address_page_t* page, address_space_t* addr) {
    
/*
void* tmp = realloc(rt->pages, (rt->allocated * sizeof(address_page_t)));
        if (!tmp) {
            errorf("Could not allocated memory. Aborting!");
        }

        rt->pages = (address_page_t*)tmp;

        if (rt->elements >= 128) {
            rt->pages[rt->elements] = page;
        } else {
            rt->pages[128] = page;
        }

        rt->elements++;

        return rt;*/

}

address_space_t* address_space_new(int pages) {

    // Create a new address space
    address_space_t *rt = malloc(sizeof(address_space_t));

    rt->allocated = 128 + pages;        // We allocated 128 pages and whatever extra was requested
    rt->elements = 128;                 // We have 128 that are already filled. 

    // Cycle through (hopefully) 128 times 
    for (int i = 0; i < rt->elements; i++) {

        // Create a new page
        address_page_t *pg = malloc(sizeof(address_page_t));

        // Set the type to PAGE_TYPE_VAL and the default value to 0
        pg->type = PAGE_TYPE_VAL;
        pg->value = 0;

        // Push the page onto the address space
        address_space_push(pg, rt->pages);
    
    }

    // Return the address space
    return rt;
}