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

nodearray* nodearray_new() {
    nodearray* array = malloc(sizeof(nodearray));
    array->value = NULL;
    array->elements = NULL;
    array->allocated = NULL;

    return array;
}

int nodearray_push(nodearray* array, node* item) {

    // If the number allocated is equal to the size, we need more space
    if (array->allocated == array->elements) {

        // If there are no elements, start with 2
        if (array->allocated == 0) {
            array->allocated = 2;
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