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

void address_page_dump(address_page_t* page) {

    /*
        EXEC_BAD_ACCESS occurs here.
    */
    if (page->type != NULL) {
        page_type type = page->type;

        switch (type) {
            case PAGE_TYPE_NODE:
                printlnf("Page Type:                    PAGE_TYPE_NODE");

                node *nde = malloc(sizeof(node));
                nde = (node *) page->value;
                node_dump(nde);
                break;

            case PAGE_TYPE_VAL:
                printlnf("Page Type:                    PAGE_TYPE_VAL");
                printlnf("Value:                        %d", (int) page->value);
                break;

            default:
                errorf("Unknown page type. Aborting!");
                exit(1);
        }
    } else {
        errorf("Page Type is NULL. Aborting!");
    }
}

void address_space_dump(address_space_t* spc) {

    // Debugging message
    debugf("Dumping address_space...");

    // Print array information
    printlnf("=== ADDRESS SPACE DUMP ===");
    printlnf("Elements:             %d", spc->elements);
    printlnf("Allocated:            %d", spc->allocated);
    printlnf("");

    if (spc->pages == NULL) {
        errorf("Pages are NULL. Aborting");
        exit(1);
    } else {
        printlnf("Pages Size:            %d", sizeof(spc->pages));
        printlnf("");
        for (int i = 0; i < spc->allocated; i++) {
            address_page_dump(spc->pages[i]);
        }
    }
}

int address_space_push(address_page_t* page, address_space_t* addr) {
    
    if (addr->allocated == addr->elements) {

        if (addr->allocated == 0) {
            addr->allocated = 130;      // 128 + 2 extra
        } else {
            addr->allocated += 2;
        }

        void *tmp = realloc(addr->pages, (addr->allocated * sizeof(address_page_t)));

        if (!tmp) errorf("Could not allocated memory. Aborting!");

        addr->pages = (address_page_t**) tmp;

        if (page->type == PAGE_TYPE_VAL) {
            for (int i = 0; i < 127; i++) {
                if (addr->pages[i] == NULL) {
                    addr->pages[i] = page;
                    i = 127;
                }
            }
        } else if (page->type == PAGE_TYPE_NODE) {
            if (addr->elements < 127) {

            }
        }
    }

/*

    if (!addr->allocated) {
        return 0;
    } else {
        void* tmp = realloc(addr->pages, addr->allocated * sizeof(address_page_t));

        if (!tmp) {
            errorf("Could not allocated memory. Aborting!");
        }

        addr->pages = (address_page_t **) tmp;

        if (page->type == PAGE_TYPE_NODE) {
            if (addr->elements > 128) {
                addr->pages[addr->elements] = page;
            } else {
                addr->pages[128] = page;
            }
        } else {
            for (int i = 0; i < 128; i++) {
                if (addr->pages[i] == NULL) {
                    addr->pages[i] = page;
                } 
            }
        }

        addr->elements++;

        return addr->elements;
    }*/

}

address_space_t* address_space_new() {

    // Create a new address space
    address_space_t *rt = malloc(sizeof(address_space_t));

    rt->allocated = 128 + 1;        // We allocated 128 pages and 1 for a node
    rt->elements = 0;                 // We have 128 that are already filled. 
    rt->pages = NULL;

    // Cycle through (hopefully) 128 times 
    for (int i = 0; i < 127; i++) {

        // Create a new page
        address_page_t *pg = malloc(sizeof(address_page_t));

        // Set the type to PAGE_TYPE_VAL and the default value to 0
        pg->type = PAGE_TYPE_NODE;
        pg->value = 0;

        // Push the page onto the address space
        address_space_push(pg, rt);
    
    }

    // Return the address space
    return rt;
}