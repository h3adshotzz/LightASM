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

#include "node.h"

void node_dump(node* node) {

    if (!node) {
        warningf("Node is nil");
        exit(0);
    }

    // Check the type
    switch(node->type) {
        case NTYPE_MOV:                     
            printlnf("Node Type:                                NTYPE_MOV");
        
            node_op *node_op_value = (node_op *) node->value;

            if (node_op_value->type == NOP_REGISTER) {
                printlnf("Operation Destination:                    R%d", node_op_value->dest);
                printlnf("Operation Value:                          R%d", node_op_value->value);
            } else {
                printlnf("Operation Destination:                    R%d", node_op_value->dest);
                printlnf("Operation Value:                          #%d", node_op_value->value);
            }

            break;
        
        case NTYPE_LDR:
            printlnf("Node Type:                                NTYPE_LDR");

            node_mem *node_mem_value = (node_mem *)node->value;

            printlnf("Operation Register:                       R%d", node_mem_value->reg);
            printlnf("Operation Memref:                         %d", node_mem_value->mem);

            break;

        default:
            errorf("Unknown Node Type.");
    }

}

void nodearray_dump(nodearray* array) {

    debugf("Dumping nodearray...");

    // Print array information
    printlnf("=== NODEARRAY DUMP ===");
    
    printlnf("Elements:             %d", array->elements);
    printlnf("Allocated:            %d", array->allocated);
    printlnf("");

    for (int i = 0; i < array->elements; i++) {
        
        

        printlnf("== Node %d ==", i);
        node_dump(array->value[i]);
    }
}


nodearray* nodearray_new() {
    nodearray* array = malloc(sizeof(nodearray));
    array->value = NULL;
    array->elements = 0;
    array->allocated = 0;

    return array;
}

int nodearray_push(nodearray* array, node* item) {

    // If the number allocated is equal to the size, we need more space
    if (array->allocated == array->elements) {

        // If there are no elements, start with 2
        if (array->allocated == 0) {
            array->allocated = 10;
        } else {
            // Add another two
            array->allocated += 2;
        }

        /**
         * Move the array to a place in memory that can hold it.
         * 
         * array->value is what we are re-allocating
         * 
         * array->allocated * sizeof(node*) is just allocating the amount of
         * nodes we need
         */
        void *tmp = realloc(array->value, (array->allocated * sizeof(node*)));

        // Did we cock up somewhere?
        if (!tmp) {
            // Error msg
            errorf("Could not allocate memory. Aborting!");
            exit(0);
        }

        // Things appear to have gone okay, store the new pointer.
        array->value = (node**)tmp;
    }

    // Store the new node
    array->value[array->elements] = item;

    // Increment the elemnt count
    array->elements++;

    // Return
    return array->elements;

}