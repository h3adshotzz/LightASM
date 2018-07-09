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

#include "memory.h"

void _tst_pge_dump(void* pge, space_type type, int memref) {
    if (type != NULL) {

        switch (type) {
            case SPACE_TYPE_VAL:
                printlnf("Memory Ref:                   %d", memref);
                printlnf("Value:                        %d", (int) pge);
                printlnf("--------------------------------------");
                break;
            
            case SPACE_TYPE_NODE:
                break;

            default:
                break;
        }

    }
}

void _tst_spc_dump(address_space_t* spc) {
    // Debugging message
    debugf("Dumping address_space...");

    // Print array information
    printlnf("=== ADDRESS SPACE DUMP ===");
    if (spc->type == SPACE_TYPE_VAL) {
        printlnf("Type:                 SPACE_TYPE_VAL");
    } else if (spc->type == SPACE_TYPE_NODE) {
        printlnf("Type:                 SPACE_TYPE_NODE");
    } else {
        printlnf("Type:                 UNKNOWN");
        printlnf("Elements:             %d", spc->elements);
        printlnf("Allocated:            %d", spc->allocated);
        printlnf("");

        errorf("Error, Type is unknown. Aborting....");
        exit(1);
    }
    printlnf("Elements:             %d", spc->elements);
    printlnf("Allocated:            %d", spc->allocated);
    printlnf("");

    for (int i = 0; i < spc->elements; i++) {
        _tst_pge_dump(spc->pages[i], spc->type, i);
    }
}

int address_space_get_ref(address_space_t* spc, int ref) {
    int tmp = (int) spc->pages[ref];
    if (tmp != NULL) {
        return tmp;
    } else {
        return 0;
    }
}

int address_space_push(address_space_t* spc, void* elm) {

    if (spc->type == SPACE_TYPE_VAL) {

        debugf("Pushing a space_type of SPACE_TYPE_VAL, %d, onto the address space...", elm);

        if (spc->allocated <= spc->elements) {
            // Throw an error, out of user memroy.
        }

        spc->pages[spc->elements] = elm;
        spc->elements++;

        return 1;

    }

}

address_space_t* address_space_new(space_type type) {

    address_space_t* rt = malloc(sizeof(address_space_t));

    if (type == SPACE_TYPE_VAL) {

        rt->type = SPACE_TYPE_VAL;
        rt->allocated = 128;        // We allocated 128 for the user data.
        rt->elements = 5;           // There currently isn't anything in it. 

        rt->pages = malloc(sizeof(int) * rt->allocated);    // Allocate enough memory. 

        rt->pages[0] = 12;
        rt->pages[1] = 13;
        rt->pages[2] = 14;
        rt->pages[3] = 15;

        return rt;

    } else if (type == SPACE_TYPE_NODE) {

        rt->type = SPACE_TYPE_NODE;
        rt->allocated = 10;;        // We allocate 10 for the commands.
        rt->elements = 0;           // There currently isn't anything in it.

        rt->pages = malloc(sizeof(node) * rt->allocated);

        return rt;

    } 
}